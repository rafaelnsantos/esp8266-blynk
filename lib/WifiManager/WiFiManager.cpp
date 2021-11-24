#include "WiFiManager.h"

WiFiManager wifi;

bool WiFiManager::begin()
{
  String ssid = data.getSSID();
  String password = data.getPassword();

  if (ssid == NULL || ssid.length() == 0 || ssid.equals("")) {
    connected = false;
    setupAP();
  } else {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED) {
      delay(1000);
      DEBUG_PRINT(".");
    }
    connected = true;
  }

  api.begin(connected);

  return connected;
}

void WiFiManager::run()
{
  api.run();

  static unsigned long last = millis();
  if (millis() - last > 5000) {
    last = millis();
    connected = WiFi.status() == WL_CONNECTED;
  }
}

void WiFiManager::setupAP()
{
  char hostString[16] = {0};

  sprintf(hostString, "ESP_%06X", ESP.getChipId());

  DEBUG_PRINT(hostString);

  WiFi.softAP(hostString);
}

bool WiFiManager::isConnected()
{
  return connected;
}