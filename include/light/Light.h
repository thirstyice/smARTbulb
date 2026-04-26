/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/Light.h                                                       *
*                                                                              *
* Created: 2026-04-04                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#pragma once
#include <Arduino.h>

namespace light {

enum Color : uint8_t {
	Intensity=0,
	Red,
	Green,
	Blue,
	Cool,
	Warm,
	End
};

/**
** @brief Defines the common interface for Light types
**
**/
struct Interface {
	struct Setting {
		const char * label;
		int16_t min;
		int16_t max;
		int16_t value;
	};
	virtual Setting* getSettingsArray()=0;
	virtual uint8_t getSettingsLength()=0;
	virtual void begin() =0;
	virtual void end() =0;
	virtual void setColor(Color, uint16_t) =0;
	const char * const name = "err";
}; // class Interface

void setColor(Color, uint8_t);
uint8_t getColor(Color);
void setOutputMap(Color, int8_t = -1); // -1 = disabled
int8_t getOutputMap(Color);
bool hasRGB();
bool hasCT();
extern const uint8_t numModules;
extern const Interface* modules[numModules];
extern uint8_t currentModuleIndex;

} // namespace light