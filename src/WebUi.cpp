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
#include "WebUi.h"

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

#include "Networking.h"

namespace WebUi {
AsyncWebServer server(80);
AsyncWebSocketMessageHandler wsHandler;
AsyncWebSocket ws("/ws", wsHandler.eventHandler());

void begin() {
	server.on("*.html", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
			if (var == "HOSTNAME") {
				return WiFi.getHostname();
			}
			if (var == "VERSION") {
				return SMARTBULB_VERSION_STR;
			}
			if (request->url().startsWith("/config")) {
				if (var == "IP") {
					return Networking::ip.toString();
				}
				if (var == "SSID1") {
					return Networking::wifiSSID1;
				}
				if (var == "SSID2") {
					return Networking::wifiSSID2;
				}
				if (var == "SUBNET") {
					return Networking::subnet.toString();
				}
				if (var == "GATEWAY") {
					return Networking::gateway.toString();
				}
			}
			if (var == "IP") {
				return WiFi.localIP().toString();
			}
			return emptyString;
		});
	});
	server.on("", HTTP_GET, [](AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url());
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