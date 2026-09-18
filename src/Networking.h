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

#include <Arduino.h>
#include "JsonSettings.h"
#include <WiFi.h>

namespace Networking {

extern TaskHandle_t handle;

void networkingTask(void*);
}
