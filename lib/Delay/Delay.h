#include <Arduino.h>  

class NonBlockDelay {  
  private:
    unsigned long iTimeout;  
  public:  
    void Delay (unsigned long);  
    bool Timeout (void);  
    unsigned long Time(void);  
};  
