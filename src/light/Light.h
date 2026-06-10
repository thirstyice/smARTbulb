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
	static std::map<uint16_t, Light*> modules;
	Light(
		uint16_t moduleID,
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
	{modules[moduleID] = this;}
}; // class Light

void setColor(Color, uint8_t);
uint8_t getColor(Color);
bool hasRGB();
bool hasCT();

extern Settings settings;

} // namespace light