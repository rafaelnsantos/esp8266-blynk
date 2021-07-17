#include <Arduino.h>
#include "OTACredentials.h"
#include <BlynkSimpleEsp8266.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

#define ATOMIC_FS_UPDATE

credentials Credentials;

//Variables
char auth_token[33];
bool connected_to_internet = 0;
const int Erasing_button = 0;

//Provide credentials for your ESP server
char *esp_pass = "";
char hostString[16] = {0};

//
//
// .     Add your variables
//
// .             HERE
// .
//
//

void setup()
{
  Serial.begin(115200);
  pinMode(Erasing_button, INPUT);

  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.println(t);
    delay(1000);
  }
  Serial.println(digitalRead(Erasing_button));
  // Press and hold the button to erase all the credentials
  if (digitalRead(Erasing_button) == LOW)
  {
    Credentials.Erase_eeprom();
  }
  sprintf(hostString, "ESP_%06X", ESP.getChipId());
  String auth_string = Credentials.EEPROM_Config();
  auth_string.toCharArray(auth_token, 33);

  if (Credentials.credentials_get())
  {

    Blynk.config(auth_token);
    connected_to_internet = 1;
  }
  else
  {
    Credentials.setupAP(hostString, esp_pass);
    connected_to_internet = 0;
  }

  if (connected_to_internet)
  {

    if (!MDNS.begin(hostString)) {             // Start the mDNS responder for esp8266.local
        Serial.println("Error setting up MDNS responder!");
    } else {
      MDNS.addService("esp", "tcp", 8266);
    }

    Credentials.setupST();

    ArduinoOTA.onStart([]()
                       { Serial.println("Inicio..."); });
    ArduinoOTA.onEnd([]()
                     { Serial.println("nFim!"); });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                          { Serial.printf("Progresso: %u%%r", (progress / (total / 100))); });
    ArduinoOTA.onError([](ota_error_t error)
                       {
                         Serial.printf("Erro [%u]: ", error);
                         if (error == OTA_AUTH_ERROR)
                           Serial.println("Autenticacao Falhou");
                         else if (error == OTA_BEGIN_ERROR)
                           Serial.println("Falha no Inicio");
                         else if (error == OTA_CONNECT_ERROR)
                           Serial.println("Falha na Conexao");
                         else if (error == OTA_RECEIVE_ERROR)
                           Serial.println("Falha na Recepcao");
                         else if (error == OTA_END_ERROR)
                           Serial.println("Falha no Fim");
                       });

    ArduinoOTA.begin();
    //
    //
    // .  Write the setup part of your code
    //
    // .             HERE
    // .
    //
    //
  }
}

void loop()
{
  Credentials.server_loops();

  if (connected_to_internet)
  {
    ArduinoOTA.handle();
    //
    //
    // .  Write the loop part of your code
    //
    // .             HERE
    // .
    //
    //
    Blynk.run();
  }
}