#include "Debugger.h"

Debugger Debug;

void Debugger::begin()
{
#ifdef DEBUG
    Serial.begin(9600, SERIAL_8N1, SERIAL_TX_ONLY);
#endif
}