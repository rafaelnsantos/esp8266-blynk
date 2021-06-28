// from https://www.element14.com/community/community/arduino/arduino-tutorials/blog/2014/06/05/a-non-blocking-delay

#include "Delay.h"  

void NonBlockDelay::Delay (unsigned long t)  
{  
  iTimeout = millis() + t;  
  return;  
};  
bool NonBlockDelay::Timeout (void)  
{  
  return (iTimeout < millis());  
}  
unsigned long NonBlockDelay::Time(void)  
 {  
   return iTimeout;  
 }  
