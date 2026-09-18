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
#include <ArduinoJson.h>

#define SETTINGSFILE "settings.json"
#define DEFAULTSETTINGSFILE "default-settings.json"
#define USERDEFAULTSETTINGSFILE "user-settings.json"

JsonDocument settingsDoc;
