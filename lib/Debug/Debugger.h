#ifndef Debugger_h
#define Debugger_h

// #define DEBUG

#include <Arduino.h>  

class Debugger {  
  public:  
    static void begin();

    static void logln(void);
    static void logln(const String &s);
    static void logln(const char c[]);
    static void logln(char c);
    static void logln(unsigned char b, int base);
    static void logln(int num, int base);
    static void logln(unsigned int num, int base);
    static void logln(long num, int base);
    static void logln(unsigned long num, int base);
    static void logln(long long num, int base);
    static void logln(unsigned long long num, int base);
    static void logln(double num, int digits);

    static void log(const String &s);
    static void log(const char str[]);
    static void log(char c);
    static void log(unsigned char b, int base);
    static void log(int n, int base);
    static void log(unsigned int n, int base);
    static void log(long n, int base);
    static void log(unsigned long n, int base);
    static void log(long long n, int base);
    static void log(unsigned long long n, int base);
    static void log(double n, int digits);
};  

#endif