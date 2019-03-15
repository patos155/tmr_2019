#include <AFMotor.h>


AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

int joy = A8;
int pos;
void setup() {
  Serial.begin(115200);
}

void loop(){
  pos = analogRead(joy);

  if (pos > 600)
  {
    motor1.setSpeed(50);//velocidad de motor izquierdo
    motor1.run(FORWARD); //polaridad de motor izquierdo
    motor2.setSpeed(50);//velocidad de motor derecho
    motor2.run(FORWARD);//polaridad de motor  derecho
  }
  // velocidades joystick derecho hacia adelante
  if (pos < 200)
  {
    motor1.setSpeed(50);//velocidad de motor izquierdo
    motor1.run(BACKWARD); //polaridad de motor izquierdo
    motor2.setSpeed(50);//velocidad de motor derecho
    motor2.run(BACKWARD);//polaridad de motor  derecho
  }
  //Posicion por defecto del joistick(motores detenidos)
  if ((pos <= 600) && (pos >= 200))
  {
    motor1.setSpeed(0);//velocidad de motor izquierdo
    motor1.run(BACKWARD); //polaridad de motor izquierdo
    motor2.setSpeed(0);//velocidad de motor derecho
    motor2.run(BACKWARD);//polaridad de motor  derecho
  }


}



//#include "ArduinoMotorShieldR3.h"
//
//ArduinoMotorShieldR3 md;
//int fwd = -255;
//int bwd = 255;
//
//int joy1 = 2;
//int joy2 = 3;
////int joy3 = 4;
//
//int pos1;
//int pos2;
//
//void setup() {
//  Serial.begin(115200);
//  Serial.println("Arduino Motor Shield R3");
//  md.init();
//}
//
//void loop() {
//  pos1 = analogRead(joy1);
//  pos2 = analogRead(joy2);
//  Serial.println("M1 Speed 100% Forward");
//  md.setM1Speed(fwd);
//  Serial.println("M2 Speed 100% Forward");
//  md.setM2Speed(fwd);
//  delay(500);
//  Serial.println("M1 Speed 100% Backward");
//  md.setM1Speed(bwd);
//  Serial.println("M2 Speed 100% Backward");
//  md.setM2Speed(bwd);
//  delay(500);
//  Serial.println("M1 Speed 0%");
//  md.setM1Speed(0);
//  Serial.println("M2 Speed 0%");
//  md.setM2Speed(0);
//  delay(2000);
//}

