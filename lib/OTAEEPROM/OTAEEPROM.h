#include "Arduino.h"

#include <EEPROM.h>

class OTAEEPROM
{
public:
  OTAEEPROM();
  void erase(boolean commit);
  void saveSSID(String ssid);
  void savePassword(String password);
  void saveAuth(String auth);

  String getSSID();
  String getPassword();
  String getAuth();
};

