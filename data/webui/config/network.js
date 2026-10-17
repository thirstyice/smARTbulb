/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /data/webui/config/network.js                                      *
*                                                                              *
* Created: 2026-09-22                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
'use strict';

let networkSettings = {};

function addWifi(ssid="", pass="", ip="", gateway="", subnet="", index=-1) {
	var wifiDiv = document.getElementById("wifi");
	if (index == -1) {
		index = wifiDiv.childElementCount;
	}
	const newWifi = document.createElement("form");
	wifiDiv.appendChild(newWifi);
	newWifi.outerHTML =
		'<form class="subform" id="wifi' + index + '">\
		<label>SSID:<input name="ssid" type="text" value="' + ssid + '" maxlength="32"></label>\
		<label>Pass:<input name="pass" type="text" value="' + pass + '" maxlength="63"></label>\
		<label>IP Address <small>(0.0.0.0 for DHCP)</small>:<input name="ip" type="text" pattern="[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}" value="' + ip  + '"></label>\
		<label>Gateway:<input name="gateway" type="text" pattern="[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}" value="' + gateway  + '"></label>\
		<label>Subnet:<input name="subnet" type="text" pattern="[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}" value="' + subnet  + '"></label>\
		<button name="remove" type="button" onclick="removeWifi(this.parentElement.id.replace(\'wifi\', \'\'))">Remove</button>\
		</form>'
	;
}

function removeWifi(index) {
	let wifiDiv = document.getElementById("wifi");
	wifiDiv.removeChild(document.getElementById("wifi" + index));
	for (let i=parseInt(index); i<wifiDiv.childElementCount; i++) {
		console.log(i+1);
		console.log("wifi" + (i+1));
		document.getElementById("wifi" + (i+1)).id = "wifi" + i;
	}
}

function settingsUpdate(jsonData) {
	networkSettings = jsonData.network;
	let wifiSettings = networkSettings.wifi;
	for (var wifi in wifiSettings) {
		addWifi(
			wifi,
			wifiSettings[wifi].pass,
			wifiSettings[wifi].ip,
			wifiSettings[wifi].gateway,
			wifiSettings[wifi].subnet
		);
	}
	document.getElementById('hostname').setAttribute("value", networkSettings.hostname);
	document.getElementById('apSSID').setAttribute("value", networkSettings.apSSID);
	document.getElementById("apPass").setAttribute("value", networkSettings.apPass);
	document.getElementById("retries").value = networkSettings.retries;
}

function saveSettings() {
	let settings = {};
	let wifi = {};
	for (let i=0; i<document.getElementById("wifi").childElementCount; i++) {
		let wifiFormData = new FormData(document.getElementById("wifi" + i));
		let ssid = wifiFormData.ssid;
		wifiFormData.forEach((value, key) => {
			if (key == "ssid") {
				return;
			}
			wifi[ssid][key] = value;
		});
	}
	if (wifi != networkSettings.wifi) {
		settings.wifi = wifi;
	}
	for (let key of ["hostname", "retries", "apSSID", "apPass"]) {
		let val = document.getElementById(key).value;
		if (val != networkSettings[key]) {
			settings[key] = val;
		}
	}
	let config = { network: settings };
	sendConfig(config);
}