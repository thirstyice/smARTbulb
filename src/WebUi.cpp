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
#include "light/Light.h"

namespace WebUi {
AsyncWebServer server(80);
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

void setSettings(Settings& settings, JsonVariant& json) {
	for (auto const setting : settings) {
		const char* value = json[setting.first].as<const char*>();
		if (value==NULL || !setting.second->setFromString(String(value))) {
			log_w("Could not set setting %s to value %s!", setting.first, value);
		} else {
			setting.second->save();
		}
		json.remove(setting.first);
	}
	for (uint8_t i=0; i<json.size(); i++) {
		log_w("Setting %s does not exist!", json[i]);
	}
}

void begin() {
	log_i("Begin WebUI");

	server.on("/config/network.html", HTTP_GET, [] (AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
			if (Networking::settings.contains(var.c_str())) {
				return Networking::settings[var.c_str()]->getAsString();
			}
			return getGenericVar(var);
		});
	});
	server.on("/config/network", HTTP_PUT, [](AsyncWebServerRequest* request, JsonVariant& json) {
		setSettings(Networking::settings, json);
		request->send(200);
	});


	server.on("/config/light.html", HTTP_GET, [] (AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
				if (var == "MODULES") {
					String out;
					for (const auto& [id, module] : light::modules) {
						out += "<option value='";
						out += String(id);
						out += "'>";
						out += module->name;
						out += "</option>\n";
					}
					if (light::settings.contains(var.c_str())) {
						return light::settings[var.c_str()]->getAsString();
					}
					return out;
				}
			return getGenericVar(var);
		});
	});
	server.on("/config/light", HTTP_PUT, [](AsyncWebServerRequest* request, JsonVariant& json) {
		setSettings(light::settings, json);
		request->send(200);
	});


	server.on("/config/module.html", HTTP_GET, [] (AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
			if (var == "GPIO") {
				String out = String("\0\0", 150);
				Light* module = light::modules[light::settings["moduleIndex"]->getAsString().toInt()];
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
	server.on("/config/module", HTTP_PUT, [](AsyncWebServerRequest* request, JsonVariant& json) {
		// TODO
	});


	server.on("/config/control.html", HTTP_GET, [] (AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
			// TODO
			return getGenericVar(var);
		});
	});
	server.on("/config/network", HTTP_PUT, [](AsyncWebServerRequest* request, JsonVariant& json) {
		// setSettings( ::settings, json);
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