#ifndef DATA_H
#define DATA_H

#include "Arduino.h"

#include "Debugger.h"
#include "LittleFS.h"

class Data
{
public:
  void begin();
  void erase();
  void saveSSID(String ssid);
  void savePassword(String password);
  void saveAuth(String auth);
  void saveName(String name);
  void saveAppKey(String appKey);
  void saveAppSecret(String appSecret);
  void saveSwitchID(String awitchID);

  String getSSID();
  String getPassword();
  String getAuth();
  String getName();
  String getAppKey();
  String getAppSecret();
  String getSwitchID();

private:
  String read(String file);
  void save(String string, String file);
};

extern Data data;

#endif

