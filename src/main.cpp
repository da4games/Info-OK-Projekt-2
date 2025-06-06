#include <Arduino.h>
	#include <pins.h>
	#include <startup.h>
	
	//display libs
	#include <Wire.h>
	#include <Adafruit_GFX.h>
	#include <Adafruit_SSD1306.h>

	#define SCREEN_WIDTH 128 // OLED display width, in pixels
	#define SCREEN_HEIGHT 64 // OLED display height, in pixels
	#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
	Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

	unsigned long sensor1TriggerTime = 0;
	unsigned long sensor2TriggerTime = 0;
	const unsigned long timeThreshold = 1000; // 1 second threshold
	bool sensor1Triggered = false;
	bool sensor2Triggered = false;
	int movementState = 0; // 0: No movement, 1: 1->2, 2: 2->1
	const char* dirMsgNone = "No movement";
	const char* dirMsg1to2 = "Direction: 1 -> 2";
	const char* dirMsg2to1 = "Direction: 2 -> 1";
	
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
		while (true) {//debuging
			digitalWrite(ir_led1, HIGH); // Turn on IR LED
			delay(100); // Wait for 100 milliseconds
			display.clearDisplay();
			display.setCursor(0, 0);
			if (digitalRead(ir_sens1) == LOW) { // ir sensor is LOW when triggered
				display.println("IR Sensor Triggered!");
				digitalWrite(green_led, HIGH);
			}
			else {
				display.println("IR Sensor NOT Triggered");
				digitalWrite(green_led, LOW);
			}
		}//debuging

		//2 Lichtschranken, richtung der Bewegung bestimmen
		//falls zweiter Sensor nicht schnell genug nach dem ersten ausgelöst wird, dann wird der erste Sensor nicht mehr beachtet

		digitalWrite(ir_led1, HIGH); // Turn on IR LED 1
    	digitalWrite(ir_led2, HIGH); // Turn on IR LED 2
		
    	display.clearDisplay();
    	display.setCursor(0, 0);

		// Check first sensor
		if (digitalRead(ir_sens1) == LOW && !sensor1Triggered) { // Sensor 1 just triggered
			sensor1Triggered = true;
			sensor1TriggerTime = millis();
			
			if (sensor2Triggered && (sensor1TriggerTime - sensor2TriggerTime < timeThreshold)) {
				movementState = 2; // Direction: 2 -> 1
			}
		}
		
		// Check second sensor
		if (digitalRead(ir_sens2) == LOW && !sensor2Triggered) { // Sensor 2 just triggered
			sensor2Triggered = true;
			sensor2TriggerTime = millis();
			
			if (sensor1Triggered && (sensor2TriggerTime - sensor1TriggerTime < timeThreshold)) {
				movementState = 1; // Direction: 1 -> 2
			}
		}
		
		// Reset if both sensors have been triggered or timeout
		if ((sensor1Triggered && sensor2Triggered) || 
			(sensor1Triggered && millis() - sensor1TriggerTime > timeThreshold) ||
			(sensor2Triggered && millis() - sensor2TriggerTime > timeThreshold)) {
			sensor1Triggered = false;
			sensor2Triggered = false;
			if (movementState == 0) { // Check against integer state
				digitalWrite(green_led, LOW); // No complete movement detected
			} else {
				digitalWrite(green_led, HIGH); // Movement detected
				// Reset direction after a delay or keep it until next detection
				delay(1000);
				movementState = 0; // Reset state
				digitalWrite(green_led, LOW);
			}
		}
		
		// Display status
		display.println("IR Sensor Status:");
		display.print("Sensor 1: ");
		display.println(digitalRead(ir_sens1) == LOW ? "Triggered" : "Not Triggered");
		display.print("Sensor 2: ");
		display.println(digitalRead(ir_sens2) == LOW ? "Triggered" : "Not Triggered");
		if (movementState == 1) {
			display.println(dirMsg1to2);
		} else if (movementState == 2) {
			display.println(dirMsg2to1);
		} else {
			display.println(dirMsgNone);
		}
		display.display();
		
		delay(50); // Small delay to stabilize readings

	}