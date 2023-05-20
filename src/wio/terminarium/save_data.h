/***************************************************************************************************
 * Terminarium - Saving & loading data from flash storage
 * File: {@code save_data.h} [header file]
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#include "FlashStorage_SAMD.hpp"               // import external flash storage library

#ifndef SAVE_DATA_H
#define SAVE_DATA_H                            // header guard

#include "mqtt.h"                              // import mqtt connectivity functions
extern char* SSID;                             // include wifi network name
extern char* PASSWORD;                         // include wifi network password
extern char* SERVER;                           // include mqtt broker address

extern const int WRITTEN_SIGNATURE;            // signature used to compare and determine whether EEPROM is empty or not
extern int signature;                          // signature used to compare and determine whether EEPROM is empty or not
extern uint16_t storedAddress;                 // memory address location to write data to

extern char newSSID[32];                       // character array for storing new SSID
extern char newPASSWORD[32];                   // character array for storing new WiFi password
extern char newSERVER[32];                     // character array for storing MQTT broker address


// struct to contain the saved network data
typedef struct {
  char savedSSID[32];                          // character array for storing saved SSID
  char savedPASSWORD[32];                      // character array for storing saved WiFi password 
  char savedSERVER[32];                        // character array for storing saved MQTT broker address 
} UserData;

// function that loads data on program startup
extern void loadData();

// function that saves data to flash storage
extern void saveData();

#endif                                         // end header guard