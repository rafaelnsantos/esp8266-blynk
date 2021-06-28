#include "Arduino.h"
#include "LittleFSWebServer.h"

AsyncWebServer server(80);

// This is the function which will be called when an invalid page is called from client
void notFound(AsyncWebServerRequest *request)
{
	request->send(404, "text/plain", "Not found");
}

void LittleFSWebServer::_setupFS()
{
	if (!LittleFS.begin())
	{
		Serial.println("An Error has occurred while mounting LittleFS");
		return;
	}
}

void LittleFSWebServer::_setupRoutes()
{
	server.on("/", [](AsyncWebServerRequest *request)
			  { request->send(LittleFS, "/index.html", "text/html"); });

	// Route to load bundle.js file
	server.on("/bundle.js", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(LittleFS, "/bundle.js", "text/javascript"); });

	// Route to load polyfills.js file
	server.on("/polyfills.js", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(LittleFS, "/polyfills.js", "text/javascript"); });

	// Route to load style.css file
	server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(LittleFS, "/style.css", "text/css"); });

	// Route to load style.css file
	server.on("/static/media/Rotobo-300.a29236e0.woff2", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(LittleFS, "/static/media/Roboto-300.a29236e0.woff2", "font/woff2"); });

	// Route to load static/media file
	server.on("/static/media/Roboto-400.4673b453.woff2", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(LittleFS, "/static/media/Roboto-400.4673b453.woff2", "font/woff2"); });

	// Route to load static/media/ file
	server.on("/static/media/Roboto-500.86988841.woff2", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(LittleFS, "/static/media/Roboto-500.86988841.woff2", "font/woff2"); });

	// Route to load static/media/ file
	server.on("/static/media/Roboto-700.bcf37d66.woff2", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(LittleFS, "/static/media/Roboto-700.bcf37d66.woff2", "font/woff2"); });


	server.onNotFound(notFound);
}

void LittleFSWebServer::begin()
{
	_setupFS();

	_setupRoutes();

	server.begin();
}
