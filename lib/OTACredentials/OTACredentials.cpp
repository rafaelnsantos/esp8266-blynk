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

	// String connections = "{\"type\": \"scan\"";
	String connections = "{\"type\": \"scan\", \"connections\": [";

	for (int i = 0; i < networksFound; ++i)
	{ // [{"name": "asdasd", "signal": 88, "encryption": true}]
		// connections += ",\"" + String(WiFi.SSID(i)) + "\": {\"signal\":" + String(WiFi.RSSI(i)) + ",\"encryption\":" + String((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "false" : "true") + "}";
		connections += "{\"name\": \"" + String(WiFi.SSID(i)) + "\", \"signal\": " + String(WiFi.RSSI(i)) + ", \"encryption\": " + String((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "false" : "true") + "}";
		if (i < networksFound - 1)
		{
			connections += ",";
		}
	}
	connections += "]}";
	Serial.println(connections);

	// send message to client
	webSocket.sendTXT(num, connections);
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
			delay(2000);

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

	_launchWeb();
	Serial.println("Server Started");
	webSocket.begin();
	webSocket.onEvent(_webSocketEvent);
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

void credentials::_launchWeb()
{
	Serial.println("");
	Serial.print("SoftAP IP: ");
	Serial.println(WiFi.softAPIP());

	webServer.begin();
}

void credentials::server_loops()
{
	if (checking)
	{
		waitConnection();
	}
	webSocket.loop();
}
