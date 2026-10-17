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

JsonDocument settingsDoc;

void jsonMerge(JsonObject dst, JsonObjectConst src, JsonObjectConst keyref) {
	for (JsonPairConst kvp : src) {
		if (keyref[kvp.key()]) {
			dst[kvp.key()] = kvp.value();
		}
	}
}

void mergeSettings(JsonObject dst, JsonObjectConst src) {
	for (JsonPair kvp : settingsDoc.as<JsonObject>()) {
		jsonMerge(dst[kvp.key()], src[kvp.key()], settingsDoc[kvp.key()]);
	}

}

void reloadSettings() {
	File defaultSettings = LittleFS.open(DEFAULTSETTINGSFILE);
	deserializeJson(settingsDoc, defaultSettings);
	defaultSettings.close();
	File userSettings = LittleFS.open(USERSETTINGSFILE);
	JsonDocument userSettingsDoc;
	deserializeJson(userSettingsDoc, userSettings);
	userSettings.close();
	mergeSettings(settingsDoc.as<JsonObject>(), userSettingsDoc.as<JsonObjectConst>());
}

void convertFromJson(JsonVariantConst src, IPAddress& dst) {
  dst.fromString(src.as<const char*>());
}