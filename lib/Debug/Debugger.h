#ifndef Debugger_h
#define Debugger_h

// #define DEBUG

#include <Arduino.h>  

class Debugger {  
  public:  
    void begin();

    void logln(void);
    void logln(const String &s);
    void logln(const char c[]);
    void logln(char c);
    void logln(unsigned char b, int base);
    void logln(int num, int base);
    void logln(unsigned int num, int base);
    void logln(long num, int base);
    void logln(unsigned long num, int base);
    void logln(long long num, int base);
    void logln(unsigned long long num, int base);
    void logln(double num, int digits);

    void log(const String &s);
    void log(const char str[]);
    void log(char c);
    void log(unsigned char b, int base);
    void log(int n, int base);
    void log(unsigned int n, int base);
    void log(long n, int base);
    void log(unsigned long n, int base);
    void log(long long n, int base);
    void log(unsigned long long n, int base);
    void log(double n, int digits);
};  

extern Debugger Debug;

#endif