#include "Arduino.h"

#include "OTAEEPROM.h"

OTAEEPROM::OTAEEPROM()
{
	Serial.println("initializing eeprom");
	EEPROM.begin(512); //Initialasing EEPROM
}

void OTAEEPROM::saveSSID(String ssid)
{
	Serial.println("writing eeprom ssid:");
	for (int i = 0; i < ssid.length(); ++i)
	{
		EEPROM.write(i, ssid[i]);
		Serial.print("Wrote: ");
		Serial.println(ssid[i]);
	}
}

void OTAEEPROM::savePassword(String password)
{
	Serial.println("writing eeprom pass:");
	for (int i = 0; i < password.length(); ++i)
	{
		EEPROM.write(32 + i, password[i]);
		Serial.print("Wrote: ");
		Serial.println(password[i]);
	}
}

void OTAEEPROM::saveAuth(String auth)
{
	Serial.println("writing eeprom auth token:");
	for (int i = 0; i < auth.length(); ++i)
	{
		EEPROM.write(64 + i, auth[i]);
		Serial.print("Wrote: ");
		Serial.println(auth[i]);
	}
	EEPROM.commit();
}

String OTAEEPROM::getSSID()
{
	String ssid = "";
	for (int i = 0; i < 32; ++i)
	{
		ssid += char(EEPROM.read(i));
	}
	Serial.print("SSID: ");
	Serial.println(ssid);

	return ssid;
}

String OTAEEPROM::getPassword()
{
	String pass = "";
	for (int i = 32; i < 64; ++i)
	{
		pass += char(EEPROM.read(i));
	}

	Serial.print("Password: ");
	Serial.println(pass);
	return pass;
}

String OTAEEPROM::getAuth()
{
	String auth_token = "";
	for (int i = 64; i < 100; ++i)
	{
		auth_token += char(EEPROM.read(i));
	}
	Serial.print("Auth Token: ");
	Serial.println(auth_token);
	return auth_token;
}

void OTAEEPROM::erase(boolean commit)
{
	// EEPROM.begin(512); //Initialasing EEPROM
	Serial.println("Erasing...");
	Serial.println("clearing eeprom");
	for (int i = 0; i < 100; ++i)
	{
		EEPROM.write(i, 0);
	}
	if (commit)
	{
		EEPROM.commit();
	}
}
