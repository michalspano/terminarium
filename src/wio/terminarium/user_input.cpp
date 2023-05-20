/***************************************************************************************************
 * Terminarium - Keyboard & user input functions
 * File: {@code user_input.cpp} [source file]
 * Members: Michal Spano, Manely Abbasi, Erik Lindstrand, James Klouda,
 *          Konstantinos Rokanas, Jonathan Boman
 *
 * DIT113 Systems Development, SEM @ CSE.
 ***************************************************************************************************/

#include "user_input.h"                       // include corresponding header file
#include <cstring>                            // include C standard library for use of certain string manipulation functions

// multidimensional array containing the available characters on the keyboard
const char keyboard[4][23] = {
  { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w' },
  { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W' },
  { '1', '2', '3', '4', '5', '!', '?', '@', '#', '$', '%', '_', '-', '+', '=', '^', '&', '*', '`', '~', 'x', 'y', 'z' },
  { '6', '7', '8', '9', '0', '.', ',', ';', ':', '"', '/', '(', ')', '{', '}', '[', ']', '<', '>', 'Ä', 'X', 'Y', 'Z' },
};

char inputSSID[32];                           // declare the character array that stores the user inputted Wifi SSID
char inputPSWD[32];                           // declare the character array that stores the user inputted Wifi password
char inputMQTT[32];                           // declare the character array that stores the user inputted mqtt broker address

// variables indicating currently highlighted character
int currentXY[2] = {KEY_X + 13, KEY_Y + 80};  // x, y coords of highlighted character (initialized pointing to DEL key)
int currentChar[2] = {4, 1};                  // index values to retrieve highlighted character from keyboard array (initialized pointing to DEL key)

// function called on right button press in user input screen
void keyboardRight() {
  // if at bottom row and left side of screen, jump from DEL to SPACE key
  if (currentChar[0] == KEY_ROWS && currentChar[1] < 6) {    
    currentXY[0] = 155;
    currentChar[1] = 11;
  // if at bottom row and middle of screen, jump from SPACE to ENTER key
  } else if (currentChar[0] == KEY_ROWS && currentChar[1] > 5 && currentChar[1] < 16) {
    currentXY[0] = 272;
    currentChar[1] = 20;
  // if at bottom row and right side of screen, scroll from ENTER to DEL key
  } else if (currentChar[0] == KEY_ROWS && currentChar[1] > 16) {  
    currentXY[0] = 25;
    currentChar[1] = 1;
  // if within first four character rows, change position by 1 character to the right
  } else if (currentChar[1] != (KEY_COLUMNS - 1)) { 
    currentXY[0] += 13;
    currentChar[1] += 1;
  // if within first four character rows at rightmost column, scroll to the leftmost
  } else if (currentChar[1] == KEY_COLUMNS - 1) {
    currentXY[0] = 13;
    currentChar[1] = 0;
  }
}

// function called on left button press in user input screen
void keyboardLeft() {
  // if at bottom row and right side of screen, jump from ENTER to SPACE key
  if(currentChar[0] == KEY_ROWS && currentChar[1] > 15) {                
    currentXY[0] = 155;
    currentChar[1] = 11;
  // if at bottom row and middle of screen, jump from SPACE to DEL key
  } else if (currentChar[0] == KEY_ROWS && currentChar[1] > 5 && currentChar[1] < 16) { 
    currentXY[0] = 25;
    currentChar[1] = 1;   
  // if at bottom row and left side of screen, scroll from DEL to ENTER key
  } else if (currentChar[0] == KEY_ROWS && currentChar[1] < 6) {
    currentXY[0] = 272;
    currentChar[1] = 20;
  // if within first four character rows, change position by 1 character to the left
  } else if (currentChar[1] != 0) {                   
    currentXY[0] -= 13;
    currentChar[1] -= 1;
  // if within first four character rows at leftmost column, scroll to the rightmost
  } else if (currentChar[1] == 0) {                   
    currentXY[0] = 298;
    currentChar[1] = 22;
  }
}

// function called on up button press in user input screen
extern void keyboardUp() {
  if (currentChar[0] != 0) {                  // change position by 1 character upwards
    currentXY[1] -= 20;
    currentChar[0] -= 1;
  } else if (currentChar[0] == 0) {           // if at topmost row, scroll to bottommost 
    currentXY[1] = KEY_Y + 80;
    currentChar[0] = KEY_ROWS; 
  }
}

// function called on down button press in user input screen
extern void keyboardDown() {
  if (currentChar[0] != KEY_ROWS) {           // change position by 1 character downwards
    currentXY[1] += 20;
    currentChar[0] += 1;
  } else if (currentChar[0] == KEY_ROWS) {    // if at bottommost row, scroll to the topmost
    currentXY[1] = KEY_Y;
    currentChar[0] = 0;
  }
}

// function called on middle button press in user input screen
extern void keyboardMiddle() {
  // if selecting the DEL key, call function to remove last character of input String
  if (currentChar[0] == KEY_ROWS && currentChar[1] < 6) {    
    removeChar();
    buttonPressed = true;
    
  // if selecting the SPACE key, call function to add space at the end of input String
  } else if (currentChar[0] == KEY_ROWS && currentChar[1] > 5 && currentChar[1] < 16) {
    addChar(' ');
    buttonPressed = true;

  // if selecting the ENTER key, save user input string and proceed until all network info is confirmed
  } else if (currentChar[0] == KEY_ROWS && currentChar[1] > 15) {
    saveUserInput();                          // save user input             
    if(screen == USER_INPUT_SSID) {
      screen = USER_INPUT_PSWD;               // if at input SSID screen, change to input password screen       
      initUserInput(PASSWORD);                // fetch existing password and reset the highlighted character
      buttonPressed = true;
    } else if (screen == USER_INPUT_PSWD) {
      screen = USER_INPUT_MQTT;               // if at input wifi password screen, change to input mqtt address screen 
      initUserInput(SERVER);                  // fetch existing broker address and reset the highlighted character
      buttonPressed = true;
    } else if (screen == USER_INPUT_MQTT) {   
      screen = CONNECT_CONFIRM;               // if at input broker address screen, go back to confirm network info screen
    }

  // if selecting a keyboard character, call function to add it to end of input String
  } else {
    addChar(keyboard[currentChar[0]][currentChar[1]]);
    buttonPressed = true;
  }
}

// function to add currently highlighted character to input String array
void addChar(char character) {                
  char charString[2];                         // create a temporary character array to hold the single character
  charString[0] = character;                  // assign the selected character
  charString[1] = '\0';                       // add null terminator to make it a valid string
  
  switch(screen) {
    case USER_INPUT_SSID:
      strcat(inputSSID, charString);          // concatenate existing SSID String and new character
      break;
    case USER_INPUT_PSWD:
      strcat(inputPSWD, charString);          // concatenate existing WiFi password String and new character
      break;
    case USER_INPUT_MQTT:
      strcat(inputMQTT, charString);          // concatenate existing broker address String and new character
      break;
  }
}

// function to remove last character from the input String array
void removeChar() {                           
  int length;                                 // declare variable storing length of input String

  switch (screen) {
    case USER_INPUT_SSID:
      length = strlen(inputSSID);             // determine the lenght of input String
      if (length > 0) {                       // check that input String isn't empty
      inputSSID[length - 1] = '\0';           // if not empty, add null terminator to the last element
      }
      break;
    case USER_INPUT_PSWD:
      length = strlen(inputPSWD);             // determine the lenght of input String
      if (length > 0) {                       // check that input String isn't empty
        inputPSWD[length - 1] = '\0';         // if not empty, add null terminator to the last element
      }
      break;
    case USER_INPUT_MQTT:
      length = strlen(inputMQTT);             // determine the lenght of input String
      if (length > 0) {                       // check that input String isn't empty
      inputMQTT[length - 1] = '\0';           // if not empty, add null terminator to the last element
      }
      break;
  }
}

// function to import provided network String and reset the position of highlighted key
void initUserInput(char* currentVal) {
    switch(screen) {
    case USER_INPUT_SSID:
      strcpy(inputSSID, currentVal);          // copy the contents of current Wifi SSID to user input character array
      break;
    case USER_INPUT_PSWD:
      strcpy(inputPSWD, currentVal);          // copy the contents of current Wifi password to user input character array
      break;
    case USER_INPUT_MQTT:
      strcpy(inputMQTT, currentVal);          // copy the contents of current broker address to user input character array
      break;
  }

  // reset position to highlight DEL key
  currentXY[0] = KEY_X + 13;                  // reset x coordinate of highlighted key 
  currentXY[1] = KEY_Y + 80;                  // reset y coordinate of highlighted key 
  currentChar[0] = 4;                         // reset keyboard array index value (row)
  currentChar[1] = 1;                         // reset keyboard array index value (column)
}

// function to save user input upon selecting the ENTER key
void saveUserInput() {
  switch(screen) {
    case USER_INPUT_SSID:
      SSID = inputSSID;                       // make the SSID pointer point to new user inputted character array
      break;
    case USER_INPUT_PSWD:
      PASSWORD = inputPSWD;                   // make the password pointer point to new user inputted character array
      break;
    case USER_INPUT_MQTT:
      SERVER = inputMQTT;                     // make the broker address pointer point to new user inputted character array
      saveData();                             // call function that saves all inputted network data to flash storage (COMMENT OUT TO OPT-OUT OF USING FLASH STORAGE)
      break;
  }
}