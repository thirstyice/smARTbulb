/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /webui/common.js                                                   *
*                                                                              *
* Created: 2026-01-20                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
"use strict"
addEventListener("DOMContentLoaded", (event) => {
	var collapseControl = document.getElementsByClassName("collapse-control");

	for (var i = 0; i < collapseControl.length; i++) {
		collapseControl[i].addEventListener("click", function() {
			var content = this.nextElementSibling;
			if (content.style.maxHeight){
				this.classList.remove("active");
				content.style.maxHeight = null;
			} else {
				this.classList.add("active");
				content.style.maxHeight = content.scrollHeight + "px";
			}
		});
	}
});