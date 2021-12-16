/*
 * Library taken : https://playground.arduino.cc/Code/Keypad
*/

#include <Keypad.h>

const byte ROWS = 1; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','4'}};

byte rowPins[ROWS] = {A1}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A4, A5, A2, A3}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  // Robojax 4x3 keypad test
  Serial.begin(9600);
  Serial.println("Robojax 4x3 keypad");
}
  
void loop(){
  // Robojax 4x3 keypad test
  char key = keypad.getKey();
    // just print the pressed key
   if (key){
    Serial.println(key);
  } 
   // this checkes if 4 is pressed, then do something. Here  we print the text but you can control something.
  if (key =='4'){
    // if key matches what you are looking for
    Serial.println("Key 4 is pressed");
  } 

}
