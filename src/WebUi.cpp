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

void begin() {


	server.on("/config/network.html", HTTP_GET, [] (AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
			if (Settings::sections["network"].contains(var.c_str())) {
				return Settings::sections["network"][var.c_str()]->getAsString();
			}
			return getGenericVar(var);
		});
	});


	server.on("/config/light.html", HTTP_GET, [] (AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
			light::Color color = light::Color::End;
				if (var == "redChan") {
					color = light::Red;
				}
				if (var == "greenChan") {
					color = light::Green;
				}
				if (var == "blueChan") {
					color = light::Blue;
				}
				if (var == "coolChan") {
					color = light::Cool;
				}
				if (var == "warmChan") {
					color = light::Warm;
				}
				if (color != light::Color::End) {
					return String(light::Light::getOutputMap(color));
				}
				if (var == "MODULES") {
					String out;
					for (uint8_t i = 0; i < light::Light::numModules;
								i++) {
						out += "<option value='";
						out += String(i);
						out += "'>";
						out += light::Light::modules[i]->name;
						out += "</option>\n";
					}
					return out;
				}
			return getGenericVar(var);
		});
	});


	server.on("/config/module.html", HTTP_GET, [] (AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
			if (var == "GPIO") {
				String out = String("\0\0", 150);
				light::Light* module = light::Light::modules[light::Light::currentModuleIndex];
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
					if (Settings::sections["light"].contains(name)) {
						out += Settings::sections["light"][name]->getAsString();
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


	server.on("/config/control.html", HTTP_GET, [] (AsyncWebServerRequest *request) {
		request->send(LittleFS, "/webui" + request->url(), "text/html", false, [=](const String &var) -> String {
			// TODO
			return getGenericVar(var);
		});
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

	server.on("/config", HTTP_PUT, [](AsyncWebServerRequest* request, JsonVariant& json) {
		log_d("Received settings for %s:\n%s", request->url(), json.as<String>());
		String url = request->url();
		url.remove(url.indexOf(".htm"));
		url = url.substring(url.lastIndexOf("/")+1);
		if (Settings::sections.contains(url.c_str())) {
			for (auto const setting : Settings::sections[url.c_str()]) {
				const char* value = json[setting.first].as<const char*>();
				if (value==NULL || !setting.second->setFromString(String(value))) {
					log_w("Could not set setting %s in section %s to value %s!", setting.first, url, value);
				} else {
					setting.second->save(Settings::getPrefs(url.c_str()));
				}
				json.remove(setting.first);
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