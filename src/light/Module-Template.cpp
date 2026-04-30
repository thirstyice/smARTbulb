/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /include/light/Module-Template.h                                   *
*                                                                              *
* Created: 2026-04-27                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#include "Light.h"

namespace light {

namespace none {

	void begin()  {

	};
	void end() {

	};
	void out(uint8_t, uint16_t) {

	};

} // namespace none

Light None{"No Module Selected", 0, nullptr, none::begin, none::end, none::out};

} // namespace light
