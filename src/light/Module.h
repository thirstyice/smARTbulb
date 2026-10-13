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
	Light(
		const char * const _name,
		std::function<void()> _beginFunc,
		std::function<void()> _endFunc,
		std::function<void(uint8_t, uint8_t)> _outFunc
	) :
		name(_name),
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

} // namespace light