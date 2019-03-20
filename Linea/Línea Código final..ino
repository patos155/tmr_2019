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
uint16_t RGB_sensorR3,RGB_sensorG3,RGB_sensorB3;
uint16_t RGB_sensorR4,RGB_sensorG4,RGB_sensorB4;

// sensores g
const int mpuAddress = 0x68;  // Puede ser 0x68 o 0x69
MPU6050 mpu(mpuAddress);

// Inicialización de los objetos para sensores RGB
SFE_ISL29125 RGB_sensor1;
SFE_ISL29125 RGB_sensor2;
SFE_ISL29125 RGB_sensor3;
SFE_ISL29125 RGB_sensor4;


//--------------------------------------- Definición de puertos para sensores y monitores 
  // Pines del ultrasonico
    int Trigger = 27;   //Pin digital 2 para el Trigger del sensor
    int Echo = 26;   //Pin digital 3 para el Echo del sensor
    int t; //timepo que demora en llegar el eco
    int d; //distancia en centimetros
  
  //puertos de conección de sensor infrarojo
    int izq_1=A8;
    int izq_2=A9;
    int izq_3=A10;
    int centro_i=A11;
    int centro_d=A12;
    int der_6=A13;
    int der_7=A14;
    int der_8=A15;
  
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


//------------------------------------------------ Variables para configurar el funcionamiento del Robot
      // Calibrar o Buscar (Calibrar en CERO buscar en UNO)
      int busca=1;

    
    // Espera para las curvas de 90°
      int rd=100;
      int esp_giro=1000;

    //Variables para deficion de la velocidad de los motores
      // Velocidad normal adelante 
        int velD = 130;
        int velI = 130;
      // Velocidad minima adelante (se desvia un poco)
        int minD = 0;
        int minI = 0;
      // Velocidad maxima adelante (se desvia mucho)
        int maxI = 140;
        int maxD = 140;
      // Velocidad de reversa (esquinas e intersecciones)
        int atrD = -120;
        int atrI = -120;
      //velocidades para la rampa
        int acelI=225;
        int acelD=225;
        int norI=125;
        int norD=125;
      //variables 90° ????????????????????????????????????????????
        int velND = 230;
        int velNI = 230;
        int velRD = -260;
        int velRI = -260;
      
     
    //ultra variables  ??????????????????????????????????????????
      int uldI = 180;
      int uldD = 180;

  
  //valores de blanco y negro
    int bco=500;//600
    int negro=0;  //600
    int blanco = 1;
  
  // Limites para encontar el color RGB
    //RGB1
      int min_verde1=1400;
      int max_verde1=1600;
    //RGB2
      int min_verde2=6700;
      int max_verde2=7000;
    //RGB3
      int min_verde3=1400;
      int max_verde3=1600;
    //RGB4
      int min_verde4=1800;
      int max_verde4=2000;
  // Valor para determinar la nclinación en la rampa 
    int inclinado = 12;

//---------------------------------------------------- Variables de trabajo 
  // encontre el verde 
  int enc_verde1=0;
  int enc_verde2=0;
  //Variables donde se guardan las lecuturas analogas del sensor infrarojo
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

  //giroscopio
    int ax, ay, az;
    int gx, gy, gz;
    float accel_ang_x;
    float accel_ang_y;
  
  // secuencia de iguales para los topes 
    int cont_igual=0;
  
  //Banderas para color encontrado
    int enc_color_I=0;
    int enc_color_D=0;
    long time0;

//------------------------------------------------------------------------------SetUp
void setup() {
    //Puerto serial 
    Serial.begin(9600);
    Serial.println("entre setup");
    Wire.begin();
    
    //inicia motores  
    motores.init();
    
    //giroscopio
    tcaselect(7);
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
    pinMode(Trigger, OUTPUT); //pin como salida
    pinMode(Echo, INPUT);  //pin como entrada
    digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  
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
    
    //hay que asignarlo como salida 
    pinMode(giro, OUTPUT); 
    //Inicia led del giroscopio
    digitalWrite(giro, LOW);
    
    // monitor de RGB
    pinMode(led_RGBI,OUTPUT);
    pinMode(led_RGBD,OUTPUT);
    //Inicia leds del monitor a BAJO
    digitalWrite(led_RGBI, LOW);
    digitalWrite(led_RGBD, LOW);
    
    
    // Inicializa el 1er sensor RGB Izquierdo
    Serial.println("entre setup 1");
    tcaselect(0);
    if (RGB_sensor1.init())    //Iniciar 1° sensor RGB
       {
           Serial.println("Sensor RGB 1 iniciado");
       }
    else 
       {
           Serial.println("Sensor RGB 1 ERROR de iniciado");
       }
       
    tcaselect(1);
    if (RGB_sensor2.init())    //Iniciar 1° sensor RGB
       {
           Serial.println("Sensor RGB 2 iniciado");
       }
    else 
       {
           Serial.println("Sensor RGB 2 ERROR de iniciado");
       }
      
    // Inicializa el 2° sensor RGB Derecho
    tcaselect(2);
    if (RGB_sensor3.init())    //Iniciar 2° sensor RGB
       {
           Serial.println("Sensor RGB 3 iniciado");
       }
    else 
       {
           Serial.println("Sensor RGB 3 ERROR de iniciado");
       }
    
    tcaselect(3);
    if (RGB_sensor4.init())    //Iniciar 2° sensor RGB
       {
           Serial.println("Sensor RGB 4 iniciado");
       }
    else 
       {
           Serial.println("Sensor RGB 4 ERROR de iniciado");
       }
        Serial.println("sali setup");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                             LOOP
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void loop() {
    Serial.println("loop");


    //------  Encuentra colores y selecciona el camino-------------
    enc_color();
    
    //Lee datos del sensor Infrarojo
    leerinfra(); 
    //muestra lecturas en el monitor
    monitor();
    if (busca==0){
        //----------- Muestra los datos para calibración de sensores (DEBE ESTAR0BUSCA EN CERO PARA EVITAR SEGUIR LA LINEA)
        imprimirDatosInf();
    }else{ 
        //----------- Busca el camino (DEBE ESTAR0 BUSCA EN UNO PARA SEGUIR LA LINEA)
        buscar();
    }
    //------  Lee el sensor ultrasonico y calcula distancia al obstaculo  ------------ 
    //ultra();
    //------  Evade los obstaculos ---------------------------------------------------    
    //ultra_so();

    
    

   
    giroscopio();
    //Serial.println("regresado ");
    //Serial.println(accel_ang_x);
    if ((accel_ang_x > inclinado)){
       velI=acelI;
       velD=acelD;
       //Serial.println("Inclinado");
       digitalWrite(giro, HIGH);
    }else{
       velI=norI;
       velD=norD;
       //Serial.println("Horizontal");
       digitalWrite(giro, LOW);
    }
 //    delay(300);
     
}


    
//------------------------------------------------------------------------------Movimiento de los motores
void buscar(){
     
    //--------------  Si esta detenido regresa y toma impulso -----------------------------------
    if (cont_igual>=30){
        Moverse (-180, -180);
        delay(500);
        Moverse (220,220);
        delay(800); 
        Moverse (velI, velD);
    }
    Serial.print("cont_igual ");
    Serial.println(cont_igual);

    
    // 11111111               TODOS EN BLANCO
    // 11100111               NEGRO 4 Y 5                SIGUE DE FRENTE  
    // 11101111               NEGRO  4
    // 11110111               NEGRO  5 
    // 11000111               NEGRO  3, 4 Y 5
    // 11000111               NEGRO  3, 4 , 5 y 6
    if ((dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
        (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == negro  && dl5 == negro  && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
        (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == negro  && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 ==blanco )||
        (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == negro  && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
        (dl1 == blanco && dl2 == blanco && dl3 == negro  && dl4 == negro  && dl5 == negro  && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
        (dl1 == blanco && dl2 == blanco && dl3 == negro  && dl4 == negro  && dl5 == negro  && dl6 == negro && dl7 == blanco && dl8 == blanco)) {
        Moverse (velI, velD);
    }else{
        // 00000000                            INTERSECCIÓN RETROCEDE Y NUSCA EL CAMINO
        // 10000001  
        // 10000000
        if ((dl1 == negro  && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro )||
            (dl1 == blanco && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == blanco)||
            (dl1 == blanco && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro )) {
                Moverse(0,0);
                delay(200);
                /*Moverse ( atrI, atrD );
                //-----------------------------Checar----------------------------------------------------
                //revisar que regrese hasta que los senores queden a la altura de los parches 
                delay(500);
                Moverse(0,0);
                enc_verde1=0;
                enc_verde2=0;
                // Busca los parches verdes en un cilclo de maximo 20 loops 
                int contador=0;
                while (enc_verde1==0 && enc_verde2==0 && contador<=100){
                     enc_color();
                     contador++;  
                }
                // gira cuando encuentra los parches verdes 
                Giro_RGB();*/
                //---------------------------------------------------------------------------------------
        }else{    
            //11011111            NEGRO 3           
            //11001111            NEGRO 3 Y 4          POCO DESVIADO A LA DERECHA
            if ((dl1 == blanco && dl2 == blanco && dl3 == negro  && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
                (dl1 == blanco && dl2 == blanco && dl3 == negro  && dl4 == negro  && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 ==blanco)) {
                    Moverse (minI, velD);
            }else{
                //01111111            NEGRO 6         
                //00111111            NEGRO 5 Y 6          MUY DESVIADO A LA DERECHA
                if ((dl1 == negro  && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
                    (dl1 == negro  && dl2 == negro  && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 ==blanco)) {
                        Moverse (minI, maxD);
                }else{
                    //11111011            NEGRO 6           
                    //11110011            NEGRO 5 Y 6          POCO DESVIADO A LA IZQUIERDA
                    if ((dl1 == blanco && dl2 == blanco && dl3 == blanco  && dl4 == blanco && dl5 == blanco && dl6 == negro && dl7 == blanco && dl8 == blanco)||
                        (dl1 == blanco && dl2 == blanco && dl3 == blanco  && dl4 == blanco && dl5 == negro  && dl6 == negro && dl7 == blanco && dl8 == blanco)) {
                            Moverse (velI, minD);
                    }else{
                        //11111110            NEGRO 8         
                        //11111100            NEGRO 7 Y 8          MUY DESVIADO A LA IZQUIERDA
                        if ((dl1 == blanco  && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == negro )||
                            (dl1 == blanco  && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == negro  && dl8 == negro)) {
                                Moverse (maxI, minD);
                        }else{
                            // 11000111
                            // 10001111      CURVA IZQUIRDA
                            // 00011111
                            if ((dl1 == blanco && dl2 == blanco && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == blanco && dl7 == blanco && dl8 ==blanco)||
                                (dl1 == blanco && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 ==blanco)||
                                (dl1 == negro && dl2 == negro && dl3 == negro && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 ==blanco)) {
                                    Moverse ( atrI, velD );
                            }else{
                                // 11100011
                                // 11110001     CURVA DERECHA 
                                // 11111000
                                // 11100001
                                // 01000111
                                // 01100011
                                if ((dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == negro  && dl5 == negro  && dl6 == negro  && dl7 == blanco && dl8 == blanco)||
                                    (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == negro  && dl6 == negro  && dl7 == negro  && dl8 == blanco)||
                                    (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == negro  && dl7 == negro  && dl8 == negro )||
                                    (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == negro  && dl5 == negro  && dl6 == negro  && dl7 == negro  && dl8 == blanco)||
                                    (dl1 == negro  && dl2 == blanco && dl3 == negro  && dl4 == negro  && dl5 == negro  && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
                                    (dl1 == negro  && dl2 == blanco && dl3 == blanco && dl4 == negro  && dl5 == negro  && dl6 == negro  && dl7 == blanco && dl8 == blanco)) {
                                        Moverse (velI, atrD); 
                                }else{                
                                    // 00001111    
                                    // 00000111           ESQUINA 90° IZQUIERDA
                                    // 00000011
                                    // 10000011
                                    if ((dl1 == negro  && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 ==blanco)||
                                        (dl1 == negro  && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro  && dl6 == blanco && dl7 == blanco && dl8 ==blanco)||
                                        (dl1 == negro  && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro  && dl6 == negro  && dl7 == blanco && dl8 ==blanco)||
                                        (dl1 == blanco && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro  && dl6 == negro  && dl7 == blanco && dl8 ==blanco)) {
                                            Moverse ( atrI, maxD );
                                            delay(rd);
                                    }else{
                                        // 11110000 
                                        // 11100000         90° DERECHA
                                        // 11000000
                                        // 11000001
                                        if ((dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro )||
                                            (dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == negro  && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro )||
                                            (dl1 == blanco && dl2 == blanco && dl3 == negro  && dl4 == negro  && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro )||
                                            (dl1 == blanco && dl2 == blanco && dl3 == negro  && dl4 == negro  && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == blanco)){
                                                Moverse (maxI, atrD);
                                                delay(rd);
                                        }else{
                                            //---------------------------Detenerse--------------------------------
                                            /*Moverse (0,0); 
                                            delay(5000); 
                                            Moverse (velI, velD);
                                            delay(100);*/
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
    // Lectura analogica de los senores Infrarrojos 
    l1=analogRead(izq_1);
    l2=analogRead(izq_2);
    l3=analogRead(izq_3);
    l4=analogRead(centro_i);
    l5=analogRead(centro_d);
    l6=analogRead(der_6);
    l7=analogRead(der_7);
    l8=analogRead(der_8);
    
    //Conversion de datos analogos a Digitales  a 0 1  1=blanco 0=negro
      
    if (l1<=bco){dl1=1;} else {dl1=0;}
    if (l2<=bco){dl2=1;} else {dl2=0;}
    if (l3<=bco){dl3=1;} else {dl3=0;}
    if (l4<=bco){dl4=1;} else {dl4=0;}
    if (l5<=bco){dl5=1;} else {dl5=0;}
    if (l6<=bco){dl6=1;} else {dl6=0;}
    if (l7<=bco){dl7=1;} else {dl7=0;}
    if (l8<=bco){dl8=1;} else {dl8=0;}


    // Cuenta las lecturas iguales para saber si esta detenido en un tope 
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

    // Si son iguales pero todos blancos no incrementa la secuencia 
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


//---------------------------------------------------------------------------------Lee los sensores RGB
void enc_color(){
    //-------------------------RGB
    
    tcaselect(0);
    RGB_sensorG1 = RGB_sensor1.readGreen();
    Serial.print(F("\tG1: "));  Serial.println(RGB_sensorG1);
    tcaselect(1);
    RGB_sensorG2 = RGB_sensor2.readGreen();
    Serial.print(F("\tG2: "));  Serial.println(RGB_sensorG2);
    if ((RGB_sensorG1>=min_verde1 && RGB_sensorG1<=max_verde1) || (RGB_sensorG2>=min_verde2 && RGB_sensorG2<=max_verde2)) {
       enc_verde1=1;
    }else{
       enc_verde1=0;
    }
    
    tcaselect(2);
    RGB_sensorG3 = RGB_sensor3.readGreen();
    Serial.print(F("\tG3: "));  Serial.println(RGB_sensorG3);
    
    tcaselect(3);
    RGB_sensorG4 = RGB_sensor4.readGreen();
    Serial.print(F("\tG4: "));  Serial.println(RGB_sensorG4);
    //delay(1000);

    if ((RGB_sensorG3>=min_verde3 && RGB_sensorG3<=max_verde3) || (RGB_sensorG4>=min_verde4 && RGB_sensorG4<=max_verde4)){
        enc_verde2=1;
    }else{
        enc_verde2=0;
    }


}





//---------------------------------------------------------------------------------  Encuentra los parches verdes 
void Giro_RGB(){
    // Encuentra parche Izquierdo 
    if (enc_verde1==1 && enc_verde2==0) {
        digitalWrite(led_RGBI,HIGH);
        Serial.print("Verde Izquierdo");
        Moverse(atrI,velD);
        delay(esp_giro);
        
    }else {
        // Encuentra parche derecho 
        if (enc_verde1==1 && enc_verde2==0) {
            digitalWrite(led_RGBD,HIGH);
            Serial.print("Verde Derecha");
            Moverse(velI,atrD);
            delay(esp_giro);
        }else{
            // Encuentra ambos parches 
            if (enc_verde1==1 && enc_verde2==1) {
                digitalWrite(led_RGBD,HIGH);
                digitalWrite(led_RGBI,HIGH);
                Serial.print(" Ambos lados");
                // Moverse hacia atras 
                Moverse(0,0);
                delay(50000);
            }else{
                digitalWrite(led_RGBD,LOW);
                digitalWrite(led_RGBI,LOW);
            }
        }
    }
}



//--------------------------------------------------------------  Evade los obstaculos 
void ultra_so(){
  if ((d<=10)){
    delay(200);
    Moverse(velI,atrD);
     delay(1000);
    Moverse(0,0);
    delay(3000);
    Moverse(velI,velD);
     delay(1000);
    Moverse(0,0);
     delay(200);
    Moverse(atrI,velD);
     delay(1000);
    Moverse(0,0);
    delay(3000);
    Moverse(velI,velD);
     delay(1000);
    Moverse(0,0);
      delay(200);
    Moverse(atrI,velD);
     delay(1000);
    Moverse(0,0);
     delay(3000);
    Moverse(velI,velD);
     delay(1000);
    Moverse(0,0);
     delay(200);
    Moverse(velI,atrD);
     delay(1000);
    Moverse(0,0);
    delay(2000);
    Moverse(velI,velD);
  }
}






//---------------------------------------------------------------------------------Selecciona puerto I2C  
void tcaselect(uint8_t i) {
    if (i > 7) return;
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << i);
    Wire.endTransmission();
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
    Serial.println("-------------------------------------------------------------------------------------------");
    Serial.print("Enc color Izquierdo ");Serial.println(enc_verde1);
    Serial.print("Enc color Derecho ");Serial.println(enc_verde2);
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
    if (d<=10){
        digitalWrite(giro,HIGH);
    }else{
        digitalWrite(giro,LOW);
    }
}



//---------------------------------  Lectura de Giroscopio para saber si esta horizontal o inclinado el robot 
void giroscopio(){
    tcaselect(7);
    // Leer las aceleraciones 
    mpu.getAcceleration(&ax, &ay, &az);
 
    //Calcular los angulos de inclinacion
   
    accel_ang_x = atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);
    accel_ang_y = atan(ay / sqrt(pow(ax, 2) + pow(az, 2)))*(180.0 / 3.14);
 
    // Mostrar resultados
    Serial.print(F("Inclinacion en X-------------: "));
    Serial.print(accel_ang_x);
    Serial.print(F("\tInclinacion en Y-----------:"));
    Serial.println(accel_ang_y);
    //delay(5000);
}

//----------------------------------------------------- Lectura de distancia al obstaculo 
void ultra(){
    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10);          //Enviamos un pulso de 10us
    digitalWrite(Trigger, LOW);
  
    t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
    d = t/59;             //escalamos el tiempo a una distancia en cm
  
    Serial.print("Distancia: ");
    Serial.print(d);      //Enviamos serialmente el valor de la distancia
    Serial.print("cm");
    Serial.println();
    delay(100);          //Hacemos una pausa de 100ms
}
