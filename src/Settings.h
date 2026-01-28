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

#define Settings(section, ...) namespace Settings { \
enum section : unsigned char { __VA_ARGS__, End }; \
const char* const section[section::End] = { STR_ARRAY(__VA_ARGS__)}; \
}

Preferences* getPrefs(const char* section);

Settings(Network, ip, subnet, gateway, ssid1, pass1, ssid2, pass2, hostname);
Settings(Light, type, gpio, chanmap, startcolor, connectcolor, noconnectcolor);
Settings(Control, protocol, net, subnet, universe, address);
