#include <Arduino.h>
#include "Networking.h"

TaskHandle_t NetworkTaskHandle;

void setup() {
	Serial.begin(115200);
	// Set up Light
	xTaskCreate(
		Networking::networkingTask,
		"Networking",
		256,
		NULL,
		2,
		&NetworkTaskHandle
	);
	// Start web server
	// Set up to receive data
}

void loop() {
	// Listen for incoming data
}