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
#include <ArduinoJson.h>

#include "Settings.h"
#include "Networking.h"

namespace WebUi {
AsyncWebServer server(80);
AsyncWebSocketMessageHandler wsHandler;
AsyncWebSocket ws("/ws", wsHandler.eventHandler());

void begin() {
	server.on("", HTTP_GET, [](AsyncWebServerRequest *request) {
		if (request->url().endsWith(".html") || request->url().endsWith(".htm")) {
			request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
				if (var == "HOSTNAME") {
					return WiFi.getHostname();
				}
				if (var == "VERSION") {
					return SMARTBULB_VERSION_STR;
				}
				if (var == "IP") {
					return WiFi.localIP().toString();
				}
				if (request->url().startsWith("/config/")) {
					String page = request->url();
					page.remove(page.indexOf(".htm"));
					page = page.substring(page.lastIndexOf("/"));
					if (Section::sections.contains(page.c_str())) {
						for (uint8_t i=0; i<Section::sections[page.c_str()].size; i++) {
							Settings* setting = Section::sections[page.c_str()].array[i];
							if (var == setting->getKey()) {
								return setting->getAsString();
							}
						}
					}
				}
				return emptyString;
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

	server.on("/config/", HTTP_PUT, [](AsyncWebServerRequest* request, JsonVariant& json) {
		log_d("Received settings for %s:\n%s", request->url(), json.as<String>());
		String url = request->url();
		url.remove(url.indexOf(".htm"));
		url = url.substring(url.lastIndexOf("/"));
		if (Section::sections.contains(url.c_str())) {
			for (uint8_t i=0; i<Section::sections[url.c_str()].size; i++) {
				Settings* setting = Section::sections[url.c_str()].array[i];
				const char* value = json[setting->getKey()].as<const char*>();
				if (value==NULL || !setting->setFromString(String(value))) {
					log_w("Could not set setting %s in section %s to value %s!", setting->getKey(), url, value);
				}
				json.remove(setting->getKey());
			}
			for (uint8_t i=0; i<json.size(); i++) {
				log_w("Setting %s does not exist in section %s!", json[i], url);
			}
		} else {
			log_e("Could not find setting section %s from url %s", url, request->url());
		}
		request->send(200);
	});

	server.begin();
}

} // namespace WebUi