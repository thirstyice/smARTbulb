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


function addWifi(ssid="", pass="", ip="", gateway="", subnet="", index=-1) {
	var wifiDiv = document.getElementById("wifi");
	if (index == -1) {
		index = wifiDiv.childElementCount;
	}
	wifiDiv.append(
		"<div id='wifi" + index + "'>\
		<label>SSID:<input name='ssid' type='text' value='" + ssid + "' maxlength='32'></label>\
		<label>Pass:<input name='pass' type='text' value='" + pass + "' maxlength='63'></label>\
		<label>IP Address <small>(use 0.0.0.0 for DHCP)</small>:<input name='ip' type='text' pattern='[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}' value='" + ip  + "'></label>\
		<label>Gateway:<input name='gateway' type='text' pattern='[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}' value='" + gateway  + "'></label>\
		<label>Subnet:<input name='subnet' type='text' pattern='[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}' value='" + subnet  + "'></label>\
		<button name='remove' type='button' onclick='removeWifi(this.parentElement.id.replace('wifi', ''))'>Remove</button>\
		</div>"
	);
}

function removeWifi(index) {
	var wifiDiv = document.getElementById("wifi");
	wifiDiv.removeChild(document.getElementById("wifi" + index));
	for (let i=index; i<wifiDiv.childElementCount; i++) {
		document.getElementById("wifi" + (index+1)).id = "wifi" + index;
	}
}

function settingsUpdate(jsonData) {
	var networkSettings = jsonData["network"];
	var wifiSettings = networkSettings["wifi"];
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
	document.getElementById('apSSID').setAttribute("value", networkSettings.ap.ssid);
	document.getElementById("apPass").setAttribute("value", networkSettings.ap.pass);
}

function saveSettings() {
	var network;
	for (let i=0; i<wifiDiv.childElementCount; i++) {
		var wifiDiv = document.getElementById("wifi" + index);
		// TODO
	}
}