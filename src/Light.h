/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/Light.h                                                       *
*                                                                              *
* Created: 2026-10-13                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#pragma once

#include <Arduino.h>
#include "JsonSettings.h"
#include "light/Module.h"

namespace light {
	extern volatile bool restart;
	extern TaskHandle_t handle;
	extern volatile uint8_t colors[Color::End];
	void lightTask(void*);
}