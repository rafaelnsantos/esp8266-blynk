#include "Data.h"

Data data;

void Data::begin()
{
	if (!LittleFS.begin())
	{
		DEBUG_PRINT("error opening file system");
	}
}

void Data::saveSSID(String ssid)
{
	DEBUG_PRINT("writing ssid");
	save(ssid, "/ssid.txt");
}

void Data::savePassword(String password)
{
	DEBUG_PRINT("writing pass");
	save(password, "/password.txt");
}

void Data::saveName(String name)
{
	DEBUG_PRINT("writing name");
	save(name, "/name.txt");
}

String Data::getName()
{
	DEBUG_PRINT("name");

	return read("/name.txt");
}

String Data::getSSID()
{
	DEBUG_PRINT("SSID");

	return read("/ssid.txt");
}

String Data::read(String file)
{
	File rFile = LittleFS.open(file, "r");
	if (!rFile)
	{
		DEBUG_PRINT("error opening file");
		return "";
	}
	String content = rFile.readStringUntil('\r');
	DEBUG_PRINT(content);
	rFile.close();
	return content;
}

void Data::save(String value, String file)
{
	File rFile = LittleFS.open(file, "w+");
	if (!rFile)
	{
		DEBUG_PRINT("error opening file");
	}
	else
	{
		rFile.println(value);
		DEBUG_PRINT("WROTE");
		DEBUG_PRINT(value);
	}
	rFile.close();
}

String Data::getPassword()
{
	DEBUG_PRINT("Password");
	return read("/password.txt");
}

void Data::erase()
{
	DEBUG_PRINT("clearing data");
	saveSSID("");
	savePassword("");

	saveAppKey("");
	saveAppSecret("");
	saveSwitchID("");
	
	saveName("");
}

String Data::getAppKey()
{
	DEBUG_PRINT("App key");
	return read("/key.txt");
}

String Data::getAppSecret()
{
	DEBUG_PRINT("App Secret");
	return read("/secret.txt");
}

String Data::getSwitchID()
{
	DEBUG_PRINT("Switch ID");
	return read("/id.txt");
}

void Data::saveAppKey(String key)
{
	DEBUG_PRINT("writing key");
	save(key, "/key.txt");
}

void Data::saveAppSecret(String secret)
{
	DEBUG_PRINT("writing secret");
	save(secret, "/secret.txt");
}

void Data::saveSwitchID(String id)
{
	DEBUG_PRINT("writing id");
	save(id, "/id.txt");
}


void Data::saveRelay(bool state)
{
	DEBUG_PRINT("writing relay");
	save(state ? "true" : "false", "/relay.txt");
}

bool Data::getRelay()
{
	DEBUG_PRINT("relay");
	return read("/relay.txt").equals("true");
}