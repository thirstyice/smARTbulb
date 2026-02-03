/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/smartbulb-version.h                                           *
*                                                                              *
* Created: 2026-02-03                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#pragma once

#define SMARTBULB_VERSION_MAJOR 0
#define SMARTBULB_VERSION_MINOR 0
#define SMARTBULB_VERSION_PATCH 0

#define SMARTBULB_VERSION_VAL(major, minor, patch) ((major << 16) | (minor << 8) | (patch))
#define SMARTBULB_VERSION SMARTBULB_VERSION_VAL(SMARTBULB_VERSION_MAJOR, SMARTBULB_VERSION_MINOR, SMARTBULB_VERSION_PATCH)

#define df2xstr(s)              #s
#define df2str(s)               df2xstr(s)
#define SMARTBULB_VERSION_STR df2str(SMARTBULB_VERSION_MAJOR) "." df2str(SMARTBULB_VERSION_MINOR) "." df2str(SMARTBULB_VERSION_PATCH)
