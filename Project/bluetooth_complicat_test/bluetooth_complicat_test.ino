/* Code written by Chams for Youtube Channel - That'sEngineering
 *  12/2/2020
 *  Youtube video: HC-05 BT module, interfacing with Arduino (via Smartphone)
 *  
 */

#include <SoftwareSerial.h>

String value;
int Tx = 2;       // connect BT module TX to 2
int Rx = 3;       // connect BT module RX to 3

// creates a "virtual" serial port/UART
SoftwareSerial bluetooth(Tx, Rx);

void setup() {

  // start serial communication at default baud rate 9600bps
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  bluetooth.begin(9600);
}

void loop() {
  
  if (bluetooth.available())
  {
    value = bluetooth.readString();
    Serial.println(value);

    if (value == "turn on") {
      digitalWrite(13, HIGH);
    }

    if (value == "blink") {
      while (value != "Stop blinking.") {
     
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);

        value = bluetooth.readString();
      }
      
      digitalWrite(13, LOW);
    }
  }
}
