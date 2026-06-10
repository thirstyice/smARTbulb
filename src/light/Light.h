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
#include "modules.h"
#include "Settings.h"


/**
** @brief Defines the common interface for Light types
**
**/
class Light {
private:
	std::function<void()> beginFunc;
	std::function<void()> endFunc;
	std::function<void(uint8_t, uint8_t)> outFunc;
public:
	void setOutput(int8_t output, uint16_t value) {
		if (output<0) {
			return;
		}
		outFunc(output, value);
	};
	void begin() {
		beginFunc();
	}
	void end() {
		endFunc();
	}
	const char * const name;
	const uint8_t& numGPIO;
	const char * const * gpioNames;
	Light(
		const char * const _name,
		const uint8_t& _numGPIO,
		const char * const * _gpioNames,
		std::function<void()> _beginFunc,
		std::function<void()> _endFunc,
		std::function<void(uint8_t, uint8_t)> _outFunc
	) :
		name(_name),
		numGPIO(_numGPIO),
		gpioNames(_gpioNames),
		beginFunc(_beginFunc),
		endFunc(_endFunc),
		outFunc(_outFunc)
	{}
}; // class Light

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


void setColor(Color, uint8_t);
uint8_t getColor(Color);
bool hasRGB();
bool hasCT();

extern std::map<uint16_t, Light*> modules;
extern Settings settings;

} // namespace light

#define INCLUDE_NONE // Include the empty module