/*
 * Project: smARTbulb                                                          *
 * Filename: /webui/index.js                                                   *
 *                                                                             *
 * Created: 2026-01-19                                                         *
 * Author: thirstyice                                                          *
 *                                                                             *
 * Copyright (c) 2026 Tauran - https://github.com/thirstyice                   *
 * For details see smARTbulb/LICENSE (if applicable)                           *
 *                                                                             *
 */
"use strict"

var colorPicker;
var whitePicker;
var color = new iro.Color("#000");
var white = new iro.Color("#000");

var wsGateway = `ws://${window.location.hostname}/ws`;
var ws;
var wsConnected = false;

var liveInfo = [];
var infoRequest;

function updateLiveData() {
	let live = [];
	for (element of document.getElementsByClassName("live")) {
		live.push(element.id);
	}
	if (document.getElementById("info-collapse").classList.contains("active")) {
		for (element of document.getElementsByClassName("info")) {
			live.push(element.id);
		}
	}
	if (liveInfo != live) {
		liveInfo=live;
		console.debug("liveInfo updated:");
		console.debug(liveInfo);
	}
}

function requestData() {
	if (!wsConnected) {
		return;
	}
	ws.send(JSON.stringify(liveInfo));
	infoRequest = setTimeout(requestData, 1500);
	updateLiveData();
}

function wsOpen(event) {
	wsConnected = true;
	requestData();
}
function wsClose(event) {
	wsConnected = false;
	setTimeout(beginWebSocket, 1500);
}
function wsMessage(event) {
	clearTimeout(infoRequest);
	let data = JSON.parse(event.data);
	console.debug("WebSocket data received");
	console.debug(data);

	if ((data.source != undefined) && (data.source != "webui")) {
		document.getElementById("pickers").style.display = "none";
		document.getElementById("override").style.display = "block";
	} else {
		whitePicker.color = white;
		document.getElementById("pickers").style.display = "block";
		document.getElementById("override").style.display = "none";
	}
	if (data.color != undefined) {
		color.red = data.color.red??0;
		color.green = data.color.green??0;
		color.blue = data.color.blue??0;
		document.getElementById("rgbvalue").style.backgroundColor = color.hexString;

		white.rgb = iro.Color.kelvinToRgb(2265 + ((data.color.balance??127) * 34));
		white.value = data.color.white??0;
		document.getElementById("whitevalue").style.backgroundColor = white.hexString;

		delete data.color;
	}
	for (key in data) {
		document.getElementById(key).innerHTML = data[key];
	}
	infoRequest = setTimeout(requestData, 1000);
}
function wsError(event) {
	console.warn("WebSocket error!");
	console.warn(event);
}
function beginWebSocket() {
	ws = new WebSocket(wsGateway);
	ws.addEventListener("open", wsOpen);
	ws.addEventListener("error", wsError);
	ws.addEventListener("close", wsClose);
	ws.addEventListener("message", wsMessage);
}

addEventListener("DOMContentLoaded", (event) => {
	beginWebSocket();
	if (colors.includes("R") && colors.includes("G") && colors.includes("B")) {
		colorPicker = new iro.ColorPicker("#color-picker", {
			width: 300,
			color: "#f0f",
			wheelLightness: false,
		});
	} else {
		let colorLayout = [];
		if (colors.includes("R")) {
			colorLayout.push({
				component: iro.ui.Slider,
				options: {
					sliderType: "red"
				}
			});
		}
		if (colors.includes("G")) {
			colorLayout.push({
				component: iro.ui.Slider,
				options: {
					sliderType: "green"
				}
			});
		}
		if (colors.includes("B")) {
			colorLayout.push({
				component: iro.ui.Slider,
				options: {
					sliderType: "blue"
				}
			});
		}
		if (colorLayout != []) {
			colorPicker = new iro.ColorPicker("#color-picker", {
				width: 300,
				layout: colorLayout
			});
		}
	}
	if (colorPicker == undefined) {
		document.getElementById("rgbvalue").style.display = "none";
	}
	let whiteLayout = [];
	if ((colors.includes("W") && colors.includes("C")) || (colors.split("W").length > 2)) {
		whiteLayout.push({
			component: iro.ui.Slider,
			options: {
				sliderType: "kelvin",
				minTemperature: 2265,
				maxTemperature: 10935,
			}
		});
	}
	if (colors.includes("W")) {
		whiteLayout.push({
			component: iro.ui.Slider,
			options: {
				sliderType: "value",
			}
		});
	}
	if (whiteLayout != []) {
		whitePicker = new iro.ColorPicker("#white-picker", {
			width: 300,
			layout: whiteLayout
		});
	}
	if (whitePicker == undefined) {
		document.getElementById("whitevalue").style.display = "none";
	}
	var overrideControl = document.getElementById("override");
	overrideControl.addEventListener("click", function() {
		if (this.classList.contains("active")) {
			ws.send("disableoverride");
			this.classList.remove("active");
		} else {
			if (window.confirm("Are you sure you want to override live data?")) {
				ws.send("enableoverride");
				this.classList.add("active");
			}
		}
	});
});