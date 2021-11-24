#include "WiFiUtil.h"

bool WiFiUtil::testWifi(String ssid, String password)
{
  int c = 0;

  DEBUG_PRINT("Waiting for Wifi to connect");

  WiFi.mode(WIFI_AP_STA);

  WiFi.begin(ssid, password);

  while (wifi_station_get_connect_status() == STATION_CONNECTING && c < 10)
  {
    DEBUG_PRINT(".");
    delay(1000);
    c++;
  }

  int status = wifi_station_get_connect_status();

  // if (status != STATION_GOT_IP)
  //   WiFi.mode(WIFI_AP);

  return status == STATION_GOT_IP;
}

DynamicJsonDocument parseNetworks(int networksFound)
{
  DynamicJsonDocument doc(400);
  JsonObject root = doc.to<JsonObject>();
  JsonArray connections = root.createNestedArray("connections");

  for (int i = 0; i < networksFound; ++i)
  {
    JsonObject connection = connections.createNestedObject();
    connection["name"] = WiFi.SSID(i);
    connection["signal"] = WiFi.RSSI(i);
    connection["encryption"] = WiFi.encryptionType(i);
  }

  return doc;
}

void WiFiUtil::scanNetworkAsync(ScanCallback callback)
{
  WiFi.scanNetworksAsync([callback](int networksFound)
                         { callback(parseNetworks(networksFound)); });
}

DynamicJsonDocument WiFiUtil::scanNetwork()
{
  return parseNetworks(WiFi.scanNetworks());
}
