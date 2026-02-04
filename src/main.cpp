#include <Arduino.h>
#include "Networking.h"
#include <LittleFS.h>

TaskHandle_t NetworkTaskHandle;

void setup() {
	Serial.begin(115200);
	LittleFS.begin();
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