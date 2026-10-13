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

#include "Module.h"

#include <driver/ledc.h>

namespace pwm {
	void begin()  {

	};
	void end() {

	};
	void out(uint8_t, uint16_t) {

	};
} // namespace pwm

Light PWM{"pwm", pwm::begin, pwm::end, pwm::out};