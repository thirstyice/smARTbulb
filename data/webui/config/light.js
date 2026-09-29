/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /data/webui/config/light.js                                        *
*                                                                              *
* Created: 2026-09-29                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
"use strict";

function showModule(module) {
	for (const form of document.getElementById("modulesettings").getElementsByClassName("show")) {
		form.classList.remove("show");
	}
	document.getElementById("module" + module).classList.add("show");
}

function settingsUpdate(jsonData) {
	let lightSettings = jsonData.light;
	let moduleSettings = lightSettings.module;
	document.getElementById("module").value = moduleSettings.type;
	showModule(moduleSettings.type);

	let moduleForm = document.getElementById("module" + moduleSettings.type);
	for (const key in moduleSettings.settings) {
		moduleForm.querySelector("[name='" + key + "']").value = moduleSettings.settings[key];
	}

	let channelMap = lightSettings.chanmap;
	let chanmapForm = document.getElementById("chanmap");
	for (let input of chanmapForm.getElementsByTagName("input")) {
		input.value = channelMap[parseInt(input.name)];
	}
}

function saveSettings() {
	let settings = {
		module: {
			type: "none",
			settings: {}
		},
		chanmap: [-1, -1, -1, -1, -1],
	};
	settings.module.type = document.getElementById("module").value;
	let moduleForm = new FormData(document.getElementById("module" + settings.module.type));
	moduleForm.forEach((val, key) => {
		settings.module.settings[key] = val;
	});
	let chanMapForm = new FormData(document.getElementById("chanmap"));
	settings.chanmap.forEach((val, index) => {
		settings.chanmap[index] = chanMapForm.values[index]
	});

	let config = { light: settings };
	sendConfig(config);
}