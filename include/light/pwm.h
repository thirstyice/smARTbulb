/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /include/light/pwm.h                                               *
*                                                                              *
* Created: 2026-04-23                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#pragma once
#include "Light.h"
#include <driver/ledc.h>

namespace light {

struct PWM : Interface {
	Setting* getSettingsArray() override;
	uint8_t getSettingsLength() override;
	void begin() override;
	void end() override;
	void setColor(Color, uint16_t) override;
	const char * const name = "PWM";
};

} // namespace light
