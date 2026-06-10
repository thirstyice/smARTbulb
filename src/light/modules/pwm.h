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

#include "../Light.h"

#ifdef INCLUDE_PWM

#include <driver/ledc.h>

namespace pwm {
	const char * const gpioNames[] = {
		"Output 1",
		"Output 2",
		"Output 3",
		"Output 4",
		"Output 5"
	};
	const uint8_t numGPIO = sizeof(gpioNames) / sizeof(gpioNames[0]);

	void begin()  {

	};
	void end() {

	};
	void out(uint8_t, uint16_t) {

	};
} // namespace pwm

Light PWM{"PWM", pwm::numGPIO, pwm::gpioNames, pwm::begin, pwm::end, pwm::out};

#endif