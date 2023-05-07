/***************************************************************************************************
 * Terminarium - MQTT communication
 * File: {@code mqtt.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#ifndef MQTT_H                                        
#define MQTT_H                                        // header guard

#include "rpcWiFi.h"                                  // import wifi library
#include "PubSubClient.h"                             // import mqtt library
//#include "credentials.h"    
extern WiFiClient wioClient;                          // wifi client 
extern PubSubClient client;                           // mqtt client 

#include "screen_draw.h"                              // include screen drawing functions
#include "screen_control.h"                           // include screen controlling functions
extern Screen screen;                                 // include global screen state variable in current scope        

// user network credentials
extern const char* SSID;                              // wifi network name
extern const char* PASSWORD;                          // wifi network password
extern const char* SERVER;                            // mqtt broker ip address

// topic for receiving messages
extern const char* TOPIC_SUB;

// topics are to be used for receiving user defined sensor ranges
extern const char* TOPIC_SUB_TEMP;
extern const char* TOPIC_SUB_HUMI;
extern const char* TOPIC_SUB_MOIST;
extern const char* TOPIC_SUB_LIGHT;
extern const char* TOPIC_SUB_LOUD;

// topics for sending sensor data
extern const char* TOPIC_PUB_TEMP;
extern const char* TOPIC_PUB_HUMI;
extern const char* TOPIC_PUB_VIB;
extern const char* TOPIC_PUB_MOIST;
extern const char* TOPIC_PUB_LIGHT;
extern const char* TOPIC_PUB_LOUD;


// ********************** CONNECT GENERAL **************************** //

// include global flag indicating connection is currently being established
extern bool isConnecting;

/* global flags denoting current connectivity 
 *NOTE: Only exists because of Fatal Error in screen_control when using the wifiConnected()/mqttConnected() functions */
extern bool wifiIsConnected;
extern bool mqttIsConnected;

// global flag indicating previous connection to wifi network
extern bool wifiWasConnected; 

// global flag indicating previous connection to mqtt server
extern bool mqttWasConnected;

// function calls wifi or mqtt connection depending on screen state context
extern void connect();

void maintainConnection();


// ************************ CONNECT WIFI ***************************** //

// function returns boolean indicating wifi connection status (used for readability)
extern bool wifiConnected();

// connect to wifi network and print status to serial monitor
extern void setupWifi();

// reconnect to wifi if connection lost during program loop
extern void reconnectWifi();


// ************************** CONNECT MQTT ***************************** //

// function returns boolean indicating mqtt connection status (used for readability)
extern bool mqttConnected();

// connect to mqtt broker and print status to serial monitor
extern void setupClient();

// reconnect to broker if connection lost during program loop
extern void reconnectClient();

// behavior when new message received from mqtt broker
extern void callback(char* topic, byte* payload, unsigned int length);

#endif
