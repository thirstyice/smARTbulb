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

#define DEFINE_SETTING(type, name, value, ...) SettingType<type> name = SettingType<type>{prefs, __STRINGIFY(name), type(value) __VA_OPT__(,) __VA_ARGS__}
#define _DEFINE_SETTING(x) DEFINE_SETTING x;
#define SETTING_NAME(type, name, ...) name
#define __SETTING_MAP(name) { __STRINGIFY(name), & name }
#define _SETTING_MAP(setting) , __SETTING_MAP(SETTING_NAME setting)
#define SETTING_MAP(first, ...)  __SETTING_MAP(SETTING_NAME first) FOR_EACH(_SETTING_MAP, __VA_ARGS__)

/**
** @brief Creates all the required variables for a section of settings. Should
** be used within the namespace of the corresponding file
** @param args A list of settings to be defined, of the form (type, name, value)
** e.g. `(IPAddress, ip, "0.0.0.0"), (String, hostname, "name")` etc
** @note Once created, the value of the setting can be accessed
** using `{setting name}.val`.
** See Settings class for more details.
**/
#define MakeSettings(...) Preferences prefs;\
FOR_EACH(_DEFINE_SETTING, __VA_ARGS__) \
Settings settings{ SETTING_MAP(__VA_ARGS__) }

#define BeginSettings(sectionName) prefs.begin(sectionName);
#define SaveSettings() for (auto& setting : settings) {setting.second->save();}
#define RecallSettings() for (auto& setting : settings) {setting.second->recall();}





class Setting {
	typedef std::function<void(Setting*)> SettingCallback;
protected:
	SettingCallback callback;
	const char * key;
	Preferences& prefs;
	virtual bool parseString(String) =0;
public:
	static constexpr void blankSettingCallback(Setting*) {}
	Setting(Preferences& _prefs, const char * _key): prefs(_prefs), key(_key) {}
	void setCallback(SettingCallback _callback) {callback = _callback;}
	constexpr const char * getKey() {return key;}
	virtual bool recall() =0;
	virtual bool save() =0;
	bool setFromString(String string);
	virtual String getAsString() =0;
};
 typedef std::map<String, Setting*> Settings;

#include "SettingsTypes.h"

// Settings(Light, type, gpio, chanmap, startcolor, connectcolor, noconnectcolor);
// Settings(Control, protocol, net, subnet, universe, address);
