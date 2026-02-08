/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/Settings.cpp                                                  *
*                                                                              *
* Created: 2026-02-08                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#include "Settings.h"

std::map<const char* const, SettingsArray> Section::sections = {};
Preferences prefsObj = Preferences{};

Preferences* Settings::getPrefs(const char* section) {
	if (prefsObj.begin(section)) {
		return &prefsObj;
	}
	prefsObj.end();
	return getPrefs(section);
}