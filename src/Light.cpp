/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/Light.cpp                                                     *
*                                                                              *
* Created: 2026-10-13                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#include "Light.h"
#include "light/Module.h"

namespace light {
	volatile bool restart = true;
	TaskHandle_t handle;
	JsonVariantConst lightSettings = settingsDoc["light"];
	volatile uint8_t colors[Color::End];


	/**
	** @section Module definitions
	**
	**/

	#include "light/Template.h"
	#include "light/pwm.h"

Light* currentModule = nullptr;

	Light* modules[] = {
		&None,
		&PWM
	};

/**
** @section Internals
**
**/



int8_t getOutFromColor(Color color) {
	if (color>0 && color<Color::End) {
		return lightSettings["chanmap"].as<JsonArrayConst>()[(uint8_t)color];
	} else {
		return -1;
	}
}

void runLight() {
	for (uint8_t i=1; i<Color::End; i++) {
		uint16_t outValue = colors[i];
		outValue *= colors[Color::Intensity];
		currentModule->setOutput(getOutFromColor((Color)i), outValue);
	}
}
void beginLight() {
	log_i("Begin light");
	for (auto module : modules) {
		if (strcmp(module->name, lightSettings["module"]["type"].as<const char*>()) == 0) {
			currentModule = module;
		}
	}
	if (currentModule == nullptr) {
		currentModule = &None;
	}
	currentModule->begin();
	colors[Color::Intensity] = 255;
	colors[Color::Red] = 128;
	colors[Color::Green] = 0;
	colors[Color::Blue] = 255;
	colors[Color::Cool] = 32;
	colors[Color::Warm] = 64;
	runLight();
}
void endLight() {
	currentModule->end();
	currentModule = nullptr;
}
void lightTask(void*) {
	while (true) {
		if (restart) {
			restart = false;
			endLight();
			vTaskDelay(100);
			beginLight();
			vTaskDelay(500);
		} else {
			runLight();
		}
		vTaskDelay(20);
	}
}
}