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
#include "WebUi.h"

#include <WiFiMulti.h>
#include <DNSServer.h>


namespace Networking {
	volatile bool settingsDidUpdate = false;

	IPAddress ip = INITIAL_IP;
	IPAddress gateway = INITIAL_IP;
	IPAddress subnet = INITIAL_IP;
	std::map<String, String> wifi {{WIFI_INITIAL_SSID, WIFI_INITIAL_PASS}};
	String hostname = INITIAL_HOSTNAME;
	String apSSID = AP_SSID;
	String apPass = AP_PASS;

bool connected = false;

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
				if (ip.val != IPAddress(0UL)) {
					connected = true;
				}
				break;
		case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
				log_d("WiFi disconnect");
				connected = false;
				break;
		case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
				log_d("WiFi authmode");
				break;
		case ARDUINO_EVENT_WIFI_STA_GOT_IP:
				log_d("WiFi got IP");
				connected = true;
				break;
		case ARDUINO_EVENT_WIFI_STA_LOST_IP:
				log_d("WiFi lost IP");
				connected = false;
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
	while (!WiFi.softAP(apSSID, apPass)) {
		log_w("AP mode failure! Will try again");
		vTaskDelay(1000);
	}
	dnsServer.start(53, "*", WiFi.softAPIP());
}

void networkingTask(void*) {
	unsigned long beginTime;
	uint8_t mac[6];
	log_i("Begin Networking");
	if (hostname == INITIAL_HOSTNAME) {
		WiFi.macAddress(mac);
		hostname += "-";
		for (uint8_t i = 3; i<6; i++) {
			hostname += String(mac[i], 16);
		}
	}
	log_i("Begin WiFi");
	WiFi.onEvent(WiFiEvent);
	WiFi.setHostname(hostname.c_str());
	WiFi.enableSTA(true);
	WiFi.STA.setDefault();
	WiFi.config(ip, gateway, subnet);
	for (const auto& [ssid, pass] : wifi) {
		wifiMulti.addAP(ssid.c_str(), pass.c_str());
	}
	beginTime = millis();
	while (wifiMulti.run() != WL_CONNECTED) {
		if (millis() - beginTime > WIFI_TIMEOUT) {
			useAPMode();
			WebUi::begin();
			while (true) {
				vTaskDelay(1000);
			}
		}
	}
	WebUi::begin();
	while (true) {
		wifiMulti.run();
		vTaskDelay(2000);
	}
}

}