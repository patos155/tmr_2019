#include <Servo.h>

/*  Ultrasónicos  */
const int trig_D = 33;
const int echo_D = 32;
const int trig_R = 53;
const int echo_R = 52;
const int trig_L = 27;
const int echo_L = 26;

/*  Motores  */
Servo m_der;
Servo m_izq;

/*  Distancia de paredes  */
const int p_d = 6;
const int p_l = 6;

/*  Variable de paredes  */
int adelante = 0;
int derecha = 0;
int izquierda = 0;

long D = 0;
long R = 0;
long L = 0;

void setup() {
  /*  Ultrasónicos  */
  pinMode(trig_D, OUTPUT);    //Delantero
  pinMode(echo_D, INPUT);
  digitalWrite(trig_D,LOW);
  pinMode(trig_R, OUTPUT);    //Derecho
  pinMode(echo_R, INPUT);
  digitalWrite(trig_R,LOW);
  pinMode(trig_L, OUTPUT);    //Izquierdo
  pinMode(echo_L, INPUT);
  digitalWrite(trig_L,LOW);

  /*  Motores  */
  m_der.attach(9);
  m_izq.attach(10);  
}

void loop() {
  /*  Lecturas  */
  Leer();

  /*  << Funcionamiento >>  */

  /*
      |       |     |       |
      |   1   |     |   1   |
      |0     0|     |0     1
      |       |     |       |
  */
  if( ((adelante==1) && (izquierda==0) && (derecha==0)) || ((adelante==1) && (izquierda==0) && (derecha==1)) ){
    moverse(1,1);       //Moverse hacia adelante
  }

  /*
      |-------|
      |   0   |
      |0     1
      |       |
  */
  if( ((adelante==0) && (izquierda==0) && (derecha==1)) ){
    giroD();
  }

  /*
      |-------|
      |   0   |
       1     0|
      |       |
  */
  if( ((adelante==0) && (izquierda==1) && (derecha==0)) ){
    giroI();
  }

  /*
      |-------|
      |   0   |
       1     1
      |       |
  */
  if( ((adelante==0) && (izquierda==1) && (derecha==1)) ){
    //giroI();
    moverse(0,0);
  }

  /*     
         
          1   
       1     1
      |       |
  */
  if( ((adelante==1) && (izquierda==1) && (derecha==1)) ){
    //giroI();
    moverse(0,0);
  }

  /*
      |-------|
      |   0   |
      |0     0|
      |       |
  */
  if( ((adelante==0) && (izquierda==0) && (derecha==0)) ){
    //giroU();
    moverse(0,0);
  }

}

void Leer(){
  /*  Lecturas  */
  D = ultra(trig_D,echo_D);
  R = ultra(trig_R,echo_R);
  L = ultra(trig_L,echo_L);
  
  /*  determinación de situación  */
  if(D<10){
    adelante=0;
  }else{
    adelante=1;
  }

  if(R<30){
    derecha=0;
  }else{
    derecha=1;
  }

  if(L<30){
    izquierda=0;
  }else{
    izquierda=1;
  }
}

/*  Función para lectura de ultrasónicos  */
long ultra(int trigPin,int echoPin){
  long t=0;
  long d=0;

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  t=pulseIn(echoPin,HIGH);
  d = t/59;

  return d;
}

/*  Función para controlar Servo motores  */
int moverse(int vi, int vd){
  int mi = 90;
  int md = 90;
  
  switch(vi){
    case 1:mi=0;break;
    case 0:mi=90;break;
    case -1:mi=180;break;
  }
  switch(vd){
    case 1:md=180;break;
    case 0:md=90;break;
    case -1:md=0;break;
  }

  m_izq.write(mi);
  m_der.write(md);
}

void giroD(){
  moverse(0,0);
  delay(1000);
  moverse(1,1);
  delay(1000);
  moverse(1,-1);      //Giro a la derecha
  delay(2100);
  moverse(1,1);
  delay(1000);
  moverse(0,0);
  delay(1000);
}

void giroI(){
  moverse(0,0);
  delay(1000);
  moverse(1,1);
  delay(1000);
  moverse(-1,1);      //Giro a la izquierda
  delay(2100);
  moverse(1,1);
  delay(1000);
  moverse(0,0);
  delay(1000);
}

void giroU(){
  moverse(0,0);
  delay(800);
  moverse(-1,1);      //Giro a la izquierda
  delay(3400);
  moverse(0,0);
  delay(800);
}

