#include "API.h"

void API::begin(bool connected)
{
  if (connected)
  {
    server.on("/api/reset", HTTP_GET, std::bind(&API::handleReset, this));

    const char * headerkeys[] = {"Token"} ;
    size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
    server.collectHeaders(headerkeys, headerkeyssize );

    String key = data.getSwitchID() + data.getAppSecret();
    Crypto.setKey(key.substring(0, 64));
  }
  else
  {
    server.on("/api/scan", HTTP_GET, std::bind(&API::handleScan, this));
    server.on("/api/config", HTTP_POST, std::bind(&API::handleConfig, this));
  }

  server.on("/api/stats", HTTP_GET, std::bind(&API::handleStats, this));

  server.begin();
};

void API::handleScan()
{
  String response;
  serializeJson(WiFiUtil::scanNetwork(), response);
  server.send(200, "application/json", response);
}

void API::handleConfig()
{
  DynamicJsonDocument body(400);

  deserializeJson(body, server.arg("plain"));

  String ssid = body["ssid"];
  String password = body["password"];

  DEBUG_PRINT(ssid);
  DEBUG_PRINT(password);


  if (WiFiUtil::testWifi(ssid, password)) 
  {
    String key = body["key"];
    String secret = body["secret"];
    String id = body["id"];

    DEBUG_PRINT(key);
    DEBUG_PRINT(secret);
    DEBUG_PRINT(id);


    data.saveSSID(ssid);
    data.savePassword(password);
    data.saveAppKey(key);
    data.saveAppSecret(secret);
    data.saveSwitchID(id);

    server.send(200);

    ESP.restart();
  }
  else
  {
    server.send(401);
    WiFi.mode(WIFI_AP);
  }
}

void API::handleReset()
{
  String token = server.header("token");

  DEBUG_PRINT(token);

  ESP.wdtDisable();

  String message = Crypto.decrypt(token);

  ESP.wdtEnable(1000);

  DEBUG_PRINT(message);

  if (message.equals("reset"))
  {
    // data.erase();

    server.send(200);

    ESP.restart();
  }
  else
  {
    server.send(401);
  }
}

void API::handleStats()
{
  DynamicJsonDocument doc(200);
  JsonObject root = doc.to<JsonObject>();

  root["freeHeap"] = ESP.getFreeHeap();
  root["heapFragmentation"] = ESP.getHeapFragmentation();

  String response;
  serializeJson(doc, response);

  server.send(200, "application/json", response);
}

void API::run()
{
  server.handleClient();
}