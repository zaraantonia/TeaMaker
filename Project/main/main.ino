#include <Keypad.h>
#include <SevSeg.h>
#include <Servo.h>

//keypad
const byte ROWS = 1; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {{'1','6','7','8'}}; 
byte rowPins[ROWS] = {A1}; //row pinouts
byte colPins[COLS] = {A4, A5, A2, A3}; //column pinouts for 2, 1, 4, 3

//2 digit seven segment display
int digit1 = 6; 
int digit2 = 12;

int segA = 10; 
int segB = 9; 
int segC = 4;
int segD = 2;
int segE = 11;
int segF = 5;
int segG = A0;
int segDP = 3;

int numberOfDigits = 2;
byte digitPins[] = {12, 6};
byte segmentPins[] = {10, 9, 4, 2, 11, 5, A0, 3};
bool resistorsOnSegments = false;
byte hardwareConfig = COMMON_CATHODE;

//servo
int servoPin = 7;
int moveTime = 25; // Move every 0.5s
unsigned long int startMillis = 0;
int position = 0;
int step = 5; // Move 5 degrees

//led
int ledPin = 8;
bool ledHigh = true;

int ledState = LOW;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;   

//bluetooth
int bluetoothPin = 13;

//used objects
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
SevSeg sevseg;
Servo servo;

//states
#define NOT_STARTED 0
#define SERVO_GOING_DOWN 1
#define INFUSING 2
#define SERVO_GOING_UP 3
#define DONE 4
#define INVALID 5
 
int state = NOT_STARTED;

//tea making process
int minutes = 0;
int minutesLeft = 0;
int timePassed = 0;

int halvesPassed = 0;
//int secondsPassed = 0;
void setup() {

  //pink led
  pinMode(ledPin, OUTPUT);

  //servo
  servo.attach(servoPin);
  servo.write(0); 
  
  //2 digit ssd setup
  sevseg.begin(hardwareConfig, numberOfDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100);

  //bluetooth
  Serial.begin(9600);
  
}

void loop() {
  //Serial.println(state);

  if(state == NOT_STARTED)// or state == DONE)
  {
    char key = keypad.getKey();
    if(key)
    {
      minutes = key - '0';
      minutesLeft = minutes;
      state = SERVO_GOING_DOWN;
      startMillis = millis();
    }
  }
  else

  if(state == SERVO_GOING_DOWN)
  {
      //startMillis = millis();
      if (millis() - startMillis >= moveTime) {
        servo.write(position);
        if (position <= 180) {
          position = position + step;
      }
      else
      {
        state = INFUSING;
        startMillis = millis();
      }
    }
  }
  else

  if(state == INFUSING)
  {
    digitalWrite(ledPin, HIGH);
    timePassed = millis() - startMillis;
    if (timePassed > 30000)
    {
      halvesPassed++;
      startMillis = millis();
    }
    else
    {
      int mins = halvesPassed / 2;
      if (mins < minutes)
      {     
        int minutesLeftNow = minutes - mins;
        
        int secondsPassed = timePassed / 1000 + (halvesPassed % 2) * 30;
        
          sevseg.refreshDisplay();
          if(minutesLeftNow>1){
            sevseg.setNumber(minutesLeftNow, 1);}
          else{
            sevseg.setNumber(59-secondsPassed, 1);
            }
        String string=(String(mins) + " : "+ String(secondsPassed));

       // Serial.println(string);
        
      }
      else
      {
        state = SERVO_GOING_UP;
        startMillis = millis();
      
      }
    }
    timePassed = millis() - startMillis;
  }
  else

  if(state == SERVO_GOING_UP)
  {
      sevseg.refreshDisplay();
      sevseg.setNumber(0, 1);
     if (millis() - startMillis >= moveTime) {
        servo.write(position);
        if (position >= 0) {
          position = position - step;
      }
      else
      {
        state = DONE;
        startMillis = millis();
      }
    }
  }
  else
  
  if(state == DONE)
  {
      sevseg.refreshDisplay();
      sevseg.setNumber(0, 1);
      
      unsigned long currentMillis = millis();
      
      if (currentMillis - previousMillis >= interval) {
        ledState = (ledState == LOW) ? HIGH : LOW;
        digitalWrite(ledPin, ledState);
        previousMillis = currentMillis;
      }

      char key = keypad.getKey();
      if(key)
      {
        minutes = key - '0';
        minutesLeft = minutes;
        state = SERVO_GOING_DOWN;
        startMillis = millis();
        minutesLeft = 0;
        timePassed = 0;
        halvesPassed = 0;
      }
  }
}
