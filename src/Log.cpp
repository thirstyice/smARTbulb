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
#include "Log.h"

uint16_t LogFileClass::line = 0;
uint8_t LogFileClass::col = 0;

size_t LogFileClass::write(uint8_t c) {
	log[line][col] = c;
	col++;
	if (col>=LOGCOLS || c=='\n') {
		line++;
		col=0;
		if (line>=LOGLINES) {
			line=0;
		}
		memset(log[line], 0, sizeof(log[0]));
	}
	return pointer->write(c);
}
const char** LogFileClass::getPastLines(const char** arr, uint16_t startLine, size_t count) {
	if (startLine > line) {
		startLine = LOGLINES-(startLine-line);
	} else {
		startLine = line-startLine;
	}
	for (uint16_t i=0; i<count; i++) {
		arr[i] = log[startLine];
		if (startLine == 0) {
			startLine = LOGLINES;
		}
		startLine--;
	}
	return arr;
}

LogFileClass LogFile{&Serial};

Print* logger = &LogFile;