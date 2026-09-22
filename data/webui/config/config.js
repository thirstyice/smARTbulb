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

async function loadSettings(file, count=0) {
  const response = await fetch(file);
	if (response.ok == false) {
		count++;
		console.error("Failed to get settings json!");
		if (count<5) {
			loadSettings(file, count);
		}
		return;
	}
	settingsUpdate(response.json());
}

function sendConfig(config) {
	fetch("/settings", {
		body: JSON.stringify(config),
		keepalive: true,
		method: "PUT",
		headers: {
      "Content-Type": "application/json",
    },
	});
}

addEventListener("DOMContentLoaded", () => {
	loadJSON("/settings");
	document.getElementById("saveButton").addEventListener("click", saveSettings);
});
