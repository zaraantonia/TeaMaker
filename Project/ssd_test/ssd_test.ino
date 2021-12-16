 
#include <SevSeg.h>

//Create an instance of the object.
SevSeg myDisplay;

//Create global variables
unsigned long timer;
int deciSecond = 0;

void setup()
{

  int displayType = COMMON_CATHODE; //Your display is either common cathode or common anode

  /*
  //This pinout is for a regular display
   //Declare what pins are connected to the digits
   int digit1 = 2; //Pin 12 on my 2 digit display
   int digit2 = 3; //Pin 9 on my 2 digit display
   int digit3 = 4; //Pin 8 on my 2 digit display
   int digit4 = 5; //Pin 6 on my 2 digit display
  
   //Declare what pins are connected to the segments
   int segA = 6; //Pin 11 on my 2 digit display
   int segB = 7; //Pin 7 on my 2 digit display
   int segC = 8; //Pin 4 on my 2 digit display
   int segD = 9; //Pin 2 on my 2 digit display
   int segE = 10; //Pin 1 on my 2 digit display
   int segF = 11; //Pin 10 on my 2 digit display
   int segG = 12; //Pin 5 on my 2 digit display
   int segDP= 13; //Pin 3 on my 2 digit display
   */

  //This pinout is for OpenSegment PCB layout
  //Declare what pins are connected to the digits
  int digit1 = 6; //Pin 7 on my 2 digit display
  int digit2 = 12; //Pin 8 on my 2 digit display
  int digit3 = 0;
  int digit4 = 0;

  //Declare what pins are connected to the segments
  int segA = 10; //Pin 10 on my 2 digit display
  int segB = 9; //Pin 9 on my 2 digit display
  int segC = 4; //Pin 1 on my 2 digit display
  int segD = 2; //Pin 4 on my 2 digit display
  int segE = 11; //Pin 3 on my 2 digit display
  int segF = 5; //Pin 6 on my 2 digit display
  int segG = A0; //Pin 5 on my 2 digit display
  int segDP= 3; //Pin 2 on my 2 digit display

  int numberOfDigits = 2; //Do you have a 1, 2 or 4 digit display?

  byte digitPins[] = {12, 6};
  byte segmentPins[] = {10, 9, 4, 2, 11, 5, A0, 3};
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_CATHODE;

  myDisplay.begin(hardwareConfig, numberOfDigits, digitPins, segmentPins, resistorsOnSegments);

  myDisplay.setBrightness(100); //Set the display to 100% brightness level

  timer = millis();
}

void loop()
{
  myDisplay.setNumber(31, 1);
  myDisplay.refreshDisplay();
}
