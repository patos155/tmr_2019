#include <Servo.h>

Servo m_der;
Servo m_izq;

int m1=0;
int mi=0;
int md=0;

void setup() {
  m_der.attach(9);
  m_izq.attach(10);  
}

void loop() {
  moverse(1,1);
  delay(2000);
  moverse(0,0);
  delay(1000);
  moverse(1,-1);
  delay(2200);
  moverse(0,0);
  delay(1000);
  
}

int moverse(int vi, int vd){
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

