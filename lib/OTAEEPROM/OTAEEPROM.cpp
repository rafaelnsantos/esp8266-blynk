#include "OTAEEPROM.h"

// SSID = 0 to 31
// PASS = 32 to 63
// BLYNK = 64 to 99
// NAME = 100 to 131

OTAEEPROM eeprom;

void OTAEEPROM::saveSSID(String ssid)
{
	DEBUG_PRINT("writing eeprom ssid:");
	save(ssid, 0, 32);
}

void OTAEEPROM::savePassword(String password)
{
	DEBUG_PRINT("writing eeprom pass:");
	save(password, 32, 64);
}

void OTAEEPROM::saveAuth(String auth)
{
	DEBUG_PRINT("writing eeprom blynk:");
	save(auth, 64, 100);
}

void OTAEEPROM::saveName(String name)
{
	DEBUG_PRINT("writing eeprom name:");
	save(name, 100, 132);
}

String OTAEEPROM::getName()
{
	String name = read(100, 132);

	DEBUG_PRINT("name: ");
	DEBUG_PRINT(name);

	return name;
}

String OTAEEPROM::getSSID()
{
	String ssid = read(0, 32);

	DEBUG_PRINT("SSID: ");
	DEBUG_PRINT(ssid);

	return ssid;
}

String OTAEEPROM::read(int init, int end)
{
	char c;
	uint8 i;

	String aux = "";

	for (i = init, c = char(EEPROM.read(i)); i < end && c != '\0'; ++i, c = char(EEPROM.read(i)))
	{
		aux += c;
	}

	return aux;
}

void OTAEEPROM::save(String value, int init, int end)
{
	for (int i = init; i < end; ++i)
	{
		EEPROM.write(i, 0);
	}

	for (uint8 i = 0; i < value.length(); ++i)
	{
		EEPROM.write(init + i, value[i]);
		DEBUG_PRINT("Wrote: ");
		DEBUG_PRINT(value[i]);
	}
	EEPROM.commit();
}

String OTAEEPROM::getPassword()
{
	String pass = read(32, 64);

	DEBUG_PRINT("Password: ");
	DEBUG_PRINT(pass);
	return pass;
}

String OTAEEPROM::getAuth()
{
	String auth_token = read(64, 100);

	DEBUG_PRINT("Auth Token: ");
	DEBUG_PRINT(auth_token);
	return auth_token;
}

void OTAEEPROM::erase()
{
	DEBUG_PRINT("clearing eeprom");
	for (int i = 0; i < 132; ++i)
	{
		EEPROM.write(i, 0);
	}
	EEPROM.commit();
}
