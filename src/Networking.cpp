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

#include "options.h"

#include "Networking.h"
#include "Log.h"


namespace Networking {

IPAddress ip = INITIAL_IP;
IPAddress gateway = INITIAL_GATEWAY;
IPAddress subnet = INITIAL_SUBNET;
bool connected = false;

String wifiSSID1 = WIFI_INITIAL_SSID;
String wifiPasscode1 = WIFI_INITIAL_PASS;
String wifiSSID2 = WIFI_INITIAL_SSID2;
String wifiPasscode2 = WIFI_INITIAL_PASS2;
String hostname = INITIAL_HOSTNAME;

// WARNING: WiFiEvent is called from a separate FreeRTOS task (thread)!
void WiFiEvent(WiFiEvent_t event)
{
	switch (event) {
		case ARDUINO_EVENT_WIFI_READY:
				Log->println("WiFi ready");
				break;
		case ARDUINO_EVENT_WIFI_SCAN_DONE:
				Log->println("WiFi scan done");
				break;
		case ARDUINO_EVENT_WIFI_STA_START:
				Log->println("WiFi started");
				break;
		case ARDUINO_EVENT_WIFI_STA_STOP:
				Log->println("WiFi stopped");
				break;
		case ARDUINO_EVENT_WIFI_STA_CONNECTED:
				Log->println("WiFi connected");
				connected = true;
				break;
		case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
				Log->println("WiFi disconnect");
				connected = false;
				break;
		case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
				Log->println("WiFi authmode");
				break;
		case ARDUINO_EVENT_WIFI_STA_GOT_IP:
				Log->println("WiFi got IP");
				ip = WiFi.localIP();
				gateway = WiFi.gatewayIP();
				subnet = WiFi.subnetMask();
				connected = true;
				break;
		case ARDUINO_EVENT_WIFI_STA_LOST_IP:
				Log->println("WiFi lost IP");
				connected = false;
				break;

		default:
			break;
	}
}

void setupNetworking() {
	Log->println("Setup Network");
	WiFi.onEvent(WiFiEvent);
	WiFi.setHostname(hostname.c_str());
	WiFi.enableSTA(true);
	WiFi.STA.setDefault();
	WiFi.begin(wifiSSID1, wifiPasscode1);
	WiFi.config(ip, gateway, subnet);
}

}