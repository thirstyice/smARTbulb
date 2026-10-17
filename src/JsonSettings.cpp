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

void jsonDeepMerge(JsonVariant dst, JsonVariantConst src, JsonVariantConst keyref) {
	if (src.is<JsonObjectConst>()) {
		for (JsonPairConst kvp : src.as<JsonObjectConst>()) {
			if (keyref[kvp.key()]) {
				if (dst[kvp.key()]) {
					jsonDeepMerge(dst[kvp.key()], kvp.value(), keyref[kvp.key()]);
				} else {
					dst[kvp.key()] = kvp.value();
				}
			}
		}
	} else {
		dst.set(src);
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
	jsonDeepMerge(settingsDoc, userSettingsDoc, settingsDoc);
}

void convertFromJson(JsonVariantConst src, IPAddress& dst) {
  dst.fromString(src.as<const char*>());
}