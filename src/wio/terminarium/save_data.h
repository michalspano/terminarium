#include "FlashStorage_SAMD.hpp"

#ifndef SAVE_DATA_H
#define SAVE_DATA_H

#include "mqtt.h"                              // import mqtt connectivity functions
extern char* SSID;                             // include wifi network name
extern char* PASSWORD;                         // include wifi network password
extern char* SERVER;                           // include mqtt broker address

extern const int WRITTEN_SIGNATURE;

extern int signature;
extern uint16_t storedAddress;

extern char newSSID[32];
extern char newPSWD[32];
extern char newMQTT[32];

typedef struct {
  char SSID[32];
  char PASSWORD[32];
  char SERVER[32];
} UserData;

extern void loadData();

extern void saveData();

#endif