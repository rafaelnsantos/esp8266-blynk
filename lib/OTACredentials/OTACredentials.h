
#include <ESP8266WiFi.h>
#include "Arduino.h"

#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include "Delay.h"
#include "LittleFSWebServer.h"
#include "OTAEEPROM.h"

class credentials
{
public:
  bool credentials_get();
  void setupAP(char *softap_ssid, char *softap_pass);
  void server_loops();
  String EEPROM_Config();
  void Erase_eeprom();

private:
  LittleFSWebServer webServer;
  bool _testWifi(void);
  void _launchWeb(void);
  String ssid = "";
  String pass = "";
};
