#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Servo myServo;

struct package
{
  int temperatura = 30;
  int gas1;
  int gas2;
};

typedef struct package Package;
Package data;

int pos = 0;
int pin_mq = 2;
int temp = 30;

//boolean mq_estado;

void setup() {
  Serial.begin(9600);
  myServo.attach(3);
  pinMode(pin_mq, INPUT);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
  radio.setPALevel(RF24_PA_MAX);
}

void loop() {
  data.temperatura = 30;
  data.gas1 = digitalRead(pin_mq);
  data.gas2 = digitalRead(pin_mq);
  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {

      radio.read(&pos, sizeof(pos));
      if (pos == 0) {
        myServo.write(90);
      }
      if (pos == 1) {
        myServo.write(180);
      }
      if (pos == -1) {
        myServo.write(0);
      }
    }
    //    Serial.println(0);
    delay(5);
    radio.stopListening();
    radio.write(&data, sizeof(data));
    Serial.println(data.temperatura);
    Serial.println(data.gas1);
    Serial.println(data.gas2);
  } else {
    Serial.println("Radio no disponible");
  }
}
