//https://sites.google.com/view/jumpinkit/nrf24-project?authuser=0

#include "RF24.h"
RF24 myRadio (7, 8); // in Mega can use> (48, 49);
byte addresses[][6] = {"0"};

struct package
{
  int valI;
  int valD;
};
typedef struct package Package;
Package data;

int joyI = 4;
int joyD = 1;
int posI;
int posD;

void setup()
{
  Serial.begin(9600);
  delay(100);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openWritingPipe( addresses[0]);
  //delay(1000);
}

void loop()
{
  posI = analogRead(joyI);
  posD = analogRead(joyD);
  if (posI > 522) {
    data.valI  = 1;
  }
  if (posD > 504) {
    data.valD = 1;
  }
  if (posI < 521) {
    data.valI = -1;
  }
  if (posD < 503) {
    data.valD = -1;
  }
  if ((posI == 522) || (posI == 521)) {
    data.valI = 0;
  }
  if ((posD == 503) || (posD == 504)) {
    data.valD = 0;
  }

//  if (myRadio.available()) {
//    Serial.println("Comunicacion disponible");
//    //    myRadio.write(&data, sizeof(data));
//  }
//  else {
//    Serial.println("Error en la comunicacion");
//  }
  myRadio.write(&data, sizeof(data));
  Serial.print(data.valI);
  Serial.print("/");
  Serial.println(data.valD);
  /*if (!myRadio.write(&data, sizeof(data)))
    {
    Serial.print(data.val1);
    Serial.println(data.val2);
    Serial.println("Error al enviar");

    }
    else
    {

    //data[32] = Serial.read();




    Serial.print(data.val1);
    Serial.println(data.val2);
    Serial.println("Transmitiendo...");
    //Serial.println(" > " + rAddress_[0]);
    //delay(1000);
    }*/


  //  myRadio.write(&data, sizeof(data));
  /* Serial.print("\nPackage:");
    Serial.print(data.id);
    Serial.print("\n");
    Serial.println(data.temperature);
    Serial.println(data.text);
    data.id = data.id + 1;
    data.temperature = data.temperature + 0.1;*/
  //delay(50);
}
















/*
  #include <SPI.h>
  #include <RF24.h>
  #include <nRF24L01.h>

  const int pinCE = 7;
  const int pinCSN = 8;
  int PinIN1 = 5;
  int PinIN2 = 6;

  RF24 radio(pinCE, pinCSN);

  #define WHICH_NODE 1

  const uint64_t wAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };
  String wAddress_[] = {"0x7878787878LL", "0xB3B4B5B6F1LL", "0xB3B4B5B6CDLL", "0xB3B4B5B6A3LL", "0xB3B4B5B60FLL", "0xB3B4B5B605LL" };

  //char dataRead[32];
  int dataRead;

  void setup()
  {
   Serial.begin(115200);

   radio.begin();
   radio.setPALevel(RF24_PA_MAX);
   radio.setDataRate(RF24_250KBPS);
   radio.setChannel(100);

   radio.openReadingPipe(1, wAddress[0]);
   radio.startListening();
   pinMode(PinIN1, OUTPUT);
   pinMode(PinIN2, OUTPUT);
  }

  void loop()
  {
  if(radio.available())
  {
    if(radio.available())
    {
      radio.read(&dataRead, sizeof(dataRead));
      Serial.println(dataRead);
      //Serial.println(" < " + wAddress_[0]);
    if(dataRead > 515 ){
      MotorHorario();
    }
    if(dataRead < 513 ){
      MotorAntihorario();
    }
    if((dataRead <= 515)  && (dataRead >= 513) ){
      MotorStop();
    }



    }

  }
  else
  {
    //Serial.println("Dispositivo no encontrado");
  }
  }

  void MotorHorario()
  {
  digitalWrite (PinIN1, HIGH);
  digitalWrite (PinIN2, LOW);

  }
  void MotorAntihorario()
  {
  digitalWrite (PinIN1, LOW);
  digitalWrite (PinIN2, HIGH);
  }

  void MotorStop()
  {
  digitalWrite (PinIN1, LOW);
  digitalWrite (PinIN2, LOW);
  }

*/
