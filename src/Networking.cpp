/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /src/Networking.cpp                                                *
*                                                                              *
* Created: 2026-01-25                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#include "Networking.h"
#include "webui/WebUi.h"

#include <WiFiMulti.h>
#include <DNSServer.h>


namespace Networking {

TaskHandle_t handle;

JsonVariantConst networkSettings = settingsDoc["network"];

WiFiMulti wifiMulti;

DNSServer dnsServer;

// WARNING: WiFiEvent is called from a separate FreeRTOS task (thread)!
void WiFiEvent(WiFiEvent_t event)
{
	switch (event) {
		case ARDUINO_EVENT_WIFI_READY:
				log_d("WiFi ready");
				break;
		case ARDUINO_EVENT_WIFI_SCAN_DONE:
				log_d("WiFi scan done");
				break;
		case ARDUINO_EVENT_WIFI_STA_START:
				log_d("WiFi started");
				break;
		case ARDUINO_EVENT_WIFI_STA_STOP:
				log_d("WiFi stopped");
				break;
		case ARDUINO_EVENT_WIFI_STA_CONNECTED:
				log_d("WiFi connected");
				break;
		case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
				log_d("WiFi disconnect");
				break;
		case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
				log_d("WiFi authmode");
				break;
		case ARDUINO_EVENT_WIFI_STA_GOT_IP:
				log_d("WiFi got IP");
				break;
		case ARDUINO_EVENT_WIFI_STA_LOST_IP:
				log_d("WiFi lost IP");
				break;
		case ARDUINO_EVENT_WIFI_AP_START:
				log_d("WiFi AP mode");
		default:
			break;
	}
}

void useAPMode() {
	log_i("Starting AP mode");
	WiFi.disconnect();
	WiFi.enableSTA(false);
	WiFi.enableAP(true);
	while (!WiFi.softAP(networkSettings["ap"]["ssid"].as<const char*>(), networkSettings["ap"]["pass"].as<const char*>())) {
		log_w("AP mode failure! Will try again");
		vTaskDelay(1000);
	}
	dnsServer.start(53, "*", WiFi.softAPIP());
}

void networkingTask(void*) {
	log_i("Begin Networking");
	WiFi.onEvent(WiFiEvent);
	WiFi.setHostname(networkSettings["hostname"].as<const char*>());
	WiFi.enableSTA(true);
	WiFi.STA.setDefault();
	for (JsonPairConst kv : networkSettings["wifi"].as<JsonObjectConst>()) {
		wifiMulti.addAP(kv.key().c_str(), kv.value().as<JsonVariantConst>()["pass"].as<const char*>());
	}
	uint8_t retries = 0;
	while (wifiMulti.run() != WL_CONNECTED) {
		if (retries >= networkSettings["retries"].as<uint8_t>()) {
			useAPMode();
			WebUi::begin();
			while (true) {
				vTaskDelay(1000);
			}
		}
		retries ++;
	}
	String ssid = WiFi.SSID();
	if (networkSettings["wifi"][ssid]["ip"].as<IPAddress>() != INADDR_NONE) {
		WiFi.config(
			networkSettings["wifi"][ssid]["ip"].as<IPAddress>(),
			networkSettings["wifi"][ssid]["gateway"].as<IPAddress>(),
			networkSettings["wifi"][ssid]["subnet"].as<IPAddress>()
		);
	}
	WebUi::begin();
	while (true) {
		if (WiFi.status() != WL_CONNECTED) {
			log_i("Reconnecting to wifi...");
			WiFi.reconnect();
		}
		vTaskDelay(3000);
	}
}

}