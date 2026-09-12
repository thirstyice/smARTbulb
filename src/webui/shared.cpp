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
#include "../Networking.h"
#include "../light/Light.h"

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

void setupConfigGet() {
	server.on("/config/*.html", HTTP_GET, [] (AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
			String filename = request->url().substring(request->url().lastIndexOf("/"), request->url().lastIndexOf("."));
			log_i("HTTP GET: %s", filename.c_str());
			JsonVariant json = settingsDoc[].as<JsonVariant>();
			if (json.containsKey(var)) {
				return json[var].as<String>();
			}
			if (var == "MODULES") {
				String out;
				for (uint8_t i=0; i<light::numModules; i++) {
					out += "<option value='";
					out += String(i);
					out += "' ";
					if (i == light::moduleIndex) {
						out += "selected ";
					}
					out += ">";
					out += light::modules[i]->name;
					out += "</option>\n";
				}
				return out;
			}
			if (var == "GPIO") {
				String out = "";
				out.reserve(150);
				Light* module = light::modules[light::moduleIndex];
				for (uint8_t i=0; i<module->numGPIO; i++) {
					char name[8];
					snprintf(name, 8, "gpio%d", i);
					out += "<tr>\n<td><label for='";
					out += name;
					out += "'>";
					out += module->gpioNames[i];
					out += "</label></td>\n<td><input id='";
					out += name;
					out += "' type='number' min='-1' max='40' value='";
					if (light::settings.contains(name)) {
						out += light::settings[name]->getAsString();
					} else {
						out += "-1";
					}
					out += "'></td>\n</tr>\n";
				}
				return out;
			}
			return getGenericVar(var);
		});
	});
}

void begin() {
	log_i("Begin WebUI");

	setupConfigGet();


	server.on("/config/module.html", HTTP_GET, [] (AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {

			return getGenericVar(var);
		});
	});


	server.on("/config/control.html", HTTP_GET, [] (AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
			// TODO
			return getGenericVar(var);
		});
	});
	server.on("/config", HTTP_PUT, [](AsyncWebServerRequest* request, JsonVariant& json) {
		setSettings( Networking::settings, json);
		// TODO: Restart networking, so settings take effect
		request->send(200);
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