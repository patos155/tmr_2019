#include "RF24.h"
RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};
struct package
{
  int valI;
  int valD;
};
typedef struct package Package;
Package data;

int PinIN1 = 4;
int PinIN2 = 2;
int PinIN3 = 5;
int PinIN4 = 6;
int ENA = 9;
int ENB = 10;
int lento = 100;
int medio = 150;
int rapido = 225;

void setup() {
  Serial.begin (9600);
  delay(100);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}

void loop() {

  if (myRadio.available())
  {
    while (myRadio.available())
    {
      myRadio.read(&data, sizeof(data));
      Serial.print(data.valI);
      Serial.print("/");
      Serial.println(data.valD);
    }
    if (data.valI >= 0)
    {
      switch (data.valI)
      {
        case 0: motorStop(PinIN1, PinIN2, ENA, 0); break;
        case 1: motorHorario(PinIN1, PinIN2, ENA, lento); break;
        case 2: motorHorario(PinIN1, PinIN2, ENA, medio); break;
        case 3: motorHorario(PinIN1, PinIN2, ENA, rapido); break;
      }
    }
    else
    {
      switch (data.valI)
      {
        case -1: motorAntihorario(PinIN1, PinIN2, ENA, lento); break;
        case -2: motorAntihorario(PinIN1, PinIN2, ENA, medio); break;
        case -3: motorAntihorario(PinIN1, PinIN2, ENA, rapido); break;
      }
    }
    if (data.valD >= 0)
    {
      switch (data.valD)
      {
        case 0: motorStop(PinIN3, PinIN4, ENB, 0); break;
        case 1: motorHorario(PinIN3, PinIN4, ENB, lento); break;
        case 2: motorHorario(PinIN3, PinIN4, ENB, medio); break;
        case 3: motorHorario(PinIN3, PinIN4, ENB, rapido); break;
      }
    }
    else
    {
      switch (data.valD)
      {
        case -1: motorAntihorario(PinIN3, PinIN4, ENB, lento); break;
        case -2: motorAntihorario(PinIN3, PinIN4, ENB, medio); break;
        case -3: motorAntihorario(PinIN3, PinIN4, ENB, rapido); break;
      }
    }
  }
  else
  {
    Serial.println("Radio no disponible");
  }
}

void motorHorario(int Pin1, int Pin2, int Pin3, int vel)
{
  digitalWrite(Pin1, HIGH);
  digitalWrite(Pin2, LOW);
  analogWrite(Pin3, vel);

}
void motorAntihorario(int Pin1, int Pin2, int Pin3, int vel)
{
  digitalWrite(Pin2, HIGH);
  digitalWrite(Pin1, LOW);
  analogWrite(Pin3, vel);

}
void motorStop(int Pin1, int Pin2, int Pin3, int vel)
{
  digitalWrite(Pin1, LOW);
  digitalWrite(Pin2, LOW);
  analogWrite(Pin3, vel);

}
