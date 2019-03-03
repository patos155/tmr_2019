//---------------------------------------------------------------------------------------------------------------------
//                                                 Librerias
//---------------------------------------------------------------------------------------------------------------------
#include <ArduinoMotorShieldR3.h>   //Libreria para usar el motor shield de arduino
ArduinoMotorShieldR3 motores;   //Declaración de los motores
#include <SD.h>
#include <QTRSensors.h>
#include <AFMotor.h>
#include <Wire.h>
extern "C" {
    #include "utility/twi.h" // from Wire library, so we can do bus scanning
}
#define TCAADDR 0x70
#include "Arduino.h"
#include "SparkFunISL29125.h"

//Librerias girospocio
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>



// Variables de lectura para sensores RGB
uint16_t RGB_sensorR1,RGB_sensorG1,RGB_sensorB1;
uint16_t RGB_sensorR2,RGB_sensorG2,RGB_sensorB2;
// sensores g
const int mpuAddress = 0x68;  // Puede ser 0x68 o 0x69
MPU6050 mpu(mpuAddress);
// Inicialización de los objetos para sensores RGB
SFE_ISL29125 RGB_sensor1;
SFE_ISL29125 RGB_sensor2;


// Pines del ultrasonico
int trigPin = 26;           //pin trigger disparado se puede usar otro pin digital
int echoPin = 27;           // Pin eco. Se puede usar otro pin digital
long duration, inches, cm;  // Declara variables



//puertos de conección de sensor infrarojo
int izq_1=A8;
int izq_2=A9;
int izq_3=A10;
int centro_i=A11;
int centro_d=A12;
int der_6=A13;
int der_7=A14;
int der_8=A15;

//Variables donde se guardan las lecuturas del sensor infrarojo
int l1=0;
int l2=0;
int l3=0;
int l4=0;
int l5=0;
int l6=0;
int l7=0;
int l8=0;

//Variables para valor digital de lectura del sensor infrarojo
int dl1=0;
int dl2=0;
int dl3=0;
int dl4=0;
int dl5=0;
int dl6=0;
int dl7=0;
int dl8=0;

//Variables para valor digital ANTERIOR de lectura del sensor infrarojo
int al1=0;
int al2=0;
int al3=0;
int al4=0;
int al5=0;
int al6=0;
int al7=0;
int al8=0;

// secuencia de iguales
int cont_igual=0;

//Variables para deficion de la velocidad de los motores 
int velD = 180;
int velI = 180;
int atrD = -160;
int atrI = -160;
//variables para la rampa
int acelI=270;
int acelD=270;
int norI=180;
int norD=180;
//variables 90°
int velND = 330;
int velNI = 330;
int velRD = -340;
int velRI = -320;

// puertos del monitor del leds
int mo1 = 31;
int mo2 = 33;
int mo3 = 35;
int mo4 = 37;
int mo5 = 39;
int mo6 = 41;
int mo7 = 43;
int mo8 = 45;
int led_RGBI=29;
int led_RGBD=47;
int giro = 48;

//giroscopio
int ax, ay, az;
int gx, gy, gz;

int accel_ang_x= atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);

//valores de blanco y negro
int bco=620;  //600
int negro=0;  //900
int blanco = 1;

// Limites para encontar el color RGB
//Izquierdo
int min_verdeI=1750;
int max_verdeI=1950;
//Derecho
int min_verdeD=1300;
int max_verdeD=1500;

//Banderas para color encontrado
int enc_color_I=0;
int enc_color_D=0;
long time0;

//------------------------------------------------------------------------------SetUp
void setup() {
    Serial.println("entre setup");
    //Puerto serial 
    Serial.begin(9600);
    //inicia motores  
    motores.init();
    
    //giroscopio
     Serial.begin(9600);
   Wire.begin();
   mpu.initialize();
   Serial.println(mpu.testConnection() ? F("IMU iniciado correctamente") : F("Error al iniciar IMU"));
   
    //inicia puertos digitales para sensores infrarojos 
    pinMode(izq_1,INPUT);
    pinMode(izq_2,INPUT);
    pinMode(izq_3,INPUT);
    pinMode(centro_i,INPUT);
    pinMode(centro_d,INPUT);
    pinMode(der_6,INPUT);
    pinMode(der_7,INPUT);
    pinMode(der_8,INPUT);
    
    // sensor ultrasonico
    pinMode(trigPin, OUTPUT); // Establece pin como salida
    pinMode(echoPin, INPUT); // Establece pin como entrada
    digitalWrite(trigPin, LOW); // Pone el pin a un estado logico bajo
    
    //Monitor infrarojo como salida 
    pinMode(mo1, OUTPUT);
    pinMode(mo2, OUTPUT);
    pinMode(mo3, OUTPUT);
    pinMode(mo4, OUTPUT);
    pinMode(mo5, OUTPUT);
    pinMode(mo6, OUTPUT);
    pinMode(mo7, OUTPUT);
    pinMode(mo8, OUTPUT);
    //Inicia leds del monitor a BAJO
    digitalWrite(mo1, LOW);
    digitalWrite(mo2, LOW);
    digitalWrite(mo3, LOW);
    digitalWrite(mo4, LOW);
    digitalWrite(mo5, LOW);
    digitalWrite(mo6, LOW);
    digitalWrite(mo7, LOW);
    digitalWrite(mo8, LOW);
    //led del giroscopio como salida
    digitalWrite(giro,OUTPUT);
    //Inicia led del giroscopio
    digitalWrite(giro, LOW);
    
    // monitor de RGB
    pinMode(led_RGBI,OUTPUT);
    pinMode(led_RGBD,OUTPUT);
    //Inicia leds del monitor a BAJO
    digitalWrite(led_RGBI, LOW);
    digitalWrite(led_RGBD, LOW);
    // Inicializa el 1er sensor RGB Izquierdo
    tcaselect(1);
    Serial.println("entre setup 1");
    if (RGB_sensor1.init())    //Iniciar 1° sensor RGB
       {
           Serial.println("Sensor 1 iniciado");
       }
    else 
       {
           Serial.println("Sensor 1 ERROR de iniciado");
       }
      
    // Inicializa el 2° sensor RGB Derecho
    tcaselect(2);
    if (RGB_sensor2.init())    //Iniciar 2° sensor RGB
       {
           Serial.println("Sensor 2 iniciado");
       }
    else 
       {
           Serial.println("Sensor 2 ERROR de iniciado");
       }
    Serial.println("sali setup");
      
}
void loop() {
  Serial.println("loop");
   // enc_color();
    //Se guardan datos del sensor infrarrojo
    //muestra lecturas en el monitor
    leerinfra(); 
    monitor();
    
    giroscopio();
    if ((accel_ang_x<0)){
       velI=acelI;
       velD=acelD;
       Serial.println("Inclinado");
    }else{
       velI=norI;
       velD=norD;
       Serial.println("Horizontal");
    }
    delay(2000);

    //-------------------------------------
    //    busca el camino
    //-------------------------------------

  buscar();
//imprimirDatosInf();
    
     
}


    
//------------------------------------------------------------------------------Movimiento de los motores
void buscar(){


  if (cont_igual>=20){
     Moverse (-180, -180);
     delay(500);
     Moverse (220,220);
     delay(800); 
     Moverse (velI, velD);
  }
  Serial.print("cont_igual ");
  Serial.println(cont_igual);
  
   // 11111111
   if ((dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == blanco)) {
      Moverse (velI, velD);
   }else{
      // 00000000
      if ((dl1 == negro && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro)) {
           //------------------------------------checar busqueda de parche verde---------------------------------
  /*         Moverse(0,0);
           delay (2000);
           Moverse(100, 100);
           delay (600);*/
           Moverse(atrI,velD);
           /*delay (500);*/
      }else{
           //01111111
           //10111111
           //11011111
           if ((dl1 == negro && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
               (dl1 == blanco && dl2 == negro && dl3 == blanco &&  dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
               (dl1 == blanco && dl2 == blanco && dl3 == negro && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == blanco)) {
                 Moverse (atrI, velD);
           }else{
                // 11111110
                // 11111101
                // 11111011
                if ((dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == negro)||
                    (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == negro && dl8 == blanco)||
                    (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == negro && dl7 == blanco && dl8 == negro)) {
                      Moverse (velI, atrD);
                }else{
                     // 11100111
                     // 11101111
                     // 11110111
                     if ((dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == negro && dl5 == negro && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
                         (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == negro && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 ==blanco)||
                         (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == negro && dl6 == blanco && dl7 == blanco && dl8 == blanco)) {
                           Moverse (velI, velD);
                     }else{
                          // 11001111
                          // 10011111
                          // 00111111
                          if ((dl1 == blanco && dl2 == blanco && dl3 == negro && dl4 == negro && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 ==blanco)||
                              (dl1 == blanco && dl2 == negro && dl3 == negro && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 ==blanco)||
                              (dl1 == negro  && dl2 == negro && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == blanco)) {
                                 Moverse ( atrI, velD );
                          }else{
                               // 11110011 
                               // 11111001
                               // 11111100
                               if ((dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == negro && dl6 == negro && dl7 == blanco && dl8 ==blanco)||
                                   (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == negro && dl7 == negro && dl8 ==blanco)||
                                   (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == negro && dl8 ==negro)) {
                                     Moverse (velI, atrD);
                               }else{
                                    // 11000111
                                    // 10001111
                                    // 00011111
                                    if ((dl1 == blanco && dl2 == blanco && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == blanco && dl7 == blanco && dl8 ==blanco)||
                                        (dl1 == blanco && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 ==blanco)||
                                        (dl1 == negro && dl2 == negro && dl3 == negro && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 ==blanco)) {
                                           Moverse ( atrI, velD );
                                    }else{
                                         // 11100011
                                         // 11110001
                                         // 11111000
                                         if ((dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == blanco && dl8 ==blanco)||
                                             (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco&& dl5 == negro && dl6 ==negro && dl7 == negro && dl8 ==blanco)||
                                             (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == negro && dl7 == negro && dl8 ==negro)) {
                                                Moverse (velI, atrD);
                                         }else{
                                              // 00001111
                                              // 10000111
                                              if ((dl1 == negro && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 ==blanco)||
                                                  (dl1 == blanco && dl2 ==negro && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == blanco && dl7 == blanco && dl8 ==blanco)) {
                                                     Moverse ( atrI, velD );
                                              }else{
                                                   // 11110000
                                                   // 11100001
                                                   if ((dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro)||
                                                       (dl1 == blanco && dl2 == blanco && dl3 ==  blanco && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 ==blanco)){
                                                          Moverse (velI, atrD);
                                                   }else{
                                                        // 00000111
                                                        // 10000011
                                                        if((dl1 == negro && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
                                                           (dl1 == blanco && dl2 == negro && dl3 == negro && dl4 == negro && dl5 ==negro && dl6 == negro && dl7 == blanco && dl8 == blanco)) {
                                                              Moverse ( atrI, velD );
                                                        }else{
                                                             // 11100000
                                                             // 11000001
                                                             if((dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro)||
                                                                (dl1 == blanco && dl2 == blanco && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 ==blanco)) {
                                                                   Moverse (velI, atrD);
                                                             }else{
                                                                  // 00000011
                                                                  if((dl1 == negro && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == blanco && dl8 == blanco)){
                                                                      Moverse (velRD, velNI);
                                                                  }else{
                                                                       // 11000000
                                                                       if((dl1 == blanco && dl2 == blanco && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro)){
                                                                           Moverse (velNI, velRD);
                                                                       }else{
                                                                            // 00000001
                                                                            if((dl1 == negro && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == blanco)){
                                                                                Moverse ( velRD, velND);
                                                                            }else{
                                                                                 // 10000000
                                                                                 if((dl1 == blanco && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro)){
                                                                                     Moverse (velND,velRD);
                                                                                 }else{
                                                                                      //---------------------------Detenerse--------------------------------
                                                                                      Moverse (0,0); 
                                                                                      //delay(5000); 
                                                                                      Moverse(150, 150 ); 

                                                                                      /* if ((RGB_sensorG1>=min_verdeI && RGB_sensorG1<=max_verdeI)){
                                                                                          Moverse (atrI, velD);
                                                                                            delay(5000);
                                                                                       }else{
                                                                                        
                                                                                       }*/
                                                                                 }
                                                                            }
                                                                       }
                                                                  }
                                                             }
                                                        }
                                                   }
                                              }
                                         }
                                    }
                               }
                          }
                     }
                } 
           }               
      }               
 }
}


//------------------------------------------------------------------------------Movimiento de los motores
int Moverse( int velI_,int velD_) {
  motores.setM1Speed((velD_)); 
  motores.setM2Speed((velI_)); 
}


//------------------------------------------------------------------------------lee sensor infrarojo 
void leerinfra(){
    l1=analogRead(izq_1);
    l2=analogRead(izq_2);
    l3=analogRead(izq_3);
    l4=analogRead(centro_i);
    l5=analogRead(centro_d);
    l6=analogRead(der_6);
    l7=analogRead(der_7);
    l8=analogRead(der_8);
    
    //Conversion de datos a 0 1  1=blanco 0=negro
      
    if (l1<=bco){dl1=1;} else {dl1=0;}
    if (l2<=bco){dl2=1;} else {dl2=0;}
    if (l3<=bco){dl3=1;} else {dl3=0;}
    if (l4<=bco){dl4=1;} else {dl4=0;}
    if (l5<=bco){dl5=1;} else {dl5=0;}
    if (l6<=bco){dl6=1;} else {dl6=0;}
    if (l7<=bco){dl7=1;} else {dl7=0;}
    if (l8<=bco){dl8=1;} else {dl8=0;}



    if ((dl1==al1) && (dl2==al2) && (dl3==al3) && (dl4==al4) && (dl5==al5) && (dl6==al6) && (dl7==al7) && (dl8==al8)){
        cont_igual++;
        Serial.print("igual ");
    }else{
        cont_igual=0;
        al1=dl1;
        al2=dl2;
        al3=dl3;
        al4=dl4;
        al5=dl5;
        al6=dl6;
        al7=dl7;
        al8=dl8;
        Serial.print("diferente  ");
    }
    if ((dl1==1) && (dl2==1) && (dl3==1) && (dl4==1) && (dl5==1) && (dl6==1) && (dl7==1) && (dl8==1)){
        cont_igual=0;
        al1=dl1;
        al2=dl2;
        al3=dl3;
        al4=dl4;
        al5=dl5;
        al6=dl6;
        al7=dl7;
        al8=dl8;
        Serial.print("blancos  ");
    }


    
}



//---------------------------------------------------------------------------------Selecciona puerto I2C  
void tcaselect(uint8_t i) {
    if (i > 7) return;
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << i);
    Wire.endTransmission();
}

//---------------------------------------------------------------------------------Lee los sensores RGB
void enc_color(){
    //-------------------------RGB
    // SparkFun ISL29125 - RGB Light Sensor - Test Code
    // Compare red value and blue value in RGB_sensor
    tcaselect(1);
    
    //RGB_sensorR1 = RGB_sensor1.readRed();
    RGB_sensorG1 = RGB_sensor1.readGreen();
    //RGB_sensorB1 = RGB_sensor1.readBlue();
    //Serial.print(F("R1: "));    Serial.print(RGB_sensorR1);
    Serial.print(F("\tG1: "));  Serial.println(RGB_sensorG1);
    //Serial.print(F("\tB1: "));  Serial.println(RGB_sensorB1);
    delay(3000);
    
    // Compare red value and blue value in RGB_sensor
    tcaselect(2);
    //RGB_sensorR2 = RGB_sensor2.readRed();
    RGB_sensorG2 = RGB_sensor2.readGreen();
    //RGB_sensorB2 = RGB_sensor2.readBlue();
    //Serial.print(F("R2: "));    Serial.print(RGB_sensorR2);
    Serial.print(F("\tG2: "));  Serial.println(RGB_sensorG2);
    //Serial.print(F("\tB2: "));  Serial.println(RGB_sensorB2);  
    delay(3000);

    if ((RGB_sensorG1>=min_verdeI && RGB_sensorG1<=max_verdeI)) {
        enc_color_I=1;
        digitalWrite(led_RGBI,HIGH); 
    }else {
        enc_color_I=0;
        digitalWrite(led_RGBI,LOW);
    }

    if ((RGB_sensorG2>=min_verdeD && RGB_sensorG2<=max_verdeD)) {
        enc_color_D=1; 
        digitalWrite(led_RGBD,HIGH);
    }else {
        enc_color_D=0;
        digitalWrite(led_RGBD,LOW);
    }

}


//---------------------------------------------------------------------------------Muestra lecturas en el puerto serial 
void imprimirDatosInf(){
    Serial.print("Izq 1: ");Serial.print(l1);Serial.print("\t / D Izq 1: ");Serial.print(dl1);Serial.print("\t / A : ");Serial.println(al1);
    Serial.print("Izq 2: ");Serial.print(l2);Serial.print("\t / D Izq 1: ");Serial.print(dl2);Serial.print("\t / A : ");Serial.println(al2);
    Serial.print("Izq 3: ");Serial.print(l3);Serial.print("\t / D Izq 1: ");Serial.print(dl3);Serial.print("\t / A : ");Serial.println(al3);
    Serial.print("Cen i: ");Serial.print(l4);Serial.print("\t / D Izq 1: ");Serial.print(dl4);Serial.print("\t / A : ");Serial.println(al4);
    Serial.print("Cen d: ");Serial.print(l5);Serial.print("\t / D Izq 1: ");Serial.print(dl5);Serial.print("\t / A : ");Serial.println(al5);
    Serial.print("Der 6: ");Serial.print(l6);Serial.print("\t / D Izq 1: ");Serial.print(dl6);Serial.print("\t / A : ");Serial.println(al6);
    Serial.print("Der 7: ");Serial.print(l7);Serial.print("\t / D Izq 1: ");Serial.print(dl7);Serial.print("\t / A : ");Serial.println(al7);
    Serial.print("Der 8: ");Serial.print(l8);Serial.print("\t / D Izq 1: ");Serial.print(dl8);Serial.print("\t / A : ");Serial.println(al8);
    Serial.println("-----------------------------------------------------------------------------");
    Serial.print("Enc color Izquierdo ");Serial.println(enc_color_I);
    Serial.print("Enc color Derecho ");Serial.println(enc_color_D);
    Serial.println("-----------------------------------");
    delay(1500);
}


//-----------------------------------------------------------------------------------muestra datos en barra de leds
void monitor(){
    if (dl1 == blanco){
       digitalWrite(mo1,HIGH);
    }else {
      digitalWrite(mo1,LOW);
    }
    if (dl1 == blanco){
       digitalWrite(mo1,HIGH);
    }else {
      digitalWrite(mo1,LOW);
    }
    if (dl2 == blanco){
       digitalWrite(mo2,HIGH);
    }else {
      digitalWrite(mo2,LOW);
    }
    if (dl3 == blanco){
       digitalWrite(mo3,HIGH);
    }else {
      digitalWrite(mo3,LOW);
    }
    if (dl4 == blanco){
       digitalWrite(mo4,HIGH);
    }else {
      digitalWrite(mo4,LOW);
    }
    if (dl5 == blanco){
       digitalWrite(mo5,HIGH);
    }else {
      digitalWrite(mo5,LOW);
    }
    if (dl6 == blanco){
       digitalWrite(mo6,HIGH);
    }else {
      digitalWrite(mo6,LOW);
    }
    if (dl7 == blanco){
       digitalWrite(mo7,HIGH);
    }else {
      digitalWrite(mo7,LOW);
    }
    if (dl8 == blanco){
       digitalWrite(mo8,HIGH);
    }else {
      digitalWrite(mo8,LOW);
    }
    if (RGB_sensorG1>=min_verdeI && RGB_sensorG1<=max_verdeI){
      digitalWrite(led_RGBI,HIGH);
    }else {
      digitalWrite(led_RGBI,LOW);
    }
     if (RGB_sensorG2>=min_verdeD && RGB_sensorG2<=max_verdeD){
      digitalWrite(led_RGBD,HIGH);
    }else {
      digitalWrite(led_RGBD,LOW);
    }
    if (accel_ang_x<0) {
      digitalWrite(giro,HIGH);
    }else{
      digitalWrite(giro,LOW);
    }
}
void giroscopio(){
  tcaselect(7);
   // Leer las aceleraciones 
   mpu.getAcceleration(&ax, &ay, &az);
 
   //Calcular los angulos de inclinacion
   
   float accel_ang_x = atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);
   float accel_ang_y = atan(ay / sqrt(pow(ax, 2) + pow(az, 2)))*(180.0 / 3.14);
 
   // Mostrar resultados
   Serial.print(F("Inclinacion en X: "));
   Serial.print(accel_ang_x);
   Serial.print(F("\tInclinacion en Y:"));
   Serial.println(accel_ang_y);
   //delay(10);
}
