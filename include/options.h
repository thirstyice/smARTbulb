/*******************************************************************************
* Project: smARTbulb                                                           *
* Filename: /include/options.h                                                 *
*                                                                              *
* Created: 2026-02-01                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see smARTbulb/LICENSE (if applicable)                            *
*                                                                              *
*******************************************************************************/
#pragma once
/**
** @file
** @brief Enable / disable features + compile-time options
**/

#include "user-options.h"

#include "smartbulb-version.h"

/**
** @brief Ethernet type
**
**/
#if !( \
	defined(ETH_PHY_TYPE) && \
	defined(ETH_PHY_ADDR) && \
	defined(ETH_PHY_MDC) && \
	defined(ETH_PHY_MDIO) && \
	defined(ETH_PHY_POWER) && \
	defined(ETH_CLK_MODE) \
)
	#define ETH_PHY_TYPE        ETH_PHY_LAN8720
	#define ETH_PHY_ADDR         1
	#define ETH_PHY_MDC         23
	#define ETH_PHY_MDIO        18
	#define ETH_PHY_POWER       -1
	#define ETH_CLK_MODE        ETH_CLOCK_GPIO17_OUT
#endif

/**
** @brief Initial network settings
**
**/
#ifndef WIFI_INITIAL_SSID
	#define WIFI_INITIAL_SSID "Test"
#endif
#ifndef WIFI_INITIAL_PASS
	#define WIFI_INITIAL_PASS "password"
#endif
#ifndef WIFI_INITIAL_SSID2
	#define WIFI_INITIAL_SSID2 WIFI_INITIAL_SSID
#endif
#ifndef WIFI_INITIAL_PASS2
	#define WIFI_INITIAL_PASS2 WIFI_INITIAL_PASS
#endif
#ifndef INITIAL_HOSTNAME
	#define INITIAL_HOSTNAME "smARTbulb"
#endif
#ifndef INITIAL_IP
	#define INITIAL_IP "0.0.0.0"
#endif
#ifndef INITIAL_SUBNET
	#define INITIAL_SUBNET "0.0.0.0"
#endif
#ifndef INITIAL_GATEWAY
	#define INITIAL_GATEWAY "0.0.0.0"
#endif

/**
** @brief How long to try to connect to wifi before switching to AP mode
**
**/
#ifndef WIFI_TIMEOUT
	#define WIFI_TIMEOUT 30000
#endif

/**
** @brief AP settings
**
**/
#ifndef AP_SSID
	#define AP_SSID "smARTbulb"
#endif
#ifndef AP_PASS
	#define AP_PASS "smartbulb"
#endif

/**
** @brief Logging options
**
**/
#ifndef Log
	#define Log logger // Print*, logs to log history and Serial by default
#endif
#ifndef LOGLINES
	#define LOGLINES 200
#endif
#ifndef LOGCOLS
	#define LOGCOLS 80
#endif
