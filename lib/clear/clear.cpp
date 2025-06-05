#include <Arduino.h>
#include <pins.h>
#include <clear.h>

Clear::Clear() {
    // No initialization needed for now
}

void Clear::clear() {
    // Iterate through all pins and set pins with mode OUTPUT to LOW
    for (size_t i = 0; i < sizeof(pins) / sizeof(pins[0]); i++) {
        if (modes[i] == OUTPUT) {
            digitalWrite(pins[i], LOW);
        }
    }
}