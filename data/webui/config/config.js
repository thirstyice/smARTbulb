/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /data/webui/config/config.js                                       *
*                                                                              *
* Created: 2026-02-07                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
"use strict";

function saveSettings() {
	let inputs = document.getElementById("settings").getElementsByTagName("input");
	let selects = document.getElementById("settings").getElementsByTagName("select");
	let settings = {};
	for (const input of inputs) {
		if (input.value != input.placeholder) {
			settings[input.id] = input.value;
		}
	}
	for (const select of selects) {
		settings[select.id] = select.value;
	}
	fetch(document.URL.slice(0, document.URL.lastIndexOf(".htm")), {
		body: JSON.stringify(settings),
		keepalive: true,
		method: "PUT",
		headers: {
      "Content-Type": "application/json",
    },
	});
}

addEventListener("DOMContentLoaded", () => {
	document.getElementById("saveButton").addEventListener("click", saveSettings);
});
