//https://sites.google.com/view/jumpinkit/nrf24-project?authuser=0
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_MLX90614.h>

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

struct packageE
{
  float temperatura;
  int gas1;
  int gas2;
  int gas3;
  //  int gas4;
};

struct packageR
{
  int valX;
  int valY;
  int valbtnI;
  int valbtnD;
};

typedef struct packageR PackageR;
typedef struct packageE PackageE;
PackageR dataR;
PackageE dataE;

//int pos = 0;
int sensorg1 = 5;
int sensorg2 = 4;
int sensorg3 = 3;
int sensorg4 = 2;
int gas4;

int PinIN1 = 32;
int PinIN2 = 33;
int PinIN3 = 35;
int PinIN4 = 34;
int PinIN3B = 31;
int PinIN4B = 30;

long TiempoMiliseg;
long tiempo;
int led1 = 9;
int led2 = 10;
int led3 = 11;

float ambiente;

void setup() {
  Serial.begin(9600);
  mlx.begin();
  pinMode(sensorg1, INPUT);
  pinMode(sensorg2, INPUT);
  pinMode(sensorg3, INPUT);
  pinMode(sensorg4, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MAX);
}

void loop() {
  dataE.gas1 = digitalRead(sensorg1);
  dataE.gas2 = digitalRead(sensorg2);
  dataE.gas3 = digitalRead(sensorg3);
  gas4 = digitalRead(sensorg4);
  ambiente = mlx.readAmbientTempC();
  dataE.temperatura = mlx.readObjectTempC();

  if (dataE.gas1 == 0 ||  dataE.gas2 == 0) {
    digitalWrite(led1, HIGH);
  }else{
    digitalWrite(led1, LOW);
  }

  if (dataE.gas3 == 0 || gas4 == 0) {
    digitalWrite(led2, HIGH);
  }else{
    digitalWrite(led2, LOW);
  }

  if ((dataE.temperatura - ambiente) >= 10.00) {
    digitalWrite(led3, HIGH);
  }else{
    digitalWrite(led3, LOW);
  }

  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {

      radio.read(&dataR, sizeof(dataR));

      Serial.println(dataR.valX);
      Serial.println(dataR.valY);
      Serial.println(dataR.valbtnI);
      Serial.println(dataR.valbtnD);

      //controla un motor la direccion con el eje x del joystick
      switch (dataR.valX) {
        case 0: MotorStop(PinIN1, PinIN2); break;
        case 1: MotorHorario(PinIN1, PinIN2); break;
        case -1: MotorAntihorario(PinIN1, PinIN2); break;
      }

      //controla un motor la direccion con el eje y del joystick
      switch (dataR.valY) {
        case 0: MotorStop(PinIN3, PinIN4); break;
        case 1: MotorHorario(PinIN3, PinIN4); break;
        case -1: MotorAntihorario(PinIN3, PinIN4); break;
      }

      //controla un motor la direccion con los valores de los push buttons
      if (dataR.valbtnI == 0 && dataR.valbtnD == 1) {
        MotorHorario(PinIN3B, PinIN4B);
      }
      if (dataR.valbtnI == 1 && dataR.valbtnD == 0) {
        MotorAntihorario(PinIN3B, PinIN4B);
      }
      if ((dataR.valbtnI == 0 && dataR.valbtnD == 0) || (dataR.valbtnI == 1 && dataR.valbtnD == 1)) {
        MotorStop(PinIN3B, PinIN4B);
      }

    }
    delay(5);
    radio.stopListening();
    radio.write(&dataE, sizeof(dataE));
    //    Serial.println(dataE.temperatura);
    //    Serial.println(dataE.gas1);
    //    Serial.println(dataE.gas2);
    //    Serial.println(dataE.gas3);
    //    Serial.println(dataE.gas4);
    TiempoMiliseg = 0;
    tiempo = 0;

  } else {
    if (tiempo == 0) {
      tiempo = millis();
    }

    TiempoMiliseg = millis();
    Serial.println(TiempoMiliseg - tiempo);
    if ((TiempoMiliseg - tiempo) > 1000) {
      MotorStop(PinIN1, PinIN1);
      MotorStop(PinIN3, PinIN4);
      MotorStop(PinIN3B, PinIN4B);
      Serial.println("Motores detenidos");
    }
    Serial.println("Radio no disponible");
  }
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
