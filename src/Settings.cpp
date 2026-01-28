/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/Settings.cpp                                                  *
*                                                                              *
* Created: 2026-01-21                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#include "Settings.h"

namespace Settings {

Preferences prefs = Preferences{};

Preferences* getPrefs(const char* section) {
	if (prefs.begin(section)) {
		return &prefs;
	}
	prefs.end();
	return getPrefs(section);
}

} // namespace Settings
