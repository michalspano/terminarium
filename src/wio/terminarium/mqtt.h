/***************************************************************************************************
 * Terminarium - MQTT communication
 * File: {@code mqtt.h}
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#include "rpcWiFi.h"                                  // import wifi library
#include "PubSubClient.h"                             // import mqtt library
//#include "credentials.h" 

extern Screen screen;                                 // include global screen state variable in current scope                  
WiFiClient wioClient;                                 // initialise wifi client
PubSubClient client(wioClient);                       // initialise mqtt client

/* Note: This code was adapted from "MQTT on Wio Terminal" by Salman Faris
* Link: https://www.hackster.io/Salmanfarisvp/mqtt-on-wio-terminal-4ea8f8 */

/***update these with values corresponding to your network***/
const char* SSID       = "HUAWEI P30 Pro";                    // wifi network name
const char* PASSWORD   = "12345678";                    // wifi network password
const char* SERVER     = "192.168.43.86";                    // mqtt broker ip address (use ipconfig command and see IPv4 address)

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

// topic for sending sensor data
const char* TOPIC_PUB_TEMP  = "/terminarium/sensor/temperature";
const char* TOPIC_PUB_HUMI  = "/terminarium/sensor/humidity";
const char* TOPIC_PUB_VIB   = "/terminarium/sensor/vibration";
const char* TOPIC_PUB_MOIST = "/terminarium/sensor/moisture";
const char* TOPIC_PUB_LIGHT = "/terminarium/sensor/light";
const char* TOPIC_PUB_LOUD  = "/terminarium/sensor/loudness";


// ************************ CONNECT WIFI ***************************** //

bool wifiConnected() {
  if(WiFi.status() == WL_CONNECTED) {
    return true;
  } else {
    return false;
  }
}

// connect to wifi network and print status to serial monitor
void setupWifi() {

  WiFi.begin(SSID, PASSWORD);                         // connect to wifi network
  Serial.print("\nConnecting to Wi-Fi network: ");    // print name of wifi network in serial monitor
  Serial.print(SSID);

  while (!wifiConnected()) {                          // loop while not connected to wifi
    Serial.print(".");                                // print dot..dot..dot... to serial monitor
    WiFi.begin(SSID, PASSWORD);                       // reattempt connection
  }

  Serial.println("\nWiFi connected!");                // affirmative message upon successful connection
  Serial.println("IP address: ");                     // display local ip address
  Serial.println(WiFi.localIP());                   
  SEPARATOR;                                          // visual separator for serial monitor   

  screen = CONNECT_MQTT;
} 


// reconnect to wifi if connection lost during program loop
void reconnectWifi() {
  Serial.print("Connection to Wi-Fi network lost.");  // print reconnect-specific message to serial monitor
  setupWifi();                                        // call wifi connection function
}


// ************************** CONNECT MQTT ***************************** //

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
  String clientID = "WioTerminal";                    // create a client ID
  client.connect(clientID.c_str());                   // connect to mqtt broker

  while(!client.connected()) {                           // loop while not connected to broker
    Serial.print("Failed, return code = ");           // print error message
    Serial.println(client.state());                   // print client state (error code as int value that represents additional info on specific error) 
    Serial.println("Try again in 5 seconds");      
    delay(5000);                                      // wait 5 seconds before retrying
    client.connect(clientID.c_str());                 // reattempt connection
  }

  Serial.println("Connected!");                       // if succesful, print affirmative message
  client.subscribe(TOPIC_SUB);                        // subscribe to topic
  client.subscribe(TOPIC_SUB_TEMP);
  client.subscribe(TOPIC_SUB_HUMI);
  client.subscribe(TOPIC_SUB_MOIST);
  client.subscribe(TOPIC_SUB_LIGHT);
  client.subscribe(TOPIC_SUB_LOUD);


  Serial.print("Subcribed to: ");                     // print topic subscribed to as a string
  Serial.println(TOPIC_SUB);                      
  SEPARATOR;                                          // visual separator for serial monitor

  screen = DASHBOARD;
} 


// reconnect to broker if connection lost during program loop
void reconnectClient() {
  Serial.println("MQTT connection lost.");            // print reconnect-specific message to serial monitor
  setupClient();                                      // call mqtt broker connection function
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
