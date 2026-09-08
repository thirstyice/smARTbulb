/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/Network.h                                                     *
*                                                                              *
* Created: 2026-01-25                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#pragma once
#include "options.h"

#include <Arduino.h>
#include <WiFi.h>

namespace Networking {

extern bool connected;
extern volatile bool settingsDidUpdate;
extern IPAddress ip;
extern IPAddress gateway;
extern IPAddress subnet;
extern std::map<String, String> wifi;
extern String hostname;
extern String apSSID;
extern String apPass;

void networkingTask(void*);
}
