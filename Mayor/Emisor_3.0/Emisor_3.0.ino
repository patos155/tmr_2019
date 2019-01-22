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

int RngDs = 523;
int RngDi = 522;
int RngIs = 504;
int RngIi = 503;
int joyI = A4;
int joyD = A1;
int posI;
int posD;

void setup()
{
  Serial.begin(9600);
  delay(100);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openWritingPipe (addresses[0]);
}

void loop()
{
  posI = analogRead(joyI);
  posD = analogRead(joyD);
  // velocidades joystick derecho hacia atras
  if (posD > RngDi && posD <= 700)
  {
    data.valD = -1;
  }
  if (posD > 700 && posD <= 900)
  {
    data.valD = -2;
  }
  if (posD > 900)
  {
    data.valD = -3;
  }
  // velocidades joystick izquierdo hacia atras
  if (posI > RngIi && posI <= 700)
  {
    data.valI = -1;
  }
  if (posI > 700 && posI <= 900)
  {
    data.valI = -2;
  }
  if (posI > 900)
  {
    data.valI = -3;
  }
  // velocidades joystick derecho hacia adelante
  if (posD < RngDs && posD >= 300)
  {
    data.valD = 1;
  }
  if (posD < 300 && posD >= 100)
  {
    data.valD = 2;
  }
  if (posD < 100)
  {
    data.valD = 3;
  }
  // velocidades joystick izquierdo hacia adelante
  if (posI < RngIs && posI >= 300)
  {
    data.vali = 1;
  }
  if (posI < 300 && posI >= 100)
  {
    data.valI = 2;
  }
  if (posI < 100)
  {
    data.valI = 3;
  }
  //Posicion por defecto del joistick(motores detenidos)
  if ((posD == RngDi) || (posD == RngDs))
  {
    data.valD = 0;
  }
  if ((posI == RngIi) || (posI == RngIs))
  {
    data.valI = 0;
  }
  myRadio.write(&data, sizeof (data));
  Serial.print(data.valI);
  Serial.print("/");
  Serial.println(data.valD);
}
