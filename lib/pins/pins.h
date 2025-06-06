#ifndef pins_h
#define pins_h

#include <Arduino.h>

// Pin definitions
const int ir_sens1 = 2;
const int ir_led1 = 3;
const int green_led = 4;
const int red_led = 5;
const int ir_sens2 = 6;
const int ir_led2 = 7;
const int pin8 = 8;
const int pin9 = 9;
const int pin10 = 10;
const int pin12 = 12;
const int pin13 = 13;

const int ir_sens1_mode = INPUT;
const int ir_led1_mode = OUTPUT;
const int green_led_mode = OUTPUT;
const int red_led_mode = OUTPUT;
const int ir_sens2_mode = OUTPUT;
const int ir_led2_mode = OUTPUT;
const int pin8_mode = OUTPUT;
const int pin9_mode = OUTPUT;
const int pin10_mode = OUTPUT;
const int pin12_mode = OUTPUT;
const int pin13_mode = OUTPUT;

const int pins[] = {
    ir_sens1, ir_led1, green_led, red_led, ir_sens2, ir_led2, pin8, pin9, pin10, pin12, pin13
};
const int modes[] = {
    ir_sens1_mode, ir_led1_mode, green_led_mode, red_led, ir_sens2_mode, ir_led2_mode, pin8_mode, pin9_mode, pin10_mode, pin12_mode, pin13_mode
};

#endif
