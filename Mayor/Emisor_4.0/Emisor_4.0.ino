#include "RF24.h"
RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};

struct package
{
  int valI;
  int valD;
  int valbtn;
};
typedef struct package Package;
Package data;

int RngDs = 521;
int RngDi = 522;
int RngIs = 502;
int RngIi = 503;
int joyI = A4;
int joyD = A1;
int posI;
int posD;
int btn = 6;
int led = 5;
void setup()
{
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
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
  data.valbtn = digitalRead(btn);
  if (data.valbtn == 1){
    digitalWrite (led, HIGH);
    }
    else{
      digitalWrite(led, LOW);
      }
  // velocidades joystick derecho hacia atras
  if (posD > RngDi)
  {
    data.valD = -1;
  }
  // velocidades joystick izquierdo hacia atras
  if (posI > RngIi )
  {
    data.valI = -1;
  }
  // velocidades joystick derecho hacia adelante
  if (posD < RngDs)
  {
    data.valD = 1;
  }
  // velocidades joystick izquierdo hacia adelante
  if (posI < RngIs)
  {
    data.valI = 1;
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
  Serial.println(digitalRead(data.valbtn));
}
