#include <Servo.h>

Servo servo;
int angle = 10;

void setup() {
  servo.attach(8);
  servo.write(angle);
}


void loop()
{
 // scan from 0 to 180 degrees
  for(angle = 10; angle < 180; angle = angle + 10)
  {
    servo.write(angle);
    delay(1000);
  }
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 10; angle = angle - 10)
  {
    servo.write(angle);
    delay(1000);
  }
}
