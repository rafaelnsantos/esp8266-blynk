#include "Debugger.h"

Debugger Debug;

void Debugger::begin()
{
#ifdef DEBUG
    Serial.begin(9600, SERIAL_8N1, SERIAL_TX_ONLY);
#endif

#ifdef DEBUG_WS
    webSocket.begin();
#endif
}

void Debugger::run()
{
#ifdef DEBUG_WS
    webSocket.loop();
#endif
}


#ifdef DEBUG_WS
void Debugger::print(String str)
{
    webSocket.broadcastTXT(str);
}

void Debugger::print(int i)
{
    String msg = String(i);
    print(msg);
}
#endif