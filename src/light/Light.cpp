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

MakeSettings(
	(uint8_t, moduleIndex, 0),
	(int8_t, redChan, -1),
	(int8_t, greenChan, -1),
	(int8_t, blueChan, -1),
	(int8_t, coolChan, -1),
	(int8_t, warmChan, -1)
);

/**
** @section Internals
**
**/

std::map<uint16_t, Light*> Light::modules;

uint8_t colors[Color::End];

int8_t getOutFromColor(Color color) {
	switch (color) {
		case Red:
			return redChan.val;
		break;
		case Green:
			return greenChan.val;
		break;
		case Blue:
			return blueChan.val;
		break;
		case Cool:
			return coolChan.val;
		break;
		case Warm:
			return warmChan.val;
		break;
		default:
			return -1;
		break;
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
	Light::modules[moduleIndex.val]->setOutput(getOutFromColor(color), out);
}

uint8_t getColor(Color color) {
	return colors[color];
}


bool hasRGB() {
	return (redChan.val>=0) && (greenChan.val>=0) && (blueChan.val>=0);
}

bool hasCT() {
	return (coolChan.val>=0) && (warmChan.val>=0);
}

} // namespace light