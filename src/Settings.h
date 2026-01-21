/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/Settings.h                                                    *
*                                                                              *
* Created: 2026-01-21                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#pragma once

#include <Arduino.h>

#if defined(ESP32)
#include <Preferences.h>
class SettingsManager {
private:
static Preferences prefs;
Preferences* getPrefs(const char*, bool);
public:
	size_t put(const char *key, int8_t value);
	size_t put(const char *key, uint8_t value);
	size_t put(const char *key, int16_t value);
	size_t put(const char *key, uint16_t value);
	size_t put(const char *key, int32_t value);
	size_t put(const char *key, uint32_t value);
	size_t put(const char *key, int32_t value);
	size_t put(const char *key, uint32_t value);
	size_t put(const char *key, int64_t value);
	size_t put(const char *key, uint64_t value);
	size_t put(const char *key, float_t value);
	size_t put(const char *key, double_t value);
	size_t put(const char *key, bool value);
	size_t put(const char *key, String value);

	size_t putBytes(const char *key, const void *value, size_t len);

	int8_t get(const char *key, int8_t defaultValue = 0);
	uint8_t get(const char *key, uint8_t defaultValue = 0);
	int16_t get(const char *key, int16_t defaultValue = 0);
	uint16_t get(const char *key, uint16_t defaultValue = 0);
	int32_t get(const char *key, int32_t defaultValue = 0);
	uint32_t get(const char *key, uint32_t defaultValue = 0);
	int32_t get(const char *key, int32_t defaultValue = 0);
	uint32_t get(const char *key, uint32_t defaultValue = 0);
	int64_t get(const char *key, int64_t defaultValue = 0);
	uint64_t get(const char *key, uint64_t defaultValue = 0);
	float_t get(const char *key, float_t defaultValue = NAN);
	double_t get(const char *key, double_t defaultValue = NAN);
	bool get(const char *key, bool defaultValue = false);
	String get(const char *key, String defaultValue = String());

	size_t getBytesLength(const char *key);
	size_t getBytes(const char *key, void *buf, size_t maxLen);
};

#elif defined(ESP8266)
class SettingsManager {
	private:

	public:
		size_t put(const char *key, int8_t value);
		size_t put(const char *key, uint8_t value);
		size_t put(const char *key, int16_t value);
		size_t put(const char *key, uint16_t value);
		size_t put(const char *key, int32_t value);
		size_t put(const char *key, uint32_t value);
		size_t put(const char *key, int32_t value);
		size_t put(const char *key, uint32_t value);
		size_t put(const char *key, int64_t value);
		size_t put(const char *key, uint64_t value);
		size_t put(const char *key, float_t value);
		size_t put(const char *key, double_t value);
		size_t put(const char *key, bool value);
		size_t put(const char *key, String value);

		size_t putBytes(const char *key, const void *value, size_t len);

		int8_t get(const char *key, int8_t defaultValue = 0);
		uint8_t get(const char *key, uint8_t defaultValue = 0);
		int16_t get(const char *key, int16_t defaultValue = 0);
		uint16_t get(const char *key, uint16_t defaultValue = 0);
		int32_t get(const char *key, int32_t defaultValue = 0);
		uint32_t get(const char *key, uint32_t defaultValue = 0);
		int32_t get(const char *key, int32_t defaultValue = 0);
		uint32_t get(const char *key, uint32_t defaultValue = 0);
		int64_t get(const char *key, int64_t defaultValue = 0);
		uint64_t get(const char *key, uint64_t defaultValue = 0);
		float_t get(const char *key, float_t defaultValue = NAN);
		double_t get(const char *key, double_t defaultValue = NAN);
		bool get(const char *key, bool defaultValue = false);
		String get(const char *key, String defaultValue = String());

		size_t getBytesLength(const char *key);
		size_t getBytes(const char *key, void *buf, size_t maxLen);
	};

#endif /* ESP32 */

namespace Settings {

SettingsManager manager;

struct Network { enum : unsigned char {
	Ip,
	Subnet,
	Gateway,
	Ssid1,
	Pass1,
	Ssid2,
	Pass2,
	Hostname,
	End
};
const char* key[End] = {
	"netip",
	"netsubnet",
	"netgateway",
	"netssid1",
	"netpass1",
	"netssid2",
	"netpass2",
	"nethost"
};
};
struct Light { enum : unsigned char {
	Type,
	Gpio,
	ChanMap,
	StartColor,
	ConnectColor,
	NoConnectColor,
	End
};
const char* key[End] = {
	"lighttype",
	"lightgpio",
	"lightmap",
	"lightstart",
	"lightconn",
	"lightnoconn"
};
};
struct Control { enum : unsigned char {
	Protocol,
	Net,
	Subnet,
	Universe,
	Address,
	End
};
const char* key[End] = {
	"conproto",
	"connet",
	"consubnet",
	"conuniverse",
	"conaddress"
};
};
} // namespace Settings
