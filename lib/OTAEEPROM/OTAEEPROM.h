#ifndef OTAEEPROM_h
#define OTAEEPROM_h

#include "Arduino.h"

#include <EEPROM.h>
#include "Debugger.h"

class OTAEEPROM
{
public:
  void erase();
  void saveSSID(String ssid);
  void savePassword(String password);
  void saveAuth(String auth);

  String getSSID();
  String getPassword();
  String getAuth();

private:
  String read(int init, int end);
  void save(String string, int init, int end);
};

extern OTAEEPROM eeprom;

#endif

