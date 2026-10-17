/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/JsonSettings.h                                                *
*                                                                              *
* Created: 2026-09-08                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#pragma once
#include <ArduinoJson.h>
#include <LittleFS.h>

#define DEFAULTSETTINGSFILE "default-settings.json"
#define USERSETTINGSFILE "user-settings.json"

extern JsonDocument settingsDoc;

void jsonDeepMerge(JsonVariant dst, JsonVariantConst src, JsonVariantConst keyref);
void reloadSettings();

void convertFromJson(JsonVariantConst src, IPAddress& dst);