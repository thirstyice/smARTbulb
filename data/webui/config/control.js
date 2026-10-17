/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /data/webui/config/control.js                                      *
*                                                                              *
* Created: 2026-09-27                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
"use strict";

let controlSettings = {};

function settingsUpdate(jsonData) {
	controlSettings = jsonData.control;
	for (var key in controlSettings) {
		document.getElementById(key).value = controlSettings[key];
	}
}

function saveSettings() {
	let settings = {};
	for (var key of ["protocol", "universe", "address", "timeout"]) {
		let value = document.getElementById(key).value;
		if (value != controlSettings[key]) {
			settings[key] = value;
		}
	}
	let config = { control: settings };
	sendConfig(config);
}