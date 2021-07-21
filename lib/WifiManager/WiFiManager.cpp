#include "WiFiManager.h"
#include <BlynkSimpleEsp8266.h>

void WiFiManager::begin()
{
  connected = testWifi();

  char hostString[16] = {0};
  sprintf(hostString, "ESP_%06X", ESP.getChipId());

  Debugger::logln(hostString);

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
  Debugger::logln("Waiting for Wifi to connect");

  WiFi.begin(ssid, password);
  while (c < 20)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    Debugger::log("*");
    c++;
  }
  Debugger::logln("");
  Debugger::logln("Connect timed out");
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
                     { Debugger::logln("Inicio..."); });
  ArduinoOTA.onEnd([]()
                   { Debugger::logln("nFim!"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        { Debugger::logln(progress / (total / 100)); });
  ArduinoOTA.onError([](ota_error_t error)
                     { Debugger::logln(error); });

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
    Debugger::logln("Error setting up MDNS responder!");
  }
}

bool WiFiManager::isConnected()
{
  return connected;
}