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
#define _DEFINE_SETTING(x) DEFINE_SETTING ## x;
#define SETTING_NAME(type, name, value) &name
#define _SETTING_ARRAY(setting) , SETTING_NAME ## setting
#define SETTING_ARRAY(first, ...)  SETTING_NAME ## first FOR_EACH(_SETTING_ARRAY, __VA_ARGS__)

#define MakeSettings(sectionName, ...) FOR_EACH(_DEFINE_SETTING, __VA_ARGS__) \
	Settings* settings[] = {SETTING_ARRAY(__VA_ARGS__)}; \
	Section setSection{sectionName, settings, sizeof(settings)/sizeof(Settings*)}


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
	const char* const getKey() {return key;}
	virtual bool get(Preferences* prefs) =0;
	virtual bool put(Preferences* prefs) =0;
	virtual bool setFromString(String&) =0;
	virtual String getAsString() =0;
};

struct SettingsArray {
	Settings** array;
	size_t size;
	SettingsArray(Settings** _array, size_t _size) : array(_array), size(_size) {}
};

struct Section {
	static std::map<const char* const, SettingsArray> sections;
	const char* const name;
	Section(const char* const _name, Settings** array, size_t size) : name(_name) {sections[name] = SettingsArray(array, size);}
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

	virtual bool get(Preferences* prefs) override {
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

	virtual bool put(Preferences* prefs) override {
		B buffer;
		buffer.var = var;
		if (prefs->putBytes(key, buffer.byte, size) == size) {
			return true;
		}
		return false;
	}

	virtual bool setFromString(String& string) override {
		if (std::is_integral<T>) {
			var = string.toInt();
			return true;
		}
		if (std::is_floating_point<T>) {
			if (size == sizeof(double)) {
				var = string.toDouble();
			} else {
				var = string.toFloat();
			}
			return true;
		}
		return false;
	}
	virtual String getAsString() override {
		return String(var);
	};
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

	bool setFromString(String& string) override {
		return val.fromString(string);
	}
	String getAsString() override {
		return val.toString();
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

	bool setFromString(String& string) override {
		var = string;
		return true;
	}
	String getAsString() override {
		return var;
	}
};

// Settings(Light, type, gpio, chanmap, startcolor, connectcolor, noconnectcolor);
// Settings(Control, protocol, net, subnet, universe, address);
