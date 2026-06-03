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

bool Setting::setFromString(String string) {
	if (parseString(string)) {
		return true;
	}
	return false;
}