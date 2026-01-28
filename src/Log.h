/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/Log.h                                                         *
*                                                                              *
* Created: 2026-01-25                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#pragma once

#include <Arduino.h>
#include <Decorator.h>

class Log {
	Log(uint16_t lines = 250, uint8_t cols = 80) {

	}
}

class Logger : public Decorator<Print> {
	protected:
		uint16_t lines = 500;
		uint8_t cols = 80;
		char log[lines][cols];
	public:
		using Decorator::Decorator;
		size_t write(uint8_t c) override;
	};

	extern Print* Log;