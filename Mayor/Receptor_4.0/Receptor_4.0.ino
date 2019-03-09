#include "RF24.h"
RF24 myRadio (7, 8);
//Dirección en la que recibe la información
byte addresses[][6] = {"0"};
//Variables donde se guarda la dirección de los motores
struct package
{
  int valI;
  int valD;
  int valbtn;
};
typedef struct package Package;
Package data;

//Controla motores izquierdos
int r1 = 2;
int r2 = 3;
//Controla motores derechos
int r3 = 4;
int r4 = 5;
//Controla la velocidad
int r5 = 6;
bool vel = LOW;
int led = 49;

void setup() {
  Serial.begin (9600);
  delay(100);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  pinMode(r5, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  //Si la comunicación está disponible entra en el if
  if (myRadio.available())
  {
    //Mientras este disponible la comunicación leerá los datos
    while (myRadio.available())
    {
      myRadio.read(&data, sizeof(data));
      Serial.print(data.valI);
      Serial.print("/");
      Serial.print(data.valD);
      Serial.print("/");
      Serial.println(data.valbtn);
    }
    
    if (data.valbtn == 1) {
      digitalWrite(led, HIGH);
      vel = HIGH;
    } else {
      digitalWrite(led, LOW);
      vel = LOW;
    }

    //Moverá los motores izquierdos según la dirección que reciba
    switch (data.valI)
    {
      case 0: motorStop(r1, r2); break;
      case 1: motorHorario(r1, r2); break;
      case -1: motorAntihorario(r1, r2); break;
    }

    //Moverá los motores derechoss según la dirección que reciba

    switch (data.valD)
    {
      case 0: motorStop(r3, r4); break;
      case 1: motorHorario(r3, r4); break;
      case -1: motorAntihorario(r3, r4); break;
    }

  }
  //Si no está disponible la comunicación imprimirá el mensaje de abajo
  else
  {
    Serial.println("Radio no disponible");
  }
}

//Mueve el motor hacia adelante
void motorHorario(int Pin1, int Pin2)
{
  digitalWrite(Pin1, HIGH);
  digitalWrite(Pin2, LOW);
  digitalWrite(r5, vel);

}

//Mueve el motor hacia atrás
void motorAntihorario(int Pin1, int Pin2)
{
  digitalWrite(Pin2, HIGH);
  digitalWrite(Pin1, LOW);
  digitalWrite(r5, vel);

}

//Detiene el motor
void motorStop(int Pin1, int Pin2)
{
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
  digitalWrite(r5, vel);

}
