#include <Arduino.h>

#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <LittleFS.h>

class LittleFSWebServer
{
public:
  void begin();

private:
  void _setupFS();
  void _setupRoutes();
};
