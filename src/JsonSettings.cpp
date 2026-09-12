/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/JsonSettings.cpp                                              *
*                                                                              *
* Created: 2026-09-12                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#include "JsonSettings.h"

#include "light/Light.h"

void updateSettings() {
	JsonObject lightObject = doc["light"].as<JsonObject>();
	JsonObject networkObject = doc["network"].as<JsonObject>();

	light::moduleIndex = lightObject["moduleIndex"];
	for (auto& i : light::colorChan) {
		i = -1;
	}
	copyArray(lightObject["colorChan"], light::colorChan);
	for (auto& i : light::moduleGPIO) {
		i = -1;
	}
	copyArray(lightObject["moduleGPIO"], light::moduleGPIO);



}

void updateJson() {

}

void saveSettingsToFile(String filePath) {
	updateJson();

}

void updateSettingsFromFile(String filePath) {


	updateSettings();
}

void updateSettingsFromJson(JsonObject json) {

	updateSettings();
}