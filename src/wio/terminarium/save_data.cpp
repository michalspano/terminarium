#include "save_data.h"

const int WRITTEN_SIGNATURE = 0xBEEFDEED;

// Create a structure that is big enough to contain a name
// and a surname. The "valid" variable is set to "true" once
// the structure is filled with actual data for the first time.

int signature;
uint16_t storedAddress = 0;

char newSSID[32];
char newPSWD[32];
char newMQTT[32];

void loadData() {
  UserData userData;

  EEPROM.get(storedAddress, signature);

  // If the EEPROM is empty then no WRITTEN_SIGNATURE
  if (signature == WRITTEN_SIGNATURE) {
    EEPROM.get(storedAddress + sizeof(signature), userData);

    strcpy(newSSID, userData.SSID);
    strcpy(newPSWD, userData.PASSWORD);
    strcpy(newMQTT, userData.SERVER);

    SSID = newSSID;
    PASSWORD = newPSWD;
    SERVER = newMQTT;
  }
}

void saveData() {

  EEPROM.put(storedAddress, WRITTEN_SIGNATURE);

  UserData saveData;

  strcpy(saveData.SSID, SSID);
  strcpy(saveData.PASSWORD, PASSWORD);
  strcpy(saveData.SERVER, SERVER);

  EEPROM.put(storedAddress + sizeof(signature), saveData);

  if (!EEPROM.getCommitASAP()) {
    Serial.println("CommitASAP not set. Need commit()");
    EEPROM.commit();
  }
}