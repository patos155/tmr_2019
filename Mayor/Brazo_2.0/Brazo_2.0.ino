#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int joyX1 = A8;
int posX1;
int joyY1 = A9;
int posY1;
int joyX2 = A12;
int posX2;
int joyY2 = A13;
int posY2;
void setup() {
  Serial.begin(9600);
}

void loop(){
  posX1 = analogRead(joyX1);
  posX2 = analogRead(joyX2);
  posY1 = analogRead(joyY1);
  posY2 = analogRead(joyY2);
  
  if (posX1 > 600)
  {
    motor1.setSpeed(255);//velocidad de motor izquierdo
    motor1.run(FORWARD); //polaridad de motor izquierdo
  }
  // velocidades joystick derecho hacia adelante
  if (posX1 < 200)
  {
    motor1.setSpeed(255);//velocidad de motor izquierdo
    motor1.run(BACKWARD); //polaridad de motor izquierdo
  }
  //Posicion por defecto del joistick(motores detenidos)
  if ((posX1 <= 600) && (posX1 >= 200))
  {
    motor1.setSpeed(0);//velocidad de motor izquierdo
    motor1.run(BACKWARD); //polaridad de motor izquierdo
  }
  if (posY1 > 600)
  {
    motor2.setSpeed(255);//velocidad de motor izquierdo
    motor2.run(FORWARD); //polaridad de motor izquierdo
  }
  // velocidades joystick derecho hacia adelante
  if (posY1 < 200)
  {
    motor2.setSpeed(255);//velocidad de motor izquierdo
    motor2.run(BACKWARD); //polaridad de motor izquierdo
  }
  //Posicion por defecto del joistick(motores detenidos)
  if ((posY1 <= 600) && (posY1 >= 200))
  {
    motor2.setSpeed(0);//velocidad de motor izquierdo
    motor2.run(BACKWARD); //polaridad de motor izquierdo
 }
  if (posX2 > 600)
  {
    motor3.setSpeed(255);//velocidad de motor izquierdo
    motor3.run(FORWARD); //polaridad de motor izquierdo
  }
  // velocidades joystick derecho hacia adelante
  if (posX2 < 200)
  {
    motor3.setSpeed(255);//velocidad de motor izquierdo
    motor3.run(BACKWARD); //polaridad de motor izquierdo
  }
  //Posicion por defecto del joistick(motores detenidos)
  if ((posX2 <= 600) && (posX2 >= 200))
  {
    motor3.setSpeed(0);//velocidad de motor izquierdo
    motor3.run(BACKWARD); //polaridad de motor izquierdo
  }
  if (posY2 > 600)
  {
    motor4.setSpeed(255);//velocidad de motor izquierdo
    motor4.run(FORWARD); //polaridad de motor izquierdo
  }
  // velocidades joystick derecho hacia adelante
  if (posY2 < 200)
  {
    motor4.setSpeed(255);//velocidad de motor izquierdo
    motor4.run(BACKWARD); //polaridad de motor izquierdo
  }
  //Posicion por defecto del joistick(motores detenidos)
  if ((posY2 <= 600) && (posY2 >= 200))
  {
    motor4.setSpeed(0);//velocidad de motor izquierdo
    motor4.run(BACKWARD); //polaridad de motor izquierdo
  }
 
}
//Serial.print  ("posicion x1: ");
//Serial.println(posX1);
//Serial.print  ("posicion y1: ");
//Serial.println(posY1);
