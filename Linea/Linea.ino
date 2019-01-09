#include <ArduinoMotorShieldR3.h>   //Libreria para usar el motor shield de arduino

ArduinoMotorShieldR3 motores;   //Declaración de los motores

// Pines del ultrasonico
int trigPin = 24;//pin trigger disparado se puede usar otro pin digital
int echoPin = 25; // Pin eco. Se puede usar otro pin digital
long duration, inches, cm; // Declara variables


//localizacion de los pines de los sensores
//sensor infrarojo
int izq_1=A15;
int izq_2=A14;
int izq_3=A13;
int centro_i=A12;
int centro_d=A11;
int der_6=A10;
int der_7=A9;
int der_8=A8;

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

int velD = 120;
int velI = 120;

//valores de blanco y negro
int bco=520;  //620
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
  
}

void loop() {
  //Se guardan datos del sensor infrarrojo
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

  //Moverse en linea recta
  //imprimirDatosInf();
  Moverse(velD, velI);
  
  if(dl3 == negro){
    Moverse(velD, 0);  
  }
  if(dl6 == negro){
    Moverse(0, velI);
  }
  if(dl3 == negro && dl2 == negro){
    Moverse(velD + 30 , -120);
  }
  if(dl6 == negro && dl7 == negro){
    Moverse(-120 , velI + 30);
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
  delay(1000);
}

//Movimiento de los motores
int Moverse(int velD_, int velI_){
  motores.setM1Speed((velD_));
  motores.setM2Speed((velI_));
}
int ultrasonico(){
// Pulso de 10us para inicial el modulo
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH); //Devuelve la longitud del pulso del pin Echo en us
   // Imprime valores por el puerto serie:
   // Convierte el tiempo de recepción del eco en distancia:
   cm = microsecondsToCentimeters(duration);
   // Imprime valores por el puerto serie:  
   return cm;
   }
   // Calcula la distancia en cm
  long microsecondsToCentimeters(long microseconds) {
  return microseconds/58;
} 
