#include <Arduino.h>
#include <pins.h>
#include <dice.h>
#include <clear.h>

Dice::Dice() {
    // No initialization needed for now
}

void Dice::face(int face) {
    Clear clear;
    clear.clear(); // Clear all LEDs before turning on new ones

    // Turn on LEDs for the specified face
    // Example: Turn on the yellow LED for face 1
    switch (face) {
        case 1:
            digitalWrite(white_led6, HIGH);
            break;
        case 2:
            digitalWrite(blue_led, HIGH);
            digitalWrite(yellow_led, HIGH);
            break;
        case 3:
            digitalWrite(white_led6, HIGH);
            digitalWrite(blue_led, HIGH);
            digitalWrite(yellow_led, HIGH);
            break;
        case 4:
            digitalWrite(blue_led, HIGH);
            digitalWrite(yellow_led, HIGH);
            digitalWrite(red_led, HIGH);
            digitalWrite(green_led, HIGH);
            break;
        case 5:
            digitalWrite(white_led6, HIGH);
            digitalWrite(blue_led, HIGH);
            digitalWrite(yellow_led, HIGH);
            digitalWrite(red_led, HIGH);
            digitalWrite(green_led, HIGH);
            break;
        case 6:
            digitalWrite(white_led7, HIGH);
            digitalWrite(white_led8, HIGH);
            digitalWrite(blue_led, HIGH);
            digitalWrite(yellow_led, HIGH);
            digitalWrite(red_led, HIGH);
            digitalWrite(green_led, HIGH);
            break;
        default:
            // Handle invalid face values (optional)
            break;
    }
}