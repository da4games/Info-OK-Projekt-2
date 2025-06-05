	
	#include <Arduino.h>
	#include <pins.h>
	#include <startup.h>
	#include <clear.h>
	
	//display libs
	#include <Wire.h>
	#include <Adafruit_GFX.h>
	#include <Adafruit_SSD1306.h>

	#define SCREEN_WIDTH 128 // OLED display width, in pixels
	#define SCREEN_HEIGHT 64 // OLED display height, in pixels
	#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
	Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

	void setup() {
		display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize with the I2C addr 0x3C (for the 128x64)
		display.clearDisplay();
		display.setTextSize(1);
		display.setTextColor(SSD1306_WHITE);
		display.setCursor(0, 0);
		display.println("Starting...");
		display.display();
	    int size = sizeof(pins) / sizeof(pins[0]);
	    Startup startup(pins, modes, size);
	    startup.boot(); // Call the boot method
	}

	void loop() {
		digitalWrite(ir_led, HIGH); // Turn on IR LED
		delay(100); // Wait for 100 milliseconds
		if (digitalRead(ir_sens) == LOW) { // ir sensor is LOW when triggered
			digitalWrite(green_led, HIGH);
		}
		else {digitalWrite(green_led, LOW);}
	}