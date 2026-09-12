/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/webui/shared.h                                                *
*                                                                              *
* Created: 2026-09-12                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#pragma once

#include "WebUi.h"
#include "../JsonSettings.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

namespace WebUi {
	AsyncWebServer server{80};
	String getGenericVar(String var);
} // namespace WebUi