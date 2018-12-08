#include <AFMotor.h>
AF_DCMotor motor_derecho(2);   //motor derecho
AF_DCMotor motor_izquierdo(3);   //motor izquierdo

//localizacion de los pines de los sensores
//sensor infrarojo
int s1_ = 49;
int s2_ = 50;
int s3_ = 51;
int s4_ = 53;
int s5_ = 52;


//variables para almacenar los valores
//sensor infrarojo
int l1=1;
int l2=1;
int l3=0;
int l4=1;
int l5=1;


int neg = 0;
int bco = 1 ;

void setup() {
Serial.begin(9600);  
  pinMode( s1_, INPUT );
  pinMode( s2_, INPUT );
  pinMode( s3_, INPUT );
  pinMode( s4_, INPUT );
  pinMode( s5_, INPUT );
  
}

void loop() {
  //Lectura de los sensores de infrajos
   l5=digitalRead(s5_);
   l4=digitalRead(s4_);
   l3=digitalRead(s3_);
   l2=digitalRead(s2_);
   l1=digitalRead(s1_);
       motor_derecho.setSpeed(75);//210
       motor_derecho.run(FORWARD);
       motor_izquierdo.setSpeed(75);
       motor_izquierdo.run(FORWARD);

}
