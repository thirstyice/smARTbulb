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
#include "Light.h"

#include <driver/ledc.h>

namespace light {

namespace pwm {
	Setting settingsArray[] = {
		Setting{"GPIO 1", -1, 33},
		Setting{"GPIO 2", -1, 33},
		Setting{"GPIO 3", -1, 33},
		Setting{"GPIO 4", -1, 33},
		Setting{"GPIO 5", -1, 33}
	};
	const uint8_t settingsArrayLength = sizeof(settingsArray) / sizeof(settingsArray[0]);

	Setting* settings()  {
		return settingsArray;
	}

	uint8_t settingsLen()  {
		return settingsArrayLength;
	};
	void begin()  {

	};
	void end() {

	};
	void out(uint8_t, uint16_t) {

	};
} // namespace pwm

Light PWM{"PWM", pwm::settings, pwm::settingsLen, pwm::begin, pwm::end, pwm::out};

} // namespace light
