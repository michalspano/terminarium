/***************************************************************************************************
 * Terminarium - Saving & loading data from flash storage
 * File: {@code save_data.cpp} [source file]
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

/**
 * NOTE: The below code makes use of the FlashStorage_SAMD library by Khoih Prog and Cristian Maglie.
 * It is adapted from the example code provided in the library's github repository.
 * Please follow the instructions in the link below for applying the patch necessary for the package:
 * Link: https://github.com/khoih-prog/FlashStorage_SAMD#using-flashstorage-objects-directly
 */

#include "save_data.h"                                          // include corresponding header file

const int WRITTEN_SIGNATURE = 0xBEEFDEED;                       // initialize signature used to compare and determine whether EEPROM is empty or not    
int signature;                                                  // declare signature to store retrieved signature value and determine whether EEPROM is empty or not    
uint16_t storedAddress = 0;                                     // initialize memory address location to write data to

char newSSID[32];                                               // declare character array for storing new SSID
char newPASSWORD[32];                                           // declare character array for storing new WiFi password
char newSERVER[32];                                             // declare character array for storing MQTT broker address

// function that loads data on program startup
void loadData() {
  UserData savedData;                                           // create instance of UserData struct

  EEPROM.get(storedAddress, signature);                         // read the signature from emulated EEPROM

  if (signature == WRITTEN_SIGNATURE) {                         // if EEPROM is not empty (otherwise there would be no WRITTEN_SIGNATURE)
    EEPROM.get(storedAddress + sizeof(signature), savedData);   // read the saved data 

    strcpy(newSSID, savedData.savedSSID);                       // copy the saved data into the corresponding char arrays for storing new info
    strcpy(newPASSWORD, savedData.savedPASSWORD);
    strcpy(newSERVER, savedData.savedSERVER);

    SSID = newSSID;                                             // set the SSID, PASSWORD and SERVER pointers to point to the char arrays with the new data
    PASSWORD = newPASSWORD;
    SERVER = newSERVER;
  }
}

// function that saves data to flash storage
void saveData() {
  EEPROM.put(storedAddress, WRITTEN_SIGNATURE);                 // write the signature to emulated EEPROM, used to determine whether data is saved at program startup

  UserData savedData;                                           // create instance of UserData struct
  strcpy(savedData.savedSSID, SSID);                            // copy the contents of SSID, PASSWORD and SERVER into UserData struct
  strcpy(savedData.savedPASSWORD, PASSWORD);
  strcpy(savedData.savedSERVER, SERVER);
  
  EEPROM.put(storedAddress + sizeof(signature), savedData);     // write UserData struct data to emulated EEPROM  

  if (!EEPROM.getCommitASAP()) {                                // if false, the EEPROM.put() call will not force EEPROM.commit() to extend flash life
    EEPROM.commit();                                            // call commit function to manually save emulated EEPROM data into flash storage
  }
}