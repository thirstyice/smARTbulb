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

struct Setting {
	const char * const label;
	const int16_t min;
	const int16_t max;
	int16_t value;
	Setting(
		const char * const _label,
		const int16_t _min,
		const int16_t _max
	) : label(_label), min(_min), max(_max)
	{}
};

/**
** @brief Defines the common interface for Light types
**
**/
struct Light {
private:
	std::function<Setting*()> getSetArrFunc;
	std::function<uint8_t()> getSetLenFunc;
	std::function<void()> beginFunc;
	std::function<void()> endFunc;
	std::function<void(uint8_t, uint8_t)> outFunc;
	void setOutput(uint8_t output, uint16_t value) {
		outFunc(output, value);
	};
public:
	static void setColor(Color, uint8_t);
	static uint8_t getColor(Color);
	static void setOutputMap(Color, int8_t = -1); // -1 = disabled
	static int8_t getOutputMap(Color);
	static bool hasRGB();
	static bool hasCT();
	static const uint8_t numModules;
	static Light* const modules[];
	static uint8_t currentModuleIndex;

	Setting* getSettingsArray() {
		return getSetArrFunc();
	}
	uint8_t getSettingsLength() {
		return getSetLenFunc();
	}
	void begin() {
		beginFunc();
	}
	void end() {
		endFunc();
	}
	const char * const name;

	Light(
		const char * const _name,
		std::function<Setting*()> _getSetArrFunc,
		std::function<uint8_t()> _getSetLenFunc,
		std::function<void()> _beginFunc,
		std::function<void()> _endFunc,
		std::function<void(uint8_t, uint8_t)> _outFunc
	) :
		name(_name),
		getSetArrFunc(_getSetArrFunc),
		getSetLenFunc(_getSetLenFunc),
		beginFunc(_beginFunc),
		endFunc(_endFunc),
		outFunc(_outFunc)
	{}
}; // class Light


extern Light None;
extern Light PWM;

} // namespace light