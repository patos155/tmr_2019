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

