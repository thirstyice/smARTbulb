/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/WebUi.cpp                                                     *
*                                                                              *
* Created: 2026-02-02                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#include "shared.h"
#include <AsyncJson.h>
#include "../Networking.h"
#include "../light/Light.h"
#include "../smartbulb-version.h"

namespace WebUi {
AsyncWebSocketMessageHandler wsHandler;
AsyncWebSocket ws("/ws", wsHandler.eventHandler());

String getGenericVar(String var) {
	if (var == "HOSTNAME") {
		return WiFi.getHostname();
	}
	if (var == "VERSION") {
		return SMARTBULB_VERSION_STR;
	}
	if (var == "IP") {
		if (WiFi.getMode() == WIFI_MODE_AP) {
			return WiFi.softAPIP().toString();
		}
		return WiFi.localIP().toString();
	}
	return emptyString;
}

void begin() {
	log_i("Begin WebUI");

	server.on("/settings", HTTP_PUT, [](AsyncWebServerRequest* request, JsonVariant& json) {
		// TODO: Set settings
		request->send(200);
	});

	server.on("/settings", HTTP_GET, [](AsyncWebServerRequest* request) {
		AsyncResponseStream* response = request->beginResponseStream("application/json");
		serializeJson(settingsDoc, *response);
		request->send(response);
	});


	server.on("", HTTP_GET, [](AsyncWebServerRequest *request) {
		if (request->url().endsWith(".html") || request->url().endsWith(".htm")) {
			request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
				return getGenericVar(var);
			});
		} else {
			request->send(LittleFS, "/webui" + request->url());
		}
	});

	server.rewrite("/", "/index.html");

	wsHandler.onConnect([](AsyncWebSocket *server, AsyncWebSocketClient *client) {

	});

	wsHandler.onDisconnect([](AsyncWebSocket *server, uint32_t clientId) {

	});

	wsHandler.onError([](AsyncWebSocket *server, AsyncWebSocketClient *client, uint16_t errorCode, const char *reason, size_t len) {

	});

	wsHandler.onMessage([](AsyncWebSocket *server, AsyncWebSocketClient *client, const uint8_t *data, size_t len) {

	});

	server.begin();
}

} // namespace WebUi