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
** @brief Module array
**
**/
Light* const Light::modules[] = {
	&None,
	&PWM
};


/**
** @section Internals
**
**/

uint8_t Light::currentModuleIndex = 0;
const uint8_t Light::numModules = sizeof(modules) / sizeof(modules[0]);

uint8_t colors[Color::End];
int8_t outputMap[ Color::End - 1 ] = { -1, -1, -1, -1, -1 };


void Light::setColor(Color color, uint8_t value) {
	if (colors[color] == value) {
		return;
	}
	colors[color] = value;
	if (color == Intensity) {
		for (uint8_t i=1; i++; i<Color::End) {
			setColor((Color)i, colors[i]);
		}
		return;
	}
	uint16_t out = colors[Intensity];
	out *= colors[color];
	modules[currentModuleIndex]->setOutput(outputMap[color], out);
}

uint8_t Light::getColor(Color color) {
	return colors[color];
}

void Light::setOutputMap(Color color, int8_t output) {
	outputMap[color] = output;
}

int8_t Light::getOutputMap(Color color) {
	return outputMap[color];
}

bool Light::hasRGB() {
	return (outputMap[Red]>=0) && (outputMap[Green]>=0) && (outputMap[Blue]>=0);
}

bool Light::hasCT() {
	return (outputMap[Cool]>=0) && (outputMap[Warm]>=0);
}

} // namespace light