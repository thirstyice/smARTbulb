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
#define ETH_PHY_TYPE        ETH_PHY_LAN8720
#define ETH_PHY_ADDR         1
#define ETH_PHY_MDC         23
#define ETH_PHY_MDIO        18
#define ETH_PHY_POWER       -1
#define ETH_CLK_MODE        ETH_CLOCK_GPIO17_OUT


#include "Networking.h"


namespace Networking {

IPAddress ip = IPAddress(192,168,0,201);
IPAddress gateway = IPAddress(192,168,0,1);
IPAddress subnet = IPAddress(255,255,255,0);
bool connected = false;

String wifiSSID1 = "Test";
String wifiPasscode1 = "password";
String wifiSSID2 = "network";
String wifiPasscode2 = "password";
String hostname = "smARTbulb";

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
	WiFi.begin(wifiSSID, wifiPasscode);
	WiFi.config(ip, gateway, subnet);
}

}