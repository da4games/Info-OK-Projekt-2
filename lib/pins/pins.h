#ifndef pins_h
#define pins_h

#include <Arduino.h>

// Pin definitions
const int ir_sens = 2;
const int ir_led = 3;
const int green_led = 4;
const int pin5 = 5;
const int pin6 = 6;
const int pin7 = 7;
const int pin8 = 8;
const int pin9 = 9;
const int pin10 = 10;
const int pin12 = 12;
const int pin13 = 13;

const int ir_sens_mode = INPUT;
const int ir_led_mode = OUTPUT;
const int green_led_mode = OUTPUT;
const int pin5_mode = OUTPUT;
const int pin6_mode = OUTPUT;
const int pin7_mode = OUTPUT;
const int pin8_mode = OUTPUT;
const int pin9_mode = OUTPUT;
const int pin10_mode = OUTPUT;
const int pin12_mode = OUTPUT;
const int pin13_mode = OUTPUT;

const int pins[] = {
    ir_sens, ir_led, green_led, pin5, pin6, pin7, pin8, pin9, pin10, pin12, pin13
};
const int modes[] = {
    ir_sens_mode, ir_led_mode, green_led_mode, pin5_mode, pin6_mode, pin7_mode, pin8_mode, pin9_mode, pin10_mode, pin12_mode, pin13_mode
};

#endif
