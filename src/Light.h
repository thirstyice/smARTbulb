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
** @brief Defines the common interface for Light objects
**
**/
class Light {
public:
	virtual void setI(uint8_t i) =0;
	virtual void setR(uint8_t r) =0;
	virtual void setG(uint8_t g) =0;
	virtual void setB(uint8_t b) =0;
	virtual void setCW(uint8_t cw) =0;
	virtual void setWW(uint8_t ww) =0;
	void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t cw, uint8_t ww) {
		setRGB(r, g, b); setWhite(cw, ww);
	}
	void setRGB(uint8_t r, uint8_t g, uint8_t b) {
		setR(r); setG(g); setB(b);
	}
	void setWhite(uint8_t cw, uint8_t ww) {
		setCW(cw); setWW(ww);
	}
	void set(uint8_t i, uint8_t r, uint8_t g, uint8_t b, uint8_t cw, uint8_t ww) {
		setI(i); setColor(r, g, b, cw, ww);
	}
	uint8_t getEnabledColors() {
		_getEnabledColors();
		return enabledColors;
	}
	virtual const char * getSettingName(uint8_t settingNum) =0; // For webui
	virtual const char * getTypeName() =0;
	virtual void setOutputMap(int8_t r=-1, int8_t g=-1, int8_t b=-1, int8_t cw=-1, int8_t ww=-1) =0; // -1 = disabled
	virtual bool hasRGB() =0;
	virtual bool hasCT() =0;
protected:
	uint8_t enabledColors = 0;
	virtual void _setEnabledColors(uint8_t) {}
	virtual void _getEnabledColors() {}

}; // class Light