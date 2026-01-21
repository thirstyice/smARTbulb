/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/Settings.cpp                                                  *
*                                                                              *
* Created: 2026-01-21                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#include "Settings.h"

#if defined(ESP32)
Preferences SettingsManager::prefs = Preferences{};

Preferences* SettingsManager::getPrefs(const char* setting, bool rw) {
	if (prefs.begin(setting)) {
		return &prefs;
	}
	prefs.end();
	return getPrefs(setting, rw);
}
size_t SettingsManager::put(const char *key, int8_t value) {

}
size_t SettingsManager::put(const char *key, uint8_t value) {

}
size_t SettingsManager::put(const char *key, int16_t value) {

}
size_t SettingsManager::put(const char *key, uint16_t value) {

}
size_t SettingsManager::put(const char *key, int32_t value) {

}
size_t SettingsManager::put(const char *key, uint32_t value) {

}
size_t SettingsManager::put(const char *key, int32_t value) {

}
size_t SettingsManager::put(const char *key, uint32_t value) {

}
size_t SettingsManager::put(const char *key, int64_t value) {

}
size_t SettingsManager::put(const char *key, uint64_t value) {

}
size_t SettingsManager::put(const char *key, float_t value) {

}
size_t SettingsManager::put(const char *key, double_t value) {

}
size_t SettingsManager::put(const char *key, bool value) {

}
size_t SettingsManager::put(const char *key, String value) {

}

size_t SettingsManager::putBytes(const char *key, const void *value, size_t len) {

}

int8_t SettingsManager::get(const char *key, int8_t defaultValue = 0) {

}
uint8_t SettingsManager::get(const char *key, uint8_t defaultValue = 0) {

}
int16_t SettingsManager::get(const char *key, int16_t defaultValue = 0) {

}
uint16_t SettingsManager::get(const char *key, uint16_t defaultValue = 0) {

}
int32_t SettingsManager::get(const char *key, int32_t defaultValue = 0) {

}
uint32_t SettingsManager::get(const char *key, uint32_t defaultValue = 0) {

}
int32_t SettingsManager::get(const char *key, int32_t defaultValue = 0) {

}
uint32_t SettingsManager::get(const char *key, uint32_t defaultValue = 0) {

}
int64_t SettingsManager::get(const char *key, int64_t defaultValue = 0) {

}
uint64_t SettingsManager::get(const char *key, uint64_t defaultValue = 0) {

}
float_t SettingsManager::get(const char *key, float_t defaultValue = NAN) {

}
double_t SettingsManager::get(const char *key, double_t defaultValue = NAN) {

}
bool SettingsManager::get(const char *key, bool defaultValue = false) {

}
String SettingsManager::get(const char *key, String defaultValue = String()) {

}

size_t SettingsManager::getBytesLength(const char *key) {

}
size_t SettingsManager::getBytes(const char *key, void *buf, size_t maxLen) {

}


#elif defined(ESP8266)
size_t SettingsManager::put(const char *key, int8_t value) {

}
size_t SettingsManager::put(const char *key, uint8_t value) {

}
size_t SettingsManager::put(const char *key, int16_t value) {

}
size_t SettingsManager::put(const char *key, uint16_t value) {

}
size_t SettingsManager::put(const char *key, int32_t value) {

}
size_t SettingsManager::put(const char *key, uint32_t value) {

}
size_t SettingsManager::put(const char *key, int32_t value) {

}
size_t SettingsManager::put(const char *key, uint32_t value) {

}
size_t SettingsManager::put(const char *key, int64_t value) {

}
size_t SettingsManager::put(const char *key, uint64_t value) {

}
size_t SettingsManager::put(const char *key, float_t value) {

}
size_t SettingsManager::put(const char *key, double_t value) {

}
size_t SettingsManager::put(const char *key, bool value) {

}
size_t SettingsManager::put(const char *key, String value) {

}

size_t SettingsManager::putBytes(const char *key, const void *value, size_t len) {

}

int8_t SettingsManager::get(const char *key, int8_t defaultValue = 0) {

}
uint8_t SettingsManager::get(const char *key, uint8_t defaultValue = 0) {

}
int16_t SettingsManager::get(const char *key, int16_t defaultValue = 0) {

}
uint16_t SettingsManager::get(const char *key, uint16_t defaultValue = 0) {

}
int32_t SettingsManager::get(const char *key, int32_t defaultValue = 0) {

}
uint32_t SettingsManager::get(const char *key, uint32_t defaultValue = 0) {

}
int32_t SettingsManager::get(const char *key, int32_t defaultValue = 0) {

}
uint32_t SettingsManager::get(const char *key, uint32_t defaultValue = 0) {

}
int64_t SettingsManager::get(const char *key, int64_t defaultValue = 0) {

}
uint64_t SettingsManager::get(const char *key, uint64_t defaultValue = 0) {

}
float_t SettingsManager::get(const char *key, float_t defaultValue = NAN) {

}
double_t SettingsManager::get(const char *key, double_t defaultValue = NAN) {

}
bool SettingsManager::get(const char *key, bool defaultValue = false) {

}
String SettingsManager::get(const char *key, String defaultValue = String()) {

}

size_t SettingsManager::getBytesLength(const char *key) {

}
size_t SettingsManager::getBytes(const char *key, void *buf, size_t maxLen) {

}

#endif
