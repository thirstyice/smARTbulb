/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/SettingsTypes.h                                               *
*                                                                              *
* Created: 2026-02-08                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#pragma once

/**
** @file SettingsTypes.h
** @brief Defines Settings interfaces for specific variable types
**
**/

#include <Arduino.h>
#include <Preferences.h>

#include "Settings.h"

template <typename T>
class SettingsTypeBase : public Settings {
protected:
	static const size_t size = sizeof(T);
	union B {
		T var;
		byte bytes[size];
	};
	T var;
public:
	SettingsTypeBase(const char* _key, T _val) : Settings(_key), var(_val) {}

	virtual bool recall(Preferences* prefs) override {
		if (!prefs->isKey(key)) {
			return true;
		}
		if (prefs->getBytesLength(key) < size) {
			return false;
		}
		B buffer;
		if (prefs->getBytes(key, buffer.bytes, size) == size) {
			var = buffer.var;
			return true;
		}
		return false;
	}

	virtual bool save(Preferences* prefs) override {
		B buffer;
		buffer.var = var;
		if (prefs->putBytes(key, buffer.bytes, size) == size) {
			return true;
		}
		return false;
	}

	virtual bool setFromString(String string) override {
		if (std::is_integral_v<T>) {
			var = string.toInt();
			return true;
		}
		if (std::is_floating_point_v<T>) {
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
	using SettingsTypeBase<T>::SettingsTypeBase;
	T& val = SettingsTypeBase<T>::var; // Access the protected variable directly
};

template <>
class SettingsType<IPAddress> : public SettingsTypeBase<uint32_t> {
protected:
public:
	IPAddress val;
	SettingsType(const char* _key, IPAddress _val) : SettingsTypeBase<uint32_t>(_key, uint32_t(_val)), val(_val) {}
	bool recall(Preferences* prefs) override {
		if (SettingsTypeBase<uint32_t>::recall(prefs)) {
			val = IPAddress(var);
			return true;
		}
		return false;
	}

	bool save(Preferences* prefs) override {
		var = uint32_t(val);
		return SettingsTypeBase<uint32_t>::save(prefs);
	}

	bool setFromString(String string) override {
		return val.fromString(string);
	}
	String getAsString() override {
		return val.toString();
	}
};

template<>
class SettingsType<String> : public Settings {
protected:
	String var;
public:
	SettingsType(const char* _key, String _val) : Settings(_key), var(_val) {}
	String& val = var;
	bool recall(Preferences* prefs) override {
		var = prefs->getString(key, var);
		return true;
	}
	bool save(Preferences* prefs) override {
		if (prefs->putString(key, var) == 0) {
			return false;
		}
		return true;
	}

	bool setFromString(String string) override {
		var = string;
		return true;
	}
	String getAsString() override {
		return var;
	}
};