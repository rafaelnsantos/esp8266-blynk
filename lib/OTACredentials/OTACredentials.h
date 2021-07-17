
#include <ESP8266WiFi.h>
#include "Arduino.h"

#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include "Delay.h"
#include "OTAEEPROM.h"
#include <ESP8266httpUpdate.h>

class credentials
{
public:
  bool credentials_get();
  void setupAP(char *softap_ssid, char *softap_pass);
  void setupST();
  void server_loops();
  String EEPROM_Config();
  void Erase_eeprom();

private:
  bool _testWifi(void);
  String ssid = "";
  String pass = "";
};
