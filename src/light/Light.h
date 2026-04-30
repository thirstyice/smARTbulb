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
struct Light {
private:
	std::function<void()> beginFunc;
	std::function<void()> endFunc;
	std::function<void(uint8_t, uint8_t)> outFunc;
	void setOutput(uint8_t output, uint16_t value) {
		outFunc(output, value);
	};
public:
	static void setColor(Color, uint8_t);
	static uint8_t getColor(Color);
	static bool hasRGB();
	static bool hasCT();
	static const uint8_t numModules;
	static Light* const modules[];

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


extern Light None;
extern Light PWM;

} // namespace light