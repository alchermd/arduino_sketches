/*
    keypadLed v0.1 - Validate a keypad's input against a preset 
    password to turn on an LED.

    Keypad used in this sketch - https://images-na.ssl-images-amazon.com/images/I/61JPRn6su1L._SL1500_.jpg

    Github @alchermd, 2017
    MIT Licensed
*/

#include <Keypad.h> // Make sure to install the Keypad library
#include <stdbool.h>
#include <string.h>
#include "helpers.h"

/* Keypad setup. */

// Keypad dimensions
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

// Map the keypad to a 2d array.
char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

// Map the pins for the keypad to use
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/* LED setup. */
const int led = 13;

/* Password setup. */
char pw[] = "123"; // Change this to any password (make sure your keypad can support it!)
char user_pw[4];

size_t i = 0; // iterator

void setup(){
    user_pw[3] = '\0';
    Serial.begin(9600);
    pinMode(led, OUTPUT);
    Serial.println(
        "INSTRUCTIONS: USE THE KEYPAD TO ENTER PASSWORD\n"
        "TO CLEAR CURRENT INPUT, PRESS THE 'D' BUTTON\n"
        "IF THE PASSWORD IS CORRECT, THE LED WILL LIGHT UP\n"
    );
}
  
void loop(){
    // Get pressed key.
    char key = keypad.getKey();
  
    if (key) {
        // Clear input if 'D' is pressed.
        if (key == 'D') {
            clearArray(user_pw, 3);
            i = 0;
            digitalWrite(led, LOW);
        }

        else {
            // Update user_pw
            user_pw[i] = key;
            i++;

            // Check if password is correct.
            bool correct = strcmp(user_pw, pw) == 0;
            if (correct) {
                digitalWrite(led, HIGH);
                clearArray(user_pw, 3);
                i = 0;
            }
            else {
                digitalWrite(led, LOW);
            }
    
            if (user_pw[2] != ' ') {
                clearArray(user_pw, 3);
                i = 0;
            }
        }
    }

}

