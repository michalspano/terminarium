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

WiFiClient wioClient;                                 // initialise wifi client
PubSubClient client(wioClient);                       // initialise mqtt client

/* Note: This code was adapted from "MQTT on Wio Terminal" by Salman Faris
* Link: https://www.hackster.io/Salmanfarisvp/mqtt-on-wio-terminal-4ea8f8 */

/***update these with values corresponding to your network***/
const char* SSID       = "INSERT NETWORK NAME";            // wifi network name
const char* PASSWORD   = "INSERT PASSWORD";                // wifi network password
const char* SERVER     = "INSERT IP ADDRESS";              // mqtt broker ip address (use ipconfig command and see IPv4 address)

// topic for receiving messages
const char* TOPIC_SUB = "/terminarium/app/conf";        

// topic for sending sensor data
const char* TOPIC_PUB_TEMP = "/terminarium/sensor/temperature";   
const char* TOPIC_PUB_HUMI = "/terminarium/sensor/humidity";
const char* TOPIC_PUB_VIB = "/terminarium/sensor/vibration";
const char* TOPIC_PUB_MOIST = "/terminarium/sensor/moisture";
const char* TOPIC_PUB_LIGHT = "/terminarium/sensor/light";
const char* TOPIC_PUB_LOUD = "/terminarium/sensor/loudness";


// ************************ CONNECT WIFI ***************************** //

// connect to wifi network and print status to serial monitor
void setupWifi() {
  WiFi.begin(SSID, PASSWORD);                         // connect to wifi network
  Serial.print("\nConnecting to Wi-Fi network: ");    // print name of wifi network in serial monitor
  Serial.print(SSID);

  while (WiFi.status() != WL_CONNECTED) {             // loop while not connected to wifi
    Serial.print(".");                                // print dot..dot..dot... to serial monitor
    WiFi.begin(SSID, PASSWORD);                       // reattempt connection
  }

  Serial.println("\nWiFi connected!");                // affirmative message upon successful connection
  Serial.println("IP address: ");                     // display local ip address
  Serial.println(WiFi.localIP());                   
  SEPARATOR;                                          // visual separator for serial monitor   

  delay(2000);                                        // arbitrary delay for readability of serial monitor
} 


// reconnect to wifi if connection lost during program loop
void reconnectWifi() {
  Serial.print("Connection to Wi-Fi network lost.");  // print reconnect-specific message to serial monitor
  setupWifi();                                        // call wifi connection function
}


// ************************** CONNECT MQTT ***************************** //

// connect to mqtt broker and print status to serial monitor
void setupClient() {                    
  Serial.println("Attempting MQTT connection...");  
  String clientID = "WioTerminal";                    // create a client ID
  client.connect(clientID.c_str());                   // connect to mqtt broker

  while(!client.connected()) {                        // loop while not connected to broker
    Serial.print("Failed, return code = ");           // print error message
    Serial.println(client.state());                   // print client state (error code as int value that represents additional info on specific error) 
    Serial.println("Try again in 5 seconds");      
    delay(5000);                                      // wait 5 seconds before retrying
    client.connect(clientID.c_str());                 // reattempt connection
  }

  Serial.println("Connected!");                       // if succesful, print affirmative message
  client.subscribe(TOPIC_SUB);                        // subscribe to topic
  Serial.print("Subcribed to: ");                     // print topic subscribed to as a string
  Serial.println(TOPIC_SUB);                      
  SEPARATOR;                                          // visual separator for serial monitor

  delay(2000);                                        // arbitrary delay for readability in serial monitor
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
  Serial.println();
  buff_p[length] = '\0';
  String message = String(buff_p);
}


