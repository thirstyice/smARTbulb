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
class SettingTypeBase : public Setting {
protected:
	static const size_t size = sizeof(T);
	union B {
		T var;
		byte bytes[size];
	};
	T var;
	virtual bool parseString(String string) override {
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
public:
	explicit SettingTypeBase(Preferences& _prefs, String _key, T _val) : Setting(_prefs, _key), var(_val) {}

	virtual bool recall() override {
		if (!prefs.isKey(key.c_str())) {
			return true;
		}
		if (prefs.getBytesLength(key.c_str()) < size) {
			return false;
		}
		B buffer;
		if (prefs.getBytes(key.c_str(), buffer.bytes, size) == size) {
			var = buffer.var;
			return true;
		}
		return false;
	}

	virtual bool save() override {
		B buffer;
		buffer.var = var;
		if (prefs.putBytes(key.c_str(), buffer.bytes, size) == size) {
			return true;
		}
		return false;
	}
	virtual String getAsString() override {
		return String(var);
	};
};

template <typename T>
class SettingType : public SettingTypeBase<T> { // Default interface
public:
	using SettingTypeBase<T>::SettingTypeBase;
	T& val = SettingTypeBase<T>::var; // Access the protected variable directly
};

template <>
class SettingType<IPAddress> : public SettingTypeBase<uint32_t> {
protected:
	bool parseString(String string) override {
		return val.fromString(string);
	}
public:
	IPAddress val;
	SettingType(Preferences& _prefs, String _key, IPAddress _val) : SettingTypeBase<uint32_t>(_prefs, _key, uint32_t(_val)), val(_val) {}
	bool recall() override {
		if (SettingTypeBase<uint32_t>::recall()) {
			val = IPAddress(var);
			return true;
		}
		return false;
	}

	bool save() override {
		var = uint32_t(val);
		return SettingTypeBase<uint32_t>::save();
	}
	String getAsString() override {
		return val.toString();
	}
};

template<>
class SettingType<String> : public Setting {
protected:
	String var;
	bool parseString(String string) override {
		var = string;
		return true;
	}
public:
	SettingType(Preferences& _prefs, String _key, String _val) : Setting(_prefs, _key), var(_val) {}
	String& val = var;
	bool recall() override {
		var = prefs.getString(key.c_str(), var);
		return true;
	}
	bool save() override {
		if (prefs.putString(key.c_str(), var) == 0) {
			return false;
		}
		return true;
	}
	String getAsString() override {
		return var;
	}
};