#include "API.h"

ESP8266WebServer server(80);

void API::begin(boolean connected)
{
  if (connected)
  {
    server.on("/api/config", HTTP_GET, std::bind(&API::handleConfig, this));
    server.on("/api/reset", HTTP_POST, std::bind(&API::handleReset, this));
    server.on("/api/update", HTTP_POST, std::bind(&API::handleUpdate, this));
  }
  else
  {
    server.on("/api/scan", HTTP_GET, std::bind(&API::handleScan, this));
    server.on("/api/wifi", HTTP_POST, std::bind(&API::handleWifi, this));
  }
  
  server.on("/api/auth", HTTP_POST, std::bind(&API::handleAuth, this));
  
  server.begin();
};

void API::run()
{
  server.handleClient();
};

void API::handleScan()
{
  DynamicJsonDocument doc(400);
  JsonObject response = doc.to<JsonObject>();

  int8_t networksFound = WiFi.scanNetworks();

  JsonArray connections = response.createNestedArray("connections");

  for (int i = 0; i < networksFound; ++i)
  {
    JsonObject connection = connections.createNestedObject();
    connection["name"] = WiFi.SSID(i);
    connection["signal"] = WiFi.RSSI(i);
    connection["encryption"] = WiFi.encryptionType(i);
  }

  char buffer[400];
  serializeJson(response, buffer);

  server.send(200, "application/json", buffer);
}

void API::handleWifi()
{
  DynamicJsonDocument body(200);

  deserializeJson(body, server.arg("plain"));

  String ssid = body["ssid"];
  String password = body["password"];

  WiFi.begin(ssid, password);

  Debugger::log("connecting");
  
  while (wifi_station_get_connect_status() == STATION_CONNECTING)
  {
    Debugger::log(".");
    delay(1000);
  }

  if (wifi_station_get_connect_status() != STATION_GOT_IP)
  {
    server.send(401, "text/plain", String(wifi_station_get_connect_status()));
  }
  else
  {
    eeprom.saveSSID(ssid);
    eeprom.savePassword(password);
    server.send(200);
  }
}

void API::handleConfig()
{
  DynamicJsonDocument doc(200);
  JsonObject response = doc.to<JsonObject>();

  response["md5"] = ESP.getSketchMD5();
  response["token"] = eeprom.getAuth();

  char buffer[200];
  serializeJson(response, buffer);

  server.send(200, "application/json", buffer);
}

void API::handleAuth()
{
  DynamicJsonDocument body(200);

  deserializeJson(body, server.arg("plain"));

  String token = body["token"];

  eeprom.saveAuth(token);

  server.send(200);

  ESP.restart();
}

void API::handleReset()
{
  eeprom.erase();

  server.send(200);

  ESP.restart();
}

void API::handleUpdate()
{
  DynamicJsonDocument body(200);

  deserializeJson(body, server.arg("plain"));

  String url = body["url"];

  WiFiClient client;

  ESPhttpUpdate.rebootOnUpdate(false);
  ESPhttpUpdate.closeConnectionsOnUpdate(false);
  
  t_httpUpdate_return ret = ESPhttpUpdate.update(client, url);

  switch(ret) {
    case HTTP_UPDATE_OK:
      server.send(200);
      ESP.restart();
      break;
    case HTTP_UPDATE_FAILED:
      server.send(500, "http/plain", ESPhttpUpdate.getLastErrorString());
      break;
    default:
      server.send(500, "http/plain", String(ret));
  }
}
