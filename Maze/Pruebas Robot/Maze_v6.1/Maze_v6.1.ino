/*-----------------------------------
 *            LIBRERIAS            *
-----------------------------------*/
#include <Servo.h>
#include <Wire.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_MLX90614.h>
#include <MPU6050.h>
#include <SPI.h>
#include <I2Cdev.h>
#include <SD.h>

/*-----------------------------------
 *            SENSORES             *
-----------------------------------*/

/*  Motores  */
Servo m_der;
Servo m_izq;

/*  Ultrasónicos  */
const int trig_D = 33;
const int echo_D = 32;
const int trig_R = 41;
const int echo_R = 40;
const int trig_L = 27;
const int echo_L = 26;

/*  Temperatura infrarroja  */
Adafruit_MLX90614 tempI = Adafruit_MLX90614();

/*  Giroscopio  */
const int mpu_dir = 0x68;
MPU6050 giro(mpu_dir);

/*  Kit  */
const int led = 19;

/*  SD  */
File archivo;
const int pinSD=46;

/*infrarrojos*/
const int infra_L = A11;
const int infra_R = A12;


/*-----------------------------------
 *            VARIABLES            *
-----------------------------------*/

/*  Variable de paredes  */
int adelante = 0;
int derecha = 0;
int izquierda = 0;

long D = 0;
long R = 0;
long R2 = 0;
long L = 0;

/*  Variables de temperatura  */
float ti_amb = 0;
float ti_obj = 0;
float ti_dif = 0;

bool vI = false;

/*  Variables de giroscopio  */
int ax = 0;
int ay = 0;
int az = 0;
int gx = 0;
int gy = 0;
int gz = 0;

int ang_x = 0;

/*  Variables de infrarrojos  */
int inf_L = 0;
int inf_R = 0;



/*-----------------------------------
 *              SETUP              *
-----------------------------------*/
void setup() {
  /*  Motores  */
  m_der.attach(9);
  m_izq.attach(10);
  
  m_der.write(90);
  m_izq.write(90);
  
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

  /*  Infrarrojos de temperatura  */
  tempI.begin();

  /*  Giroscopio  */
  giro.initialize();

  /*  Kit  */
  pinMode(led,OUTPUT);

  /*  SD  */
  SD.begin(pinSD);
  archivo = SD.open("Maze.txt",FILE_WRITE);
  archivo.println(" ");
  archivo.write("======================================================================================================================================");
  archivo.println(" ");
  archivo.close();
}


/*-----------------------------------
 *              LOOP               *
-----------------------------------*/
void loop() {
  /*  Lecturas  */
  Leer();

  /*  << Funcionamiento >>  */

  if(ang_x >= 11){
    moverse(1,1);
  }else{
    if(inf_L < 10 && inf_R <10){
      giroU();
    }else {
        
     /*  << Funcionamiento >>  */
    
      /*
          |       |     |       |
          |   1   |     |   1   |
          |0     0|     |0     1
          |       |     |       |
      */
      if( ((adelante==1) && (izquierda==0) && (derecha==0)) || ((adelante==1) && (izquierda==0) && (derecha==1)) ){
        grabar("Derecho");
        moverse(1,1);       //Moverse hacia adelante

       
      }
    
      /*
          |-------|
          |   0   |
          |0     1
          |       |
      */
      if( ((adelante==0) && (izquierda==0) && (derecha==1)) ){
        grabar("Giro D");
        giroD();
        centrar();
      }
    
      /*
          |-------|
          |   0   |
           1     0|
          |       |
      */
      if( ((adelante==0) && (izquierda==1) && (derecha==0)) ){
        grabar("Giro I");
        giroI();
        centrar();
      }
     
    
      /*
          |-------|
          |   0   |
           1     1
          |       |
      */
      if( ((adelante==0) && (izquierda==1) && (derecha==1)) ){
        grabar("Giro I");
        giroI();
        centrar();
      }
    
      /*     
             
              1   
           1     1
          |       |
      */
      if( ((adelante==1) && (izquierda==1) && (derecha==1)) ){
        grabar("Giro I");
        giroI();
        centrar();
      }
      
     /*
          |       |     
          |   1   |     
           1     0|    
          |       |    
      */
      if( ((adelante==1) && (izquierda==1) && (derecha==0))){
        grabar("Giro I");
        giroI();
        centrar();
      }
      
     /*
          |-------|
          |   0   |
          | 0    0|
          |       |
      */
      if( ((adelante==0) && (izquierda==0) && (derecha==0)) ){
        grabar("Giro U");
        giroU();
        centrar();
      }

        
      if(vI){
        digitalWrite(led,HIGH);
      }else{
        digitalWrite(led,LOW);
      }
  
    }
  }

  
}


/*-----------------------------------
 *       FUNCIONES Y PROCESOS      *
-----------------------------------*/

void Leer(){
  /*  Lecturas  */
  D = ultra(trig_D,echo_D);
  R = ultra(trig_R,echo_R);
  L = ultra(trig_L,echo_L);

  ti_amb=tempI.readAmbientTempC();
  ti_obj=tempI.readObjectTempC();
  ti_dif = ti_obj - ti_amb;

  giro.getAcceleration(&ax, &ay, &az);
  ang_x = atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);

  inf_L = analogRead(infra_L);
  inf_R = analogRead(infra_R);
  
  /*  determinación de situación | Ultrasónicos  */
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


  /*  determinación de situación | Temperatura  */
  if(L<30){
    izquierda=0;
  }else{
    izquierda=1;
  }

  if(ti_dif>10){
    vI=true;
  }else{
    vI=false;
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

/*  Función para grbar SD  */
void grabar(String situacion){
  archivo = SD.open("Maze.txt",FILE_WRITE);
  archivo.print(situacion);
  archivo.write("\tUL: ");archivo.print(L);
  archivo.write("\tUD: ");archivo.print(D);
  archivo.write("\tUR: ");archivo.print(R);
  archivo.write("\tTobjI: ");archivo.print(ti_obj);
  archivo.write("\tTambI: ");archivo.print(ti_amb);
  archivo.write("\tTdifI: ");archivo.print(ti_dif);
  archivo.write("\tvI: ");archivo.print(vI);
  archivo.write("\tAngX: ");archivo.print(ang_x);
  archivo.write("\tInfI: ");archivo.print(inf_L);
  archivo.write("\tInfR: ");archivo.print(inf_R);
  archivo.println("");
  archivo.close();
}

/*  Función para controlar Servo motores  */
void moverse(int vi, int vd){
  int mi = 90;
  int md = 90;
  
  switch(vi){
    case 1:mi=0;break;
    case 0:mi=90;break;
    case -1:mi=180;break;
  }
  switch(vd){
    case 1:md=117;break;
    case 0:md=90;break;
    case -1:md=0;break;
  }

  m_izq.write(mi);
  m_der.write(md);
} 

void centrar(){
  Leer();
  if(!(L>30)){
    
    if(L<6 && L>3){
      medioD();
    }
    if(L>6){
      medioI();
    }
    if(L<3){
      medioD2();
    }
  }
  
  
  
  
}
/*  Proceso de giro a la derecha  */
void giroD(){
  moverse(0,0);
  delay(1000);
  moverse(1,1);
  delay(750);
  moverse(1,-1);      //Giro a la derecha
  delay(1400);
  moverse(1,1);
  delay(1500);
  moverse(0,0);
  delay(1000);
}

/*Proceso de media vuelta derecha*/
void medioD(){
  moverse(1,-1);
  delay(500);
  moverse(1,1);
  delay(300);
  moverse(-1,1);
  delay(400);
}

/*Proceso de media vuelta derecha*/
void medioD2(){
  moverse(1,-1);
  delay(500);
  moverse(1,1);
  delay(600);
  moverse(-1,1);
  delay(300);
}

void medioI(){
  moverse(-1,1);
  delay(500);
  moverse(1,1);
  delay(300);
  moverse(1,-1);
  delay(300);
}

/*  Proceso de giro a la izquierda  */
void giroI(){
  moverse(0,0);
  delay(1000);
  moverse(1,1);
  delay(750);
  moverse(-1,1);      //Giro a la izquierda
  delay(1460);
  moverse(1,1);
  delay(1500);
  moverse(0,0);
  delay(1000);
}

/*  Proceso de giro en U  */
void giroU(){
  moverse(0,0);
  delay(800);
  moverse(-1,1);      //Giro a la izquierda
  delay(3100);
  moverse(0,0);
  delay(800);
  moverse(1,1);
  delay(1500);
  moverse(0,0);
  delay(1000);
}
