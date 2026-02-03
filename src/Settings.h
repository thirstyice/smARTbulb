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

#define DEFINE_SETTING(x) const char* const (set ## x) = __STRINGIFY(x);
#define SETTINGS(...) FOR_EACH(DEFINE_SETTING, __VA_ARGS__)
#define MakeSettings(section, ...) SETTINGS(__VA_ARGS__) \
const char* const setSection = __STRINGIFY(section);

namespace Settings {
	Preferences* getPrefs(const char* section);
} // namespace Settings

// Settings(Light, type, gpio, chanmap, startcolor, connectcolor, noconnectcolor);
// Settings(Control, protocol, net, subnet, universe, address);
