#include <Arduino.h>
#include "Networking.h"
#include <LittleFS.h>

TaskHandle_t NetworkTaskHandle;

void setup() {
	Serial.begin(115200);
	#ifdef ESP32
		LittleFS.begin(true);
	#else
		LittleFS.begin();
	#endif
	// Set up Light
	xTaskCreate(
		Networking::networkingTask,
		"Networking",
		4096,
		NULL,
		2,
		&NetworkTaskHandle
	);
	// Set up to receive data
}

void loop() {
	// Listen for incoming data
}