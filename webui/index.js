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

addEventListener("DOMContentLoaded", (event) => {
	colorPicker = new iro.ColorPicker("#color-picker", {
		width: 300,
		color: "#f0f",
		wheelLightness: false,
	});
	whitePicker = new iro.ColorPicker("#white-picker", {
		width: 300,
		layout: [
			{
				component: iro.ui.Slider,
				options: {
					sliderType: "kelvin",
				}
			},
			{
				component: iro.ui.Slider,
				options: {
					sliderType: "value",
				}
			}
		]
	});
});