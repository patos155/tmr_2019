#include <Servo.h>

Servo servo1;
Servo servo2;
int joyX = 0;
int Valjoy;
int pos;
int servoVal = 0;

void setup()
{
  servo1.attach(3);
  Serial.begin(9600);
}

void loop()
{
  Valjoy = analogRead(joyX);
  if (Valjoy < 509 ) {
   pos = 1;
  }
  if (Valjoy > 509 ) {
     pos = -1;
  }
  if (Valjoy >= 500 &&  Valjoy <=515 )  {
       pos = 0;
  }

  if (pos == 0) {
    servo1.write(90);
  }

  if (pos == 1) {
    servo1.write(180);
  }
  if (pos == -1){
    servo1.write(0);
  }


  Serial.println(Valjoy);

}
