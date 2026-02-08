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
#include <Preferences.h>
#include <ArxContainer.h>
#include "macros.h"

#define DEFINE_SETTING(type, name, value) SettingsType<type> name = SettingsType<type>{__STRINGIFY(name), type(value)}
#define _DEFINE_SETTING(x) DEFINE_SETTING x;
#define SETTING_NAME(type, name, value) &name
#define _SETTING_ARRAY(setting) , SETTING_NAME setting
#define SETTING_ARRAY(first, ...)  SETTING_NAME first FOR_EACH(_SETTING_ARRAY, __VA_ARGS__)

/**
** @brief Creates all the required variables for a section of settings. Should
** be used within the namespace of the corresponding file
** @param sectionName The unique name of the section of settings. Should match
** the name of the html file in the webui for adjusting the settings
** @param args A list of settings to be defined, of the form (type, name, value)
** e.g. `(IPAddress, ip, "0.0.0.0"), (String, hostname, "name")` etc
** @note Once created, the value of the setting can be accessed within the file
** using `{setting name}.val`, and the section name using `setSection.name`.
** See Settings class for more details.
**/
#define MakeSettings(sectionName, ...) FOR_EACH(_DEFINE_SETTING, __VA_ARGS__) \
	Settings* settings[] = {SETTING_ARRAY(__VA_ARGS__)}; \
	Section setSection{sectionName, settings, sizeof(settings)/sizeof(Settings*)}



class Settings {
protected:
	const char* const key;
public:
	Settings(const char* const _key) : key(_key) {}
	static Preferences* getPrefs(const char* section);
	const char* const getKey() {return key;}
	virtual bool recall(Preferences* prefs) =0;
	virtual bool save(Preferences* prefs) =0;
	virtual bool setFromString(String) =0;
	virtual String getAsString() =0;
};

struct SettingsArray {
	Settings** array;
	size_t size;
	SettingsArray(Settings** _array, size_t _size) : array(_array), size(_size) {}
	SettingsArray() : array(nullptr), size(0) {};
};

struct Section {
	static std::map<const char* const, SettingsArray> sections;
	const char* const name;
	Section(const char* const _name, Settings** array, size_t size) : name(_name) {
		sections[name] = SettingsArray(array, size);
	}
};

#include "SettingsTypes.h"

// Settings(Light, type, gpio, chanmap, startcolor, connectcolor, noconnectcolor);
// Settings(Control, protocol, net, subnet, universe, address);
