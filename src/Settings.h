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
#include "macros.h"

#define DEFINE_SETTING(type, name, value) SettingsType<type> name = SettingsType<type>{__STRINGIFY(name), type(value)}
#define _DEFINE_SETTING(x) DEFINE_SETTING ## x;
#define SETTING_NAME(type, name, value) &name
#define _SETTING_ARRAY(setting) , SETTING_NAME ## setting
#define SETTING_ARRAY(first, ...)  SETTING_NAME ## first FOR_EACH(_SETTING_ARRAY, __VA_ARGS__)

#define MakeSettings(...) FOR_EACH(_DEFINE_SETTING, __VA_ARGS__) \
	Settings* settings[] = {SETTING_ARRAY(__VA_ARGS__)}

class Settings {
private:
	static Preferences prefsObj;
protected:
	const char* const key;
public:
	Settings(const char* const _key) : key(_key) {}
	static Preferences* getPrefs(const char* section) {
		if (prefsObj.begin(section)) {
			return &prefsObj;
		}
		prefsObj.end();
		return getPrefs(section);
	}
	virtual bool get(Preferences* prefs) =0;
	virtual bool put(Preferences* prefs) =0;
};

template <typename T>
class SettingsTypeBase : public Settings {
protected:
	static const size_t size = sizeof(T);
	union B {
		T var;
		byte byte[size];
	};
	T var;
public:
	SettingsTypeBase(const char* _key, T _val) : Settings(_key), var(_val) {}

	bool get(Preferences* prefs) override {
		if (!prefs->isKey(key)) {
			return true;
		}
		if (prefs->getBytesLength(key) < size) {
			return false;
		}
		B buffer;
		if (prefs->getBytes(key, buffer.byte, size) == size) {
			var = buffer.var;
			return true;
		}
		return false;
	}

	bool put(Preferences* prefs) override {
		B buffer;
		buffer.var = var;
		if (prefs->putBytes(key, buffer.byte, size) == size) {
			return true;
		}
		return false;
	}
};

template <typename T>
class SettingsType : public SettingsTypeBase<T> { // Default interface
public:
	using SettingsTypeBase<T>;
	T& val = var; // Access the protected variable directly
};

template <>
class SettingsType<IPAddress> : public SettingsTypeBase<uint32_t> {
protected:
public:
	IPAddress val;
	SettingsType(const char* _key, IPAddress _val) : SettingsTypeBase<uint32_t>(_key, uint32_t(_val)), val(_val) {}
	bool get(Preferences* prefs) override {
		if (SettingsTypeBase<uint32_t>::get(prefs)) {
			val = IPAddress(var);
			return true;
		}
		return false;
	}

	bool put(Preferences* prefs) override {
		var = uint32_t(val);
		return SettingsTypeBase<uint32_t>::put(prefs);
	}
};

template<>
class SettingsType<String> : public SettingsTypeBase<String> {
protected:
public:
	using SettingsTypeBase<String>::SettingsTypeBase;
	String& val = var;
	bool get(Preferences* prefs) override {
		var = prefs->getString(key, var);
		return true;
	}
	bool put(Preferences* prefs) override {
		if (prefs->putString(key, var) == 0) {
			return false;
		}
		return true;
	}
};

// Settings(Light, type, gpio, chanmap, startcolor, connectcolor, noconnectcolor);
// Settings(Control, protocol, net, subnet, universe, address);
