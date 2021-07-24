#include "OTAEEPROM.h"

// SSID = 0 to 31
// PASS = 32 to 63
// BLYNK = 64 to 99

OTAEEPROM::OTAEEPROM()
{
	Debugger::logln("initializing eeprom");
	EEPROM.begin(512); //Initialasing EEPROM
}

void OTAEEPROM::saveSSID(String ssid)
{
	Debug.logln("writing eeprom ssid:");
	save(ssid, 0, 32);
	EEPROM.commit();
}

void OTAEEPROM::savePassword(String password)
{
	Debug.logln("writing eeprom pass:");
	save(password, 32, 64);
	EEPROM.commit();
}

void OTAEEPROM::saveAuth(String auth)
{
	Debug.logln("writing eeprom blynk:");
	save(auth, 64, 100);
	EEPROM.commit();
}

String OTAEEPROM::getSSID()
{
	String ssid = read(0, 32);

	Debug.log("SSID: ");
	Debug.logln(ssid);

	return ssid;
}

String OTAEEPROM::read(int init, int end){
	char c;
	uint8 i;

	String aux = "";

	for (i = init, c = char(EEPROM.read(i)); i < end && c != NULL; ++i, c = char(EEPROM.read(i)) ) {
		aux += c;
	}

	return aux;
}

void OTAEEPROM::save(String value, int init, int end) {
	for (int i = init; i < end; ++i)
	{
		EEPROM.write(i, 0);
	}

	for (uint8 i = 0; i < value.length(); ++i)
	{
		EEPROM.write(init + i, value[i]);
		Debug.log("Wrote: ");
		Debug.log(value[i]);
	}
}

String OTAEEPROM::getPassword()
{
	String pass = read(32, 64);

	Debug.log("Password: ");
	Debug.logln(pass);
	return pass;
}

String OTAEEPROM::getAuth()
{
	String auth_token = read(64, 100);

	Debug.log("Auth Token: ");
	Debug.logln(auth_token);
	return auth_token;
}

void OTAEEPROM::erase()
{
	Debug.logln("clearing eeprom");
	for (int i = 0; i < 100; ++i)
	{
		EEPROM.write(i, 0);
	}
	EEPROM.commit();
}
