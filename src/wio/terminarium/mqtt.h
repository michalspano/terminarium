/***************************************************************************************************
 * Terminarium - MQTT communication
 * File: {@code mqtt.h} [header file] 
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#ifndef MQTT_H                                        
#define MQTT_H                                        // header guard

#include "rpcWiFi.h"                                  // import wifi library
#include "PubSubClient.h"                             // import mqtt library
    
extern WiFiClient wioClient;                          // wifi client 
extern PubSubClient client;                           // mqtt client 

#include "screen_draw.h"                              // import screen drawing functions
#include "utils.h"                                    // import utility functions
#include "screen_control.h"                           // import screen controlling functions
extern Screen screen;                                 // include global screen state variable in current scope        

// user network credentials
extern char* SSID;                                    // wifi network name
extern char* PASSWORD;                                // wifi network password
extern char* SERVER;                                  // mqtt broker ip address

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

// global flag indicating previous connection to wifi network
extern bool wifiWasConnected; 

// global flag indicating previous connection to mqtt server
extern bool mqttWasConnected;

// function calls wifi or mqtt connection depending on screen state context
extern void connect();

// maintain or recover connection if it was first established but then lost
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

// global timestamp indicating the last time (in ms) update occurred
extern unsigned long lastUpdateTime;

// behavior when new message received from mqtt broker
extern void callback(char* topic, byte* payload, unsigned int length);

#endif                                                // end header guard  
