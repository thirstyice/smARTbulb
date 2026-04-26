/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /include/light/Light.cpp                                           *
*                                                                              *
* Created: 2026-04-26                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/

#include "Light.h"

namespace light {

/**
** @section Module headers
**
**/
#include "pwm.h"




/**
** @brief Module array
**
**/
const Interface* moduleArray[] = {
	new light::PWM()
};

const uint8_t numModules = sizeof(moduleArray) / sizeof(Interface*);

} // namespace light