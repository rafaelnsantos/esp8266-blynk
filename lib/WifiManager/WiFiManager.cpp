#include "WiFiManager.h"
#include <BlynkSimpleEsp8266.h>

void WiFiManager::begin()
{
  EEPROM.begin(512);
  Debug.begin();

  connected = testWifi();

  char hostString[16] = {0};
  sprintf(hostString, "ESP_%06X", ESP.getChipId());

  DEBUG_PRINT(hostString);

  if (connected)
  {
    setupOTAUpdate();
    setupMDNS(hostString);
    setupBlynk();
  }
  else
  {
    setupAP(hostString, "");
  }


  api.begin(connected);
}

void WiFiManager::run()
{
  api.run();

  if (connected)
  {
    ArduinoOTA.handle();
    Blynk.run();
    MDNS.update();
  }
}

void WiFiManager::setupAP(String ssid, String password)
{
  WiFi.mode(WIFI_AP_STA);

  delay(100);

  WiFi.softAP(ssid, password);
}

bool WiFiManager::testWifi()
{
  String ssid = eeprom.getSSID();
  String password = eeprom.getPassword();
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

void WiFiManager::reset()
{
  eeprom.erase();
  ESP.reset();
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

void WiFiManager::setupBlynk()
{
  String token = eeprom.getAuth();
  token.toCharArray(blynkToken, 33);
  Blynk.config(blynkToken);
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