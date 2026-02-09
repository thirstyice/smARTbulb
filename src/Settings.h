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

#define DEFINE_SETTING(type, name, value) SettingType<type> name = SettingType<type>{__STRINGIFY(name), type(value)}
#define _DEFINE_SETTING(x) DEFINE_SETTING x;
#define SETTING_NAME(type, name, value) name
#define __SETTING_MAP(name) { __STRINGIFY(name), & name }
#define _SETTING_MAP(setting) , __SETTING_MAP(SETTING_NAME setting)
#define SETTING_MAP(first, ...)  __SETTING_MAP(SETTING_NAME first) FOR_EACH(_SETTING_MAP, __VA_ARGS__)

/**
** @brief Creates all the required variables for a section of settings. Should
** be used within the namespace of the corresponding file
** @param sectionName The unique name of the section of settings. Should match
** the name of the html file in the webui for adjusting the settings
** @param args A list of settings to be defined, of the form (type, name, value)
** e.g. `(IPAddress, ip, "0.0.0.0"), (String, hostname, "name")` etc
** @note Once created, the value of the setting can be accessed within the file
** using `{setting name}.val`, and the section name using `settings.name`.
** See Settings class for more details.
**/
#define MakeSettings(sectionName, ...) FOR_EACH(_DEFINE_SETTING, __VA_ARGS__) \
	Settings settings{sectionName, std::map<const char* const, Setting*>{ SETTING_MAP(__VA_ARGS__) }}



class Setting {
protected:
	const char* const key;
	bool updated = false;
	virtual bool parseString(String) =0;
public:
	Setting(const char* const _key) : key(_key) {}
	constexpr bool wasUpdated() {return updated;}
	constexpr const char* const getKey() {return key;}
	virtual bool recall(Preferences* prefs) =0;
	virtual bool save(Preferences* prefs) =0;
	bool setFromString(String string);
	virtual String getAsString() =0;
};

typedef std::function<void()> SettingsCallback;
typedef std::map<const char* const, Setting*> SettingSection;

struct Settings {
	static std::map<const char* const, SettingSection> sections;
	const char* const name;
	SettingSection* settings;
	SettingsCallback callback;
	static Preferences* getPrefs(const char* section);
	Preferences* getPrefs() {return getPrefs(name);}
	Settings(
		const char* const _name,
		SettingSection _settings,
		SettingsCallback _callback = nullptr
	) : name(_name), callback(_callback) {
		sections[name] = _settings;
		settings = &sections[name];
		if (callback == nullptr) {
			callback = [&]() {
				Preferences* prefs = getPrefs();
				for (auto const& setting : *settings) {
					if (setting.second->wasUpdated()) {
						setting.second->save(prefs);
					}
				}
			};
		}
	}
};

#include "SettingsTypes.h"

// Settings(Light, type, gpio, chanmap, startcolor, connectcolor, noconnectcolor);
// Settings(Control, protocol, net, subnet, universe, address);
