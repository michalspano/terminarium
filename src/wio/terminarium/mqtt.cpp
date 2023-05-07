/***************************************************************************************************
 * Terminarium - MQTT communication
 * File: {@code mqtt.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#include "mqtt.h"                                     // include corresponding header file

WiFiClient wioClient;                                 // initialise wifi client
PubSubClient client(wioClient);                       // initialise mqtt client

/* Note: This code was adapted from "MQTT on Wio Terminal" by Salman Faris
* Link: https://www.hackster.io/Salmanfarisvp/mqtt-on-wio-terminal-4ea8f8 */

/***update these with values corresponding to your network***/
const char* SSID       = "######";                    // wifi network name
const char* PASSWORD   = "######";                    // wifi network password
const char* SERVER     = "######";                    // mqtt broker ip address (use ipconfig command and see IPv4 address)

// topic for receiving messages
const char* TOPIC_SUB = "/terminarium/app/signal";

/*These topics are to be used for receiving user defined sensor ranges 
* Note: the format of the message shall be two integers < 100 & > 0 separated by a ',' and no spaces - '##,##'
* Max value followed by min value
* Single digit numbers must start with 0 - e.g 05, 06 */
const char* TOPIC_SUB_TEMP  = "/terminarium/app/range/temperature";
const char* TOPIC_SUB_HUMI  = "/terminarium/app/range/humidity";
const char* TOPIC_SUB_MOIST = "/terminarium/app/range/moisture";
const char* TOPIC_SUB_LIGHT = "/terminarium/app/range/light";
const char* TOPIC_SUB_LOUD  = "/terminarium/app/range/loudness";

// topics for sending sensor data
const char* TOPIC_PUB_TEMP  = "/terminarium/sensor/temperature";
const char* TOPIC_PUB_HUMI  = "/terminarium/sensor/humidity";
const char* TOPIC_PUB_VIB   = "/terminarium/sensor/vibration";
const char* TOPIC_PUB_MOIST = "/terminarium/sensor/moisture";
const char* TOPIC_PUB_LIGHT = "/terminarium/sensor/light";
const char* TOPIC_PUB_LOUD  = "/terminarium/sensor/loudness";


// ********************** CONNECT GENERAL **************************** //

bool isConnecting = false;                // global flag denoting connection is currently being established
bool wifiIsConnected = false;             // global flag denoting wifi connectivity **NOTE: Only exists because of Fatal Error in Screen Control when using wifiConnected() function**
bool mqttIsConnected = false;             // global flag denoting mqtt connectivity **NOTE: Only exists because of Fatal Error in Screen Control when using mqttConnected() function**
bool wifiWasConnected = false;            // global flag denoting previous connection to mqtt server, false by default
bool mqttWasConnected = false;            // global flag denoting previous connection to wifi network, false by default

void connect() {                          // call functions to connect to wifi or mqtt depending on screen state context
  if(screen == CONNECT_WIFI) {
    setupWifi();                          // connect to wifi network
  } else if (screen == CONNECT_MQTT) {
    setupClient();                        // connect to mqtt broker
  }
} 

void maintainConnection() {               // maintain or recover connection if it was established but lost
  if(mqttConnected()) {
    client.loop();                        // stay connected and listening to mqtt broker
  }
  if(wifiWasConnected && !wifiConnected() & !isConnecting && screen != CONNECT_SELECT) {
    Serial.print("Connection to Wi-Fi network lost.");  // print connection loss message to serial monitor
    goConnSelectScreen();
  } else if (mqttWasConnected && !mqttConnected() & !isConnecting && screen != CONNECT_SELECT) {
    Serial.println("Connection to MQTT server lost");   // print connection loss message to serial monitor
    goConnSelectScreen();
  } 
}


// ************************ CONNECT WIFI ***************************** //

// return boolean indicating connection status (used for readability)
bool wifiConnected() {
  if(WiFi.status() == WL_CONNECTED) {
    wifiIsConnected = true;                           // temporary workaround
    return true;
  } else {
    wifiIsConnected = false;                          // temporary workaround 
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
  wifiWasConnected = true;                            // udpate flag to indicate that wifi connection was previously established
  Serial.println("\nWiFi connected!");                // display affirmative message on serial monitor
  Serial.println("IP address: ");                     
  Serial.println(WiFi.localIP());                     // display local ip address on serial monitor
  SEPARATOR;                                          // visual separator for serial monitor   
  
  delay(2000);
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
    mqttIsConnected = true;                           // temporary workaround 
    return true;
  } else {
    mqttIsConnected = false;                          // temporary workaround 
    return false;
  }
}

// connect to mqtt broker and print status to serial monitor
void setupClient() {                    
  Serial.println("Attempting MQTT connection...");  
  String clientID = "WioTerminal";                    // create a client ID
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
  isConnecting = false;                               // update flag to indicate that connecting process is over
  mqttWasConnected = true;                            // udpate flag to indicate that mqtt connection was previously established
  client.subscribe(TOPIC_SUB);                        // subscribe to topics
  client.subscribe(TOPIC_SUB_TEMP);
  client.subscribe(TOPIC_SUB_HUMI);
  client.subscribe(TOPIC_SUB_MOIST);
  client.subscribe(TOPIC_SUB_LIGHT);
  client.subscribe(TOPIC_SUB_LOUD);


  Serial.print("Subcribed to: ");                     // print topic subscribed to as a string
  Serial.println(TOPIC_SUB);                      
  SEPARATOR;                                          // visual separator for serial monitor

  delay(2000);
  screen = DASHBOARD;
} 


// behavior when new message received from mqtt broker
void callback(char* topic, byte* payload, unsigned int length) {

  // print affirmative message 
  Serial.print("Message arrived [" + String(topic) + "]: ");  

  // process payload and convert it to a string
  char buff_p[length];
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    buff_p[i] = (char)payload[i];
  }
  //update array values
 if(updateSensorRanges(topic, buff_p, length)){
   Serial.println(" Succesfully updated sensor ranges");
   Serial.println(userDefinedRanges[0][0]);
 } else {
      Serial.println("Sensor ranges not updated succesfully");
 }


  Serial.println();
  buff_p[length] = '\0';
  String message = String(buff_p);
}