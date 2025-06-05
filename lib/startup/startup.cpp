#include "Arduino.h"
#include "startup.h"

Startup::Startup(const int* pins, const int* modes, int size) {
    _size = size > MAX_SIZE ? MAX_SIZE : size; // Limit size to MAX_SIZE
    for (int i = 0; i < _size; i++) {
        _pins[i] = pins[i];
        _modes[i] = modes[i];
    }
}

void Startup::boot() {
    Serial.begin(9600);
    delay(2000);
    Serial.println("Starting");
    Serial.println(F("  /$$$$$$                                      /$$$$$$$                       /$$                                  "));
    Serial.println(F(" /$$__  $$                                    | $$__  $$                     | $$                                  "));
    Serial.println(F("| $$  \\__/  /$$$$$$   /$$$$$$  /$$   /$$      | $$  \\ $$ /$$$$$$   /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$   /$$$$$$$"));
    Serial.println(F("| $$       /$$__  $$ /$$__  $$| $$  | $$      | $$$$$$$/|____  $$ /$$_____/|_  $$_/   /$$__  $$ /$$__  $$ /$$_____/"));
    Serial.println(F("| $$      | $$  \\ $$| $$  \\ $$| $$  | $$      | $$____/  /$$$$$$$|  $$$$$$   | $$    | $$$$$$$$| $$  \\__/|  $$$$$$ "));
    Serial.println(F("| $$    $$| $$  | $$| $$  | $$| $$  | $$      | $$      /$$__  $$ \\____  $$  | $$ /$$| $$_____/| $$       \\____  $$"));
    Serial.println(F("|  $$$$$$/|  $$$$$$/| $$$$$$$/|  $$$$$$$      | $$     |  $$$$$$$ /$$$$$$$/  |  $$$$/|  $$$$$$$| $$       /$$$$$$$/"));
    Serial.println(F(" \\______/  \\______/ | $$____/  \\____  $$      |__/      \\_______/|_______/    \\___/   \\_______/|__/      |_______/ "));
    Serial.println(F("                    | $$       /$$  | $$                                                                           "));
    Serial.println(F("                    | $$      |  $$$$$$/                                                                           "));
    Serial.println(F("                    |__/       \\______/                                                                            "));
    Serial.println(F(""));
    Serial.println(F("Copy Pasters Software Inc."));
    Serial.println(F("=============================================="));
    Serial.println(F("starting initialisation"));
    
    // Initialize pins
    for (int i = 0; i < _size; i++) {
        pinMode(_pins[i], _modes[i]);
        Serial.print(F("Set pin "));
        Serial.print(_pins[i]);
        Serial.print(F(" as "));
        Serial.println(_modes[i] == INPUT ? "INPUT" : "OUTPUT");
    }

    Serial.println(F("initialisation complete"));
    Serial.println(F("=============================================="));
}