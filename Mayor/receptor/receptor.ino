#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 

const int pinCE = 7; 
const int pinCSN = 8; 
RF24 radio(pinCE, pinCSN); 


const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };
String rAddress_[] = {"0x7878787878LL", "0xB3B4B5B6F1LL", "0xB3B4B5B6CDLL", "0xB3B4B5B6A3LL", "0xB3B4B5B60FLL", "0xB3B4B5B605LL" };

//char data[32] = "Datos del invernadero"; 
//char data[32];
int joyX = 0;
int joyY = 1;
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
    data = analogRead(joyY);
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
}
