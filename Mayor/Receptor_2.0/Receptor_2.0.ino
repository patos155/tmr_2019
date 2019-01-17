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

int PinIN1 = 5;
int PinIN2 = 6;
int PinIN3 = 3;
int PinIN4 = 4;
//int ENA = 3;
//int ENB = 3;


void setup()
{
  Serial.begin(9600);
  delay(100);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  //  pinMode (ENA, OUTPUT);
  //  pinMode (IN1, OUTPUT);
  //  pinMode (IN2, OUTPUT);
  //  pinMode (ENB, OUTPUT);
  //  pinMode (IN3, OUTPUT);
  //  pinMode (IN4, OUTPUT);

}

void loop()
{
  if ( myRadio.available())
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
      Serial.print(data.valI);
      Serial.print("/");
      Serial.println(data.valD);
    }

    if (data.valI > 0 ) {
      MotorHorario(PinIN1, PinIN2);
    }
    if (data.valD > 0 ) {
      MotorHorario(PinIN3, PinIN4);
    }
    if (data.valI < 0 ) {
      MotorAntihorario(PinIN1, PinIN2);
    }
    if (data.valD < 0 ) {
      MotorAntihorario(PinIN3, PinIN4);
    }
    if (data.valI == 0) {
      MotorStop(PinIN1, PinIN2);
    }
    if (data.valD == 0 ) {
      MotorStop(PinIN3, PinIN4);
    }

    /*if((data.val1 <= 515)  && (data.val1 >= 513) ){
      MotorStop(PinIN1, PinIN2);
      }
      if((data.val2 <= 515)  && (data.val2 >= 513) ){

      }*/
  } else {
    Serial.println("Radio no disponible");
  }
  //delay(1000);

}


void MotorHorario(int Pin1, int Pin2)
{
  digitalWrite (Pin1, HIGH);
  digitalWrite (Pin2, LOW);

}
void MotorAntihorario(int Pin1, int Pin2)
{
  digitalWrite (Pin1, LOW);
  digitalWrite (Pin2, HIGH);
}

void MotorStop(int Pin1, int Pin2)
{
  digitalWrite (Pin1, LOW);
  digitalWrite (Pin2, LOW);
}





















/*#include <SPI.h>
  #include <nRF24L01.h>
  #include <RF24.h>

  const int pinCE = 7;
  const int pinCSN = 8;
  RF24 radio(pinCE, pinCSN);


  const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };
  String rAddress_[] = {"0x7878787878LL", "0xB3B4B5B6F1LL", "0xB3B4B5B6CDLL", "0xB3B4B5B6A3LL", "0xB3B4B5B60FLL", "0xB3B4B5B605LL" };

  //char data[32] = "Datos del invernadero";
  //char data[32];
  //int joyX = 0;
  //int joyY = 1;
  int joy1 = 1;
  int joy2 = 3;

  int data=3;
  String d;
  void setup()
  {

  Serial.begin(115200);
  radio.begin();

  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(100);

  // Open up to six pipes for PRX to receive data
  radio.openWritingPipe(rAddress[0]);
  }

  void loop()
  {
  //if (Serial.available() > 0) { // read first available byte into a variable}
    //data[32] = Serial.read();
    //char dir = Serial.read();
    //data = analogRead(joyY);
    val1 = analogRead(joy1);
    val2 = analogRead(joy2);
    int data = [val1, val2];
  //   d.valueOf(data);

    if(!radio.write(&data, sizeof(data)))
    {
      Serial.println(data);
      Serial.println("Error al enviar");

    }
    else
    {

       //data[32] = Serial.read();


      Serial.print(data);
      Serial.println(" > " + rAddress_[0]);
      //delay(1000);
    }
    //}
  }*/
