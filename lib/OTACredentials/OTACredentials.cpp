#include "Arduino.h"
#include "OTACredentials.h"

OTAEEPROM eeprom;
WebSocketsServer webSocket = WebSocketsServer(81); // Creating WebSocket Server at port81
bool checking;
NonBlockDelay d;
uint8_t num;
int c;

void onScanComplete(int networksFound)
{
	Serial.print(networksFound);
	Serial.println(" network(s) found");

	DynamicJsonDocument responseDoc(400);
	JsonObject response = responseDoc.to<JsonObject>();

	response["type"] = "scan";
	JsonArray connections = response.createNestedArray("connections");


	for (int i = 0; i < networksFound; ++i)
	{ 
		JsonObject connection = connections.createNestedObject();
		connection["name"] = WiFi.SSID(i);
		connection["signal"] = WiFi.RSSI(i);
		connection["encryption"] = WiFi.encryptionType(i) != ENC_TYPE_NONE;
	}

	char buffer[400]; // create temp buffer
	size_t len = serializeJson(response, buffer);  // serialize to buffer

	Serial.println(buffer);
	
	// send message to client
	webSocket.sendTXT(num, buffer);
}

void waitConnection()
{
	if (!d.Timeout())
		return;

	switch (WiFi.status())
	{
	case WL_CONNECT_FAILED:
		checking = false;
		webSocket.sendTXT(num, "{\"type\": \"wifi\", \"status\": false, \"message\": \"Wrong password\"}");
		break;
	case WL_NO_SSID_AVAIL:
		checking = false;
		webSocket.sendTXT(num, "{\"type\": \"wifi\", \"status\": false, \"message\": \"Network not found\"}");
		break;
	case WL_CONNECTED:
		checking = false;
		webSocket.sendTXT(num, "{\"type\": \"wifi\", \"status\": true}");
		break;
	default:
		if (c > 15)
		{
			checking = false;
			webSocket.sendTXT(num, "{\"type\": \"wifi\", \"status\": false}");
			WiFi.mode(WIFI_AP_STA);
			WiFi.disconnect();
			// delay(100);
			return;
		}
		d.Delay(500);
		Serial.print("*");
		c++;
		break;
	}
}

void _testWifi2(String SSID, String password)
{
	c = 0;
	Serial.println("Testing wifi credentials");
	char *my_ssid = &SSID[0];
	char *my_pass = &password[0];

	WiFi.begin(my_ssid, my_pass);
	checking = true;
}

void _webSocketEvent(uint8_t numm, WStype_t type, uint8_t *payload, size_t length)
{
	num = numm;
	switch (type)
	{
	case WStype_DISCONNECTED:
		Serial.printf("[%u] Disconnected!\n", num);
		break;
	case WStype_CONNECTED:
	{
		IPAddress ip = webSocket.remoteIP(num);
		Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
		if (WiFi.status() == WL_CONNECTED)
		{
			WiFi.disconnect();
		}
	}
	break;
	case WStype_TEXT:
	{
		Serial.printf("[%u] get Text: %s\n", num, payload);

		String message = String((char *)(payload));
		Serial.println(message);

		//JSON part
		DynamicJsonDocument doc(1024);
		DeserializationError error = deserializeJson(doc, message);

		String type = doc["type"];

		if (type.equals("auth"))
		{
			String auth = doc["auth"];

			eeprom.saveAuth(auth);

			webSocket.sendTXT(num, "{\"type\": \"auth\", \"status\": true}");

			//Restarting ESP board
			ESP.restart();
		}

		if (type.equals("wifi"))
		{
			String pass = doc["pass"];
			String ssid = doc["ssid"];

			_testWifi2(ssid, pass);

			eeprom.erase(false);

			eeprom.saveSSID(ssid);

			eeprom.savePassword(pass);
		}

		if (type.equals("scan"))
		{
			WiFi.scanNetworksAsync(onScanComplete, true);
		}
	}
	break;
	}
}

void _webSocketEventST(uint8_t numm, WStype_t type, uint8_t *payload, size_t length)
{
	if (type != WStype_TEXT) {
		return;
	}

	Serial.printf("[%u] get Text: %s\n", numm, payload);

	String message = String((char *)(payload));
	Serial.println(message);

	//JSON part
	DynamicJsonDocument doc(1024);
	DeserializationError error = deserializeJson(doc, message);

	DynamicJsonDocument responseDoc(200);
	JsonObject response = responseDoc.to<JsonObject>();

	String messageType = doc["type"];

	if (messageType.equals("reset"))
	{

		eeprom.erase(true);
		//Restarting ESP board
		ESP.restart();
	}

	if (messageType.equals("auth"))
	{
		String auth = doc["auth"];

		eeprom.saveAuth(auth);

		response["type"] = "auth";
		response["status"] = true;

		char buffer[200]; // create temp buffer
		size_t len = serializeJson(response, buffer);  // serialize to buffer

		webSocket.sendTXT(num, buffer);

		//Restarting ESP board
		ESP.restart();
	}

	if (messageType.equals("update"))
	{
		String url = doc["url"];
		String update_status = F("Checking for update...\n");
		WiFiClient client;

		t_httpUpdate_return ret = ESPhttpUpdate.update(client, url);

		update_status += F("Returned: ");
		switch (ret)
		{
		case HTTP_UPDATE_FAILED:
			update_status += "Update failed:\nLastError: ";
			update_status += ESPhttpUpdate.getLastError();
			update_status += "\nError: ";
			update_status += ESPhttpUpdate.getLastErrorString().c_str();
			update_status += "\n";
			break;

		case HTTP_UPDATE_NO_UPDATES:
			update_status += F("No Update Available.\n");
			break;

		case HTTP_UPDATE_OK:
			update_status += F("Updated OK.\n");
			break;
		}
		Serial.println(update_status);
	}

	if (messageType.equals("config"))
	{
		String token = eeprom.getAuth();
		String md5 = ESP.getSketchMD5();

		response["type"] = "config";
		response["token"] = token;
		response["md5"] = md5;

		char buffer[200]; // create temp buffer
		size_t len = serializeJson(response, buffer);  // serialize to buffer
		
		Serial.println(buffer);

		webSocket.sendTXT(num, buffer);
	}
}

void credentials::Erase_eeprom()
{
	eeprom.erase(true);
}

String credentials::EEPROM_Config()
{
	Serial.println();
	Serial.println();

	//---------------------------------------- Read eeprom for ssid and pass
	Serial.println("Reading EEPROM");

	ssid = eeprom.getSSID();

	pass = eeprom.getPassword();

	String auth_token = eeprom.getAuth();

	return auth_token;
}

bool credentials::credentials_get()
{
	if (_testWifi())
	{
		Serial.println("Succesfully Connected!!!");
		return true;
	}
	else
	{
		Serial.println("Turning the HotSpot On");
		return false;
	}
}

void credentials::setupAP(char *softap_ssid, char *softap_pass)
{

	WiFi.mode(WIFI_AP_STA);
	WiFi.disconnect();
	delay(100);

	WiFi.softAP(softap_ssid, softap_pass);

	Serial.println("softap");

	Serial.println("Server Started");
	webSocket.begin();
	webSocket.onEvent(_webSocketEvent);
}

void credentials::setupST()
{
	webSocket.begin();
	webSocket.onEvent(_webSocketEventST);
}

bool credentials::_testWifi()
{
	int c = 0;
	Serial.println("Waiting for Wifi to connect");
	char *my_ssid = &ssid[0];
	char *my_pass = &pass[0];

	WiFi.begin(my_ssid, my_pass);
	while (c < 20)
	{
		if (WiFi.status() == WL_CONNECTED)
		{
			return true;
		}
		delay(500);
		Serial.print("*");
		c++;
	}
	Serial.println("");
	Serial.println("Connect timed out, opening AP");
	return false;
}

void credentials::server_loops()
{
	if (checking)
	{
		waitConnection();
	}
	webSocket.loop();
}
