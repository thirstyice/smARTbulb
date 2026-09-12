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

uint8_t moduleIndex = 0;
int8_t colorChan[Color::End - 1] = {-1, -1, -1, -1, -1};
int8_t moduleGPIO[MAX_MODULE_GPIO];

/**
** @section Internals
**
**/

uint8_t colors[Color::End];

int8_t getOutFromColor(Color color) {
	if (color>0 && color<Color::End) {
		return colorChan[color];
	} else {
		return -1;
	}
}

void setColor(Color color, uint8_t value) {
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
	modules[moduleIndex]->setOutput(getOutFromColor(color), out);
}

uint8_t getColor(Color color) {
	return colors[color];
}

bool hasRGB() {
	return (colorChan[Color::Red]>=0) && (colorChan[Color::Green]>=0) && (colorChan[Color::Blue]>=0);
}

bool hasCT() {
	return (colorChan[Color::Cool]>=0) && (colorChan[Color::Warm]>=0);
}


/**
** @section Module definitions
**
**/

#include "modules/Module-Template.h"
#include "modules/pwm.h"



Light* modules[] = {
	&None,
	&PWM
};

const uint8_t numModules = sizeof(modules) / sizeof(modules[0]);




} // namespace light