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
#include "options.h"

#include <Arduino.h>
#include <Decorator.h>

class LogFileClass : public Decorator<Print> {
	static char log[LOGLINES][LOGCOLS];
	static uint16_t line;
	static uint8_t col;
	using Decorator::Decorator;
	size_t write(uint8_t c) override;
	/**
	 * @brief Get lines from log
	 * @param arr Array to copy pointers into
	 * @param from  Which line to start from. 0 = Most recent
	 * @param count How many lines to get
	 * @return An array of pointers to the requested lines
	 */
	const char** getPastLines(const char** arr, uint16_t from = 0, size_t count = LOGLINES-10);
};
extern LogFileClass LogFile;
extern Print* logger;