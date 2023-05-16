/***************************************************************************************************
 * Terminarium - MQTT communication
 * File: {@code mqtt.cpp} [source file]
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#include "mqtt.h"                                     // include corresponding header file

WiFiClient wioClient;                                 // initialise wifi client
PubSubClient client(wioClient);                       // initialise mqtt client

/**
 * Note: This code was adapted from "MQTT on Wio Terminal" by Salman Faris
 * Link: https://www.hackster.io/Salmanfarisvp/mqtt-on-wio-terminal-4ea8f8 
 */

/***update these with values corresponding to your network***/
const char* SSID       = "******";                    // wifi network name
const char* PASSWORD   = "******";                    // wifi network password
const char* SERVER     = "broker.hivemq.com";         // mqtt broker address

// topic for receiving messages
const char* TOPIC_SUB = "/terminarium/app/signal";

// topics used for receiving user defined sensor ranges 
const char* TOPIC_SUB_TEMP  = "/terminarium/app/range/temperature";
const char* TOPIC_SUB_HUMI  = "/terminarium/app/range/humidity";
const char* TOPIC_SUB_MOIST = "/terminarium/app/range/moisture";
const char* TOPIC_SUB_LIGHT = "/terminarium/app/range/light";
const char* TOPIC_SUB_LOUD  = "/terminarium/app/range/loudness";

// topics for publishing sensor data
const char* TOPIC_PUB_TEMP  = "/terminarium/sensor/temperature";
const char* TOPIC_PUB_HUMI  = "/terminarium/sensor/humidity";
const char* TOPIC_PUB_VIB   = "/terminarium/sensor/vibration";
const char* TOPIC_PUB_MOIST = "/terminarium/sensor/moisture";
const char* TOPIC_PUB_LIGHT = "/terminarium/sensor/light";
const char* TOPIC_PUB_LOUD  = "/terminarium/sensor/loudness";


// ********************** CONNECT GENERAL **************************** //

bool wifiWasConnected = false;            // global flag denoting previous connection to mqtt server, false by default
bool mqttWasConnected = false;            // global flag denoting previous connection to wifi network, false by default

/**
 * @connect: call functions to either connect to wifi or mqtt depending on screen state context.
 * It's either one or the other per interval, otherwise oldScreen won't update correctly. 
 */
void connect() {            
  if(screen == CONNECT_WIFI) {
    setupWifi();                          
  } else if (screen == CONNECT_MQTT) {
    setupClient();                       
  }
} 

void maintainConnection() {               // maintain or recover connection if it was first established but then lost
  if(wifiConnected()) {
    wifiWasConnected = true;              // maintain true value of variable so specific behaviors occur after connection lost
  }
  if(mqttConnected()) {
    mqttWasConnected = true;              // maintain true value of variable so specific behaviors occur after connection lost
    client.loop();                        // stay connected and listening to mqtt broker 
  }
  if(wifiWasConnected && !wifiConnected() && screen != CONNECT_SELECT && screen != CONNECT_WIFI && screen != CONNECT_MQTT) {
    Serial.print("Connection to Wi-Fi network lost.");  // print connection loss message to serial monitor
    mqttWasConnected = false;                           // set to false so conditional below doesn't trigger when wifi is lost
    goConnSelectScreen();                               // change screen to ask if user wants to reconnect
  } else if (mqttWasConnected && !mqttConnected() && screen != CONNECT_SELECT && screen != CONNECT_WIFI && screen != CONNECT_MQTT) {
    Serial.println("Connection to MQTT server lost");   // print connection mqtt loss message to serial monitor
    goConnSelectScreen();                               // change screen to ask if user wants to reconnect
  } 
}


// ************************ CONNECT WIFI ***************************** //

// return boolean indicating connection status (used for readability)
bool wifiConnected() {
  if(WiFi.status() == WL_CONNECTED) {
    return true;
  } else {
    return false;
  }
}

// connect to wifi network and print status to serial monitor
void setupWifi() {

  Serial.print("\nConnecting to Wi-Fi network: ");    // print name of wifi network in serial monitor
  Serial.print(SSID);
  WiFi.begin(SSID, PASSWORD);                         // connect to wifi network

  while (!wifiConnected()) {                          // loop while not connected to wifi
    drawDotDotDot(strlen(SSID), getCenterX(toString(SSID)), 169);
    Serial.print(".");                                // print dot..dot..dot... to serial monitor
    WiFi.begin(SSID, PASSWORD);                       // reattempt connection
  }

  drawConnectedText();                                // draw affirmative message on LCD screen upon succesful connection
  Serial.println("\nWiFi connected!");                // display affirmative message on serial monitor
  Serial.println("IP address: ");                     
  Serial.println(WiFi.localIP());                     // display local ip address on serial monitor
  SEPARATOR;                                          // visual separator for serial monitor   
  
  delay(2000);                                        // arbitrary delay for visual "Connected" text on LCD screen 
  screen = CONNECT_MQTT;                              // change screen state to proceed with connection
} 

// reconnect to wifi if connection lost during program loop
void reconnectWifi() {
  Serial.print("Connection to Wi-Fi network lost.");  // print reconnect-specific message to serial monitor
  setupWifi();                                        // call wifi connection function
}


// ************************** CONNECT MQTT ***************************** //

// return boolean indicating mqtt connection status (used for readability)
bool mqttConnected() {
  if (client.connected()) {
    return true;
  } else {
    return false;
  }
}

// connect to mqtt broker and print status to serial monitor
void setupClient() {                    
  Serial.println("Attempting MQTT connection...");  
  String clientID = "Terminarium-wio-terminal";       // create a client ID
  client.connect(clientID.c_str());                   // connect to mqtt broker

  while(!client.connected()) {                        // loop while not connected to broker
    drawDotDotDot(strlen(SERVER), getCenterX(toString(SERVER)), 169);
    Serial.print("Failed, return code = ");           // print error message
    Serial.println(client.state());                   // print client state (error code as int value that represents additional info on specific error) 
    Serial.println("Trying again");      
    Serial.print(".");                                // wait 5 seconds before retrying
    client.connect(clientID.c_str());                 // reattempt connection
  }

  drawConnectedText();                                // draw affirmative message on LCD screen upon succesful connection
  Serial.println("Connected!");                       // if succesful, print affirmative message to serial monitor
  client.subscribe(TOPIC_SUB);                        // subscribe to topics
  client.subscribe(TOPIC_SUB_TEMP);
  client.subscribe(TOPIC_SUB_HUMI);
  client.subscribe(TOPIC_SUB_MOIST);
  client.subscribe(TOPIC_SUB_LIGHT);
  client.subscribe(TOPIC_SUB_LOUD);


  Serial.print("Subcribed to: ");                     // print topic subscribed to as a string
  Serial.println(TOPIC_SUB);                      
  SEPARATOR;                                          // visual separator for serial monitor

  delay(2000);                                        // arbitrary delay for visual "Connected" text on LCD screen 
  screen = DASHBOARD;
} 

unsigned long lastUpdateTime = 0;                     // global timestamp indicating the last time (in ms) update occurred

// behavior when new message received from mqtt broker
void callback(char* topic, byte* payload, unsigned int length) {
  screen = UPDATE;                                    // set corresponding update screen

  // print affirmative message 
  Serial.print("Message arrived [" + String(topic) + "]: ");  

  // process payload and convert it to a string
  char buff_p[length];
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    buff_p[i] = (char)payload[i];
  }
    //update array values
  if(updateSensorRanges(topic, buff_p, length)) {
    Serial.println("Succesfully updated sensor ranges");
  } else {
      Serial.println("Sensor ranges not updated succesfully");
  }

  Serial.println();
  buff_p[length] = '\0';
  String message = String(buff_p);

  lastUpdateTime = millis();                          // update timestamp for last update time
}