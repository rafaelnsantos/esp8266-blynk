#include "Arduino.h"

#include "OTAEEPROM.h"

// SSID = 0 to 31
// PASS = 32 to 63
// BLYNK = 64 to 99

OTAEEPROM::OTAEEPROM()
{
	Serial.println("initializing eeprom");
	EEPROM.begin(512); //Initialasing EEPROM
}

void OTAEEPROM::saveSSID(String ssid)
{
	Serial.println("writing eeprom ssid:");
	save(ssid, 0, 32);
}

void OTAEEPROM::savePassword(String password)
{
	Serial.println("writing eeprom pass:");
	save(password, 32, 64);
}

void OTAEEPROM::saveAuth(String auth)
{
	Serial.println("writing eeprom blynk:");
	save(auth, 64, 100);
	EEPROM.commit();
}

String OTAEEPROM::getSSID()
{
	String ssid = read(0, 32);

	Serial.print("SSID: ");
	Serial.println(ssid);

	return ssid;
}

String OTAEEPROM::read(int init, int end){
	char c;
	int i;

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

	for (int i = 0; i < value.length(); ++i)
	{
		EEPROM.write(init + i, value[i]);
		Serial.print("Wrote: ");
		Serial.println(value[i]);
	}
}

String OTAEEPROM::getPassword()
{
	String pass = read(32, 64);

	Serial.print("Password: ");
	Serial.println(pass);
	return pass;
}

String OTAEEPROM::getAuth()
{
	String auth_token = read(64, 100);

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
