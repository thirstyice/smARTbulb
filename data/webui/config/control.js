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

function settingsUpdate(jsonData) {
	let controlSettings = jsonData.control;
	for (var key in controlSettings) {
		document.getElementById(key).value = controlSettings[key];
	}
}

function saveSettings() {
	let settings = {
		protocol: "none",
		universe: 1,
		address: 1,
		timeout: 5000
	};
	for (var key in settings) {
		settings[key] = document.getElementById(key).value;
	}
	let config = { control: settings };
	sendConfig(config);
}