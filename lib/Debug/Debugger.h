#ifndef Debugger_h
#define Debugger_h

// #define DEBUG

#ifdef DEBUG
  #define DEBUG_PRINT(str)    \
    Serial.print(__FILE__);     \
    Serial.print(':');      \
    Serial.print(__LINE__);     \
    Serial.print(' ');      \
    Serial.println(str);
#else
  #define DEBUG_PRINT(str)
#endif

#include <Arduino.h>  

class Debugger {  
  public:  
    void begin();
};  

extern Debugger Debug;

#endif