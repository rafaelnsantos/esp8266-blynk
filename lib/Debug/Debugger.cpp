#include "Debugger.h"

void Debugger::begin()
{
#ifdef DEBUG
    Serial.begin(9600);
#endif
}

void Debugger::logln()
{
#ifdef DEBUG
    Serial.print("\r\n");
#endif
}

void Debugger::logln(const String &s)
{
#ifdef DEBUG
    Serial.println(s);
#endif
}

void Debugger::logln(const char c[])
{
#ifdef DEBUG
    Serial.println(c);
#endif
}

void Debugger::logln(char c)
{
#ifdef DEBUG
    Serial.println(c);
#endif
}

void Debugger::logln(unsigned char b, int base)
{
#ifdef DEBUG
    Serial.println(b, base);
#endif
}

void Debugger::logln(int num, int base)
{
#ifdef DEBUG
    Serial.println(num, base);
#endif
}

void Debugger::logln(unsigned int num, int base)
{
#ifdef DEBUG
    Serial.println(num, base);
#endif
}

void Debugger::logln(long num, int base)
{
#ifdef DEBUG
    Serial.println(num, base);
#endif
}

void Debugger::logln(unsigned long num, int base)
{
#ifdef DEBUG
    Serial.println(num, base);
#endif
}

void Debugger::logln(long long num, int base)
{
#ifdef DEBUG
    Serial.println(num, base);
#endif
}

void Debugger::logln(unsigned long long num, int base)
{
#ifdef DEBUG
    Serial.println(num, base);
#endif
}

void Debugger::logln(double num, int digits)
{
#ifdef DEBUG
    Serial.println(num, digits);
#endif
}

void Debugger::log(const String &s)
{
#ifdef DEBUG
    Serial.print(s);
#endif
}

void Debugger::log(const char str[])
{
#ifdef DEBUG
    Serial.print(str);
#endif
}

void Debugger::log(char c)
{
#ifdef DEBUG
    Serial.print(c);
#endif
}

void Debugger::log(unsigned char b, int base)
{
#ifdef DEBUG
    Serial.print(b, base);
#endif
}

void Debugger::log(int n, int base)
{
#ifdef DEBUG
    Serial.print(n, base);
#endif
}

void Debugger::log(unsigned int n, int base)
{
#ifdef DEBUG
    Serial.print(n, base);
#endif
}

void Debugger::log(long n, int base)
{
#ifdef DEBUG
    Serial.print(n, base);
#endif
}

void Debugger::log(unsigned long n, int base)
{
#ifdef DEBUG
    Serial.print(n, base);
#endif
}

void Debugger::log(long long n, int base)
{
#ifdef DEBUG
    Serial.print(n, base);
#endif
}

void Debugger::log(unsigned long long n, int base)
{
#ifdef DEBUG
    Serial.print(n, base);
#endif
}

void Debugger::log(double n, int digits)
{
#ifdef DEBUG
    Serial.print(n, digits);
#endif
}
