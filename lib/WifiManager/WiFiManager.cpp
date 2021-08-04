#include "WiFiManager.h"

WiFiManager wifi;

bool WiFiManager::begin()
{
  data.begin();
  Debug.begin();

  String ssid = data.getSSID();
  String password = data.getPassword();

  connected = testWifi(ssid, password);

  char hostString[16] = {0};
  sprintf(hostString, "ESP_%06X", ESP.getChipId());

  DEBUG_PRINT(hostString);

  if (connected)
  {
    setupOTAUpdate();
    setupMDNS(hostString);
  }
  else
  {
    setupAP(hostString, "");
  }

  api.begin(connected);

  return connected;
}

void WiFiManager::run()
{
  api.run();
  Debug.run();

  if (connected)
  {
    ArduinoOTA.handle();
    MDNS.update();
  }

  static unsigned long last = millis();
  if (millis() - last > 5000) {
    last = millis();
    connected = WiFi.status() == WL_CONNECTED;
  }
}

void WiFiManager::setupAP(String ssid, String password)
{
  WiFi.mode(WIFI_AP_STA);

  delay(100);

  WiFi.softAP(ssid, password);
}

bool WiFiManager::testWifi(String ssid, String password)
{
  if (ssid == "")
    return false;

  int c = 0;
  DEBUG_PRINT("Waiting for Wifi to connect");

  WiFi.begin(ssid, password);
  while (c < 20)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    DEBUG_PRINT("*");
    c++;
  }
  DEBUG_PRINT("Connect timed out");
  return false;
}

void WiFiManager::setupOTAUpdate()
{
  ArduinoOTA.onStart([]()
                     { DEBUG_PRINT("Inicio..."); });
  ArduinoOTA.onEnd([]()
                   { DEBUG_PRINT("nFim!"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        { DEBUG_PRINT(progress / (total / 100)); });
  ArduinoOTA.onError([](ota_error_t error)
                     { DEBUG_PRINT(error); });

  ArduinoOTA.begin();
}

void WiFiManager::setupMDNS(String hostname)
{
  if (MDNS.begin(hostname))
  {
    MDNS.addService("esp", "tcp", 8266);
  }
  else
  {
    DEBUG_PRINT("Error setting up MDNS responder!");
  }
}

bool WiFiManager::isConnected()
{
  return connected;
}