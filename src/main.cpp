#include <Arduino.h>
#include <pins.h>
#include <startup.h>

//display libs
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

// Define SPI pins for SSD1331
#define SCLK 13
#define MOSI 11
#define CS   10
#define DC   8
#define RST  9

// Screen dimensions
#define SCREEN_WIDTH 96
#define SCREEN_HEIGHT 64

Adafruit_SSD1331 display = Adafruit_SSD1331(CS, DC, RST);

unsigned long sensor1TriggerTime = 0;
unsigned long sensor2TriggerTime = 0;
const unsigned long timeThreshold = 1000; // 1 second threshold
bool sensor1Triggered = false;
bool sensor2Triggered = false;
int movementState = 0; // 0: No movement, 1: 1->2, 2: 2->1

void setup() {
	display.begin(); // Initialize SSD1331
	display.fillScreen(0x0000); // Clear screen to black for color display
	display.setTextSize(1);
	display.setTextColor(0xFFFF); // Use SSD1331 color (e.g., WHITE)
	display.setCursor(0, 0);
	display.println("Starting...");
    int size = sizeof(pins) / sizeof(pins[0]);
    Startup startup(pins, modes, size);
    startup.boot(); // Call the boot method

	// display tests

	digitalWrite(RST, LOW);  // Assert RESET (if RES pin is used)
	delay(100);
	digitalWrite(RST, HIGH); // Release RESET
	delay(100);

	// Send CLEAR command (0x25) for full screen (columns 0-95, rows 0-63)
	display.writeCommand(0x25);
	display.writeData(0x00);  // Start column
	display.writeData(0x00);  // Start row
	display.writeData(0x5F);  // End column (95 = 0x5F)
	display.writeData(0x3F);  // End row (63 = 0x3F)
	delay(10);        // Wait for command execution

	display.fillScreen(0x0000); // Clear screen to black
	display.setTextSize(1);
	display.drawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 30, 0xFFFF); // Draw a white circle
	delay(2000); // Wait for 1 second
	display.fillScreen(0x0000); // Clear screen to black again
	display.setTextColor(0x051e); //blue
	display.println("Screen test :D");
}

unsigned long messageStartTime = 0;
bool messageActive = false;
String messageToShow = "";

void loop() {
	/*
	while (true) {//debuging
		if (digitalRead(ir_sens1) == HIGH) {
			Serial.println("IR Sensor 1 not triggered");
			//digitalWrite(green_led, HIGH); // Turn on green LED
		}
		else {
			Serial.println("IR Sensor 1 triggered");
			//digitalWrite(green_led, LOW); // Turn off green LED
		}
		if (digitalRead(ir_sens2) == HIGH) {
			digitalWrite(green_led, HIGH); // Turn off green LED
			//Serial.println("IR Sensor 2 not triggered");
		}
		else {
			digitalWrite(green_led, LOW); // Turn on green LED
			//Serial.println("IR Sensor 2 triggered");
			}
  	}//debuging
	*/
	
	unsigned long now = millis();

  	// Sensor 1 triggered
  	if (digitalRead(ir_sens1) == LOW && !sensor1Triggered) {
  	  	sensor1Triggered = true;
  	  	sensor1TriggerTime = now;

  	 	if (sensor2Triggered && (sensor1TriggerTime - sensor2TriggerTime < timeThreshold)) {
  	    	movementState = 2;
  	  	}
  	}

  	// Sensor 2 triggered
  	if (digitalRead(ir_sens2) == LOW && !sensor2Triggered) {
  	  	sensor2Triggered = true;
  	  	sensor2TriggerTime = now;

  	  	if (sensor1Triggered && (sensor2TriggerTime - sensor1TriggerTime < timeThreshold)) {
  	    	movementState = 1;
  	  	}
  	}

  	// Check for new movement and interrupt "No movement" if needed
	if ((movementState == 1 || movementState == 2) &&
	    (!messageActive || messageToShow == "No movement")) {
	  	// Interrupt current message if it's just "No movement"
	  	messageToShow = (movementState == 1) ? "1 --> 2" : "2 --> 1";
	  	display.fillScreen(0x0000);
	  	display.setCursor(0, 0);
	  	display.setTextColor(0xFFFF);
	  	display.println(messageToShow);
	  	messageStartTime = now;
	  	messageActive = true;
	}

	// Show "No movement" only if no message is currently active
	if (!messageActive && movementState == 0) {
	  	messageToShow = "No movement";
	  	display.fillScreen(0x0000);
	  	display.setCursor(0, 0);
	  	display.setTextColor(0xFFFF);
	  	display.println(messageToShow);
	  	messageStartTime = now;
	  	messageActive = true;
	}

  	// Clear message after 1 second
  	if (messageActive && (now - messageStartTime > 1000)) {
  	  	display.fillScreen(0x0000);
  	  	messageActive = false;
  	}

  	// Handle LED and reset
  	if ((sensor1Triggered && sensor2Triggered) ||
  	    (sensor1Triggered && now - sensor1TriggerTime > timeThreshold) ||
  	    (sensor2Triggered && now - sensor2TriggerTime > timeThreshold)) {

  	  	sensor1Triggered = false;
  	  	sensor2Triggered = false;

  	  	if (movementState == 0) {
  	    	digitalWrite(green_led, LOW);
  	  	} else {
  	    	digitalWrite(green_led, HIGH);
  	    	movementState = 0;
  	  	}
  	}
	}