#include <Arduino.h> // Include Arduino library for basic functions
#include <pins.h> // custom pins
#include <startup.h> // custom startup class

//display libs
#include <Adafruit_GFX.h> // to render sapes and text
#include <Adafruit_SSD1331.h> // SSD1331 OLED display driver library
#include <SPI.h> // SPI library for communication with the display

// Define SPI pins for SSD1331
#define SCLK 13 // SPI clock pin HAS TO BE PIN 13 ON ARDUINO UNO
#define MOSI 11 // SPI data pin HAS TO BE PIN 11 ON ARDUINO UNO
#define CS   10 // Chip select pin for the display
#define DC   8 // Data/Command pin for the display
#define RST  9 // Reset pin for the display

// Screen dimensions
#define SCREEN_WIDTH 96
#define SCREEN_HEIGHT 64

Adafruit_SSD1331 display = Adafruit_SSD1331(CS, DC, RST); // Create an instance of the display

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
	display.setTextColor(0xFFFF); // white in hexadecimal
	display.setCursor(0, 0); // need to set crusor position before printing
	display.println("Starting..."); // prints just like Serial.println

    int size = sizeof(pins) / sizeof(pins[0]); // calculate the size of the pins array
    Startup startup(pins, modes, size); // initialise custom startup class with pins and modes
    startup.boot(); // Call the boot method
	}

unsigned long messageStartTime = 0;
bool messageActive = false;
String messageToShow = "";

void loop() {	
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