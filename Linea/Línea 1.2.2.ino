#include <ArduinoMotorShieldR3.h>   //Libreria para usar el motor shield de arduino

ArduinoMotorShieldR3 motores;   //Declaración de los motores

// Pines del ultrasonico

int trigPin = 26;//pin trigger disparado se puede usar otro pin digital
int echoPin = 27; // Pin eco. Se puede usar otro pin digital
long duration, inches, cm; // Declara variables



//sensor infrarojo

int izq_1=A8;
int izq_2=A9;
int izq_3=A10;
int centro_i=A11;
int centro_d=A12;
int der_6=A13;
int der_7=A14;
int der_8=A15;

//Variables donde se guardan las lecuturas del sensor infrarrojo
int l1=0;
int l2=0;
int l3=0;
int l4=0;
int l5=0;
int l6=0;
int l7=0;
int l8=0;

int dl1=0;
int dl2=0;
int dl3=0;
int dl4=0;
int dl5=0;
int dl6=0;
int dl7=0;
int dl8=0;

int velD = 215;
int velI = 215;
int atrD = -180;
int atrI = -180;

// puertos dl monitor del leds

int mo1 = 38;
int mo2 = 40;
int mo3 = 42;
int mo4 = 44;
int mo5 = 46;
int mo6 = 48;
int mo7 = 50;
int mo8 = 52;

//valores de blanco y negro

int bco= 520;  //420
int negro=0;  //720
int blanco = 1;

void setup() {
  motores.init();
  Serial.begin(9600);  
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

  // monitor infrarojo como salida 
  
  pinMode(mo1, OUTPUT);
  pinMode(mo2, OUTPUT);
  pinMode(mo3, OUTPUT);
  pinMode(mo4, OUTPUT);
  pinMode(mo5, OUTPUT);
  pinMode(mo6, OUTPUT);
  pinMode(mo7, OUTPUT);
  pinMode(mo8, OUTPUT);
  
}

void loop() {
  
  //Se guardan datos del sensor infrarrojo
 // leerInfra ();
 
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

  //muestra datos en barra de leds

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
  
//Moverse en linea recta
//imprimirDatosInf();
 //Moverse(velI, velD);

 // 11111111

      if ((dl1 == blanco && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == blanco)) {
          Moverse (velI, velD);
          }else{
           // 00000000
           if ((dl1 == negro && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro)) {
            Moverse (atrI, velD);
             }else{
               //01111111
               //10111111
               //11011111
                 if ((dl1 == negro && dl2 == blanco && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
                 (dl1 == blanco && dl2 == negro && dl3 == blanco && dl4 == blanco && dl5 == blanco && dl6 == blanco && dl7 == blanco && dl8 == blanco)||
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
                                                                                   Moverse (-300, 300 );
                                                                                    }else{
                                                                                      // 11000000
                                                                                      if((dl1 == blanco && dl2 == blanco && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro)){
                                                                                         Moverse (300, -300);
                                                                                             }else{
                                                                                              // 00000001
                                                                                            if((dl1 == negro && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == blanco)){
                                                                                              Moverse ( -300, 300 );
                                                                                                }else{
                                                                                                  // 10000000
                                                                                                  if((dl1 == blanco && dl2 == negro && dl3 == negro && dl4 == negro && dl5 == negro && dl6 == negro && dl7 == negro && dl8 == negro)){
                                                                                                    Moverse (300, -300);
                                                                                                      }else{
                                                                                                       
                                                                  
                                                                                                         Moverse (0,0); 
                                                                                                         //delay(5000); 
                                                                                                         Moverse(150, 150 ); 
                                                                                                         
                                                                                                            
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
    
          void imprimirDatosInf(){
  Serial.print("Izq 1: ");Serial.print(l1);Serial.print("\t / D Izq 1: ");Serial.println(dl1);
  Serial.print("Izq 2: ");Serial.print(l2);Serial.print("\t / D Izq 1: ");Serial.println(dl2);
  Serial.print("Izq 3: ");Serial.print(l3);Serial.print("\t / D Izq 1: ");Serial.println(dl3);
  Serial.print("Cen i: ");Serial.print(l4);Serial.print("\t / D Izq 1: ");Serial.println(dl4);
  Serial.print("Cen d: ");Serial.print(l5);Serial.print("\t / D Izq 1: ");Serial.println(dl5);
  Serial.print("Der 6: ");Serial.print(l6);Serial.print("\t / D Izq 1: ");Serial.println(dl6);
  Serial.print("Der 7: ");Serial.print(l7);Serial.print("\t / D Izq 1: ");Serial.println(dl7);
  Serial.print("Der 8: ");Serial.print(l8);Serial.print("\t / D Izq 1: ");Serial.println(dl8);
  Serial.println("-----------------------------------");
  delay(1500);
}

//Movimiento de los motores
int Moverse( int velI_,int velD_) {
  motores.setM1Speed((velD_)); 
  motores.setM2Speed((velI_)); 
}
 
