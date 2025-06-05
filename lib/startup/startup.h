#ifndef startup_h
#define startup_h
#include <Arduino.h>

class Startup {
public:
    Startup(const int* pins, const int* modes, int size);
    void boot();
private:
    static const int MAX_SIZE = 20;
    int _pins[MAX_SIZE];
    int _modes[MAX_SIZE];
    int _size;
};

#endif
