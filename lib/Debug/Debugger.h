#ifndef Debugger_h
#define Debugger_h

#define DEBUG
// #define DEBUG_WS

#ifdef DEBUG_WS
    #define DEBUG_PRINT(str) Debug.print(str);
    #include <WebSocketsServer.h>
#endif

#ifdef DEBUG
  #define DEBUG_PRINT(str)    \
    Serial.print(__FILE__);     \
    Serial.print(':');      \
    Serial.print(__LINE__);     \
    Serial.print(' ');      \
    Serial.println(str);
#endif

#if !defined(DEBUG) && !defined(DEBUG_WS)
  #define DEBUG_PRINT(str)
#endif

#include <Arduino.h>  

class Debugger {  
  public:
    void begin();
    void run();

  #ifdef DEBUG_WS
  void print(String str);
  void print(int i);
  Debugger(): webSocket(81) {}
  private:
    WebSocketsServer webSocket;
  #endif
};  

extern Debugger Debug;

#endif