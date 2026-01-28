/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/Log.cpp                                                       *
*                                                                              *
* Created: 2026-01-25                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#include <Log.h>


size_t Logger::write(uint8_t c) {
	log += c;
	return pointer->write(c);
};

Print* Log = new Logger{&Serial};