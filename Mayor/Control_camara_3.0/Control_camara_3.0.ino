#include "RF24.h"
#include <LiquidCrystal_I2C.h>

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3F, 16, 2); //

struct packageR
{
  float temperatura;
  int gas1;
  int gas2;
  int gas3;
  int gas4;
};

struct packageE
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

int btnI = 6;
int btnD = 5;
int ejeX = 0;
int ejeY = 1;
int posX;
int posY;
int valY = 0;
int com = 0;

//int temp;

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MAX);
  // Inicializar el LCD
  lcd.init();
  //Encender la luz de fondo.
  lcd.backlight();
  pinMode(btnI, INPUT_PULLUP);
  pinMode(btnD, INPUT_PULLUP);
}

void loop() {
  //Valor obtenido del joystick
  posX = analogRead(ejeX);
  posY = analogRead(ejeY);
  dataE.valbtnI = digitalRead(btnI);
  dataE.valbtnD = digitalRead(btnI);
  //Posicion del joystick en el eje X
  if (posX < 600) {
    dataE.valX = 1;
  }
  if (posX > 200) {
    dataE.valX = -1;
  }
  if (posX >= 200 && posX <= 600) {
    dataE.valX = 0;
  }
  //Posicion del joystick en el eje Y
  if (posY < 600) {
    dataE.valY = 1;
  }
  if (posY > 200) {
    dataE.valY = -1;
  }
  if (posY >= 200 && posY <= 600) {
    dataE.valY = 0;
  }

  delay(5);
  radio.stopListening();
  radio.write(&dataE, sizeof(dataE));
  delay(5);
  radio.startListening();
  if (radio.available()) {

    while (radio.available()) {
      radio.read(&dataR, sizeof(dataR));
    }

    Serial.println(dataR.temperatura);
    Serial.println(dataR.gas1);
    Serial.println(dataR.gas2);
    Serial.println(dataR.gas3);
    Serial.println(dataR.gas4);

    if (com == 0) {
      lcd.clear();
    }
    com = 1;

    // Cursor en la primera posición de la primera fila
    lcd.setCursor(0, 0);
    lcd.print("Tmp:");
    lcd.print(dataR.temperatura);
    //    lcd.print("C"); // "337" -> "°"
    // Cursor en la 11° posición de la primera fila
    lcd.setCursor(9, 0);
    lcd.print("Gas 1:");
    lcd.print(dataR.gas1);//1 decimal
    lcd.print("  ");
    // Cursor en la primera posición de la 2° fila
    lcd.setCursor(0, 1);
    lcd.print("Gas 2:");
    lcd.print(dataR.gas2); //1 decimal
    lcd.print("  ");
    // Cursor en la 11° posición de la 2° fila
    lcd.setCursor(9, 1);
    lcd.print("Gas 3:");
    lcd.print(dataR.gas3);
    //    lcd.print("  ");
  } else {
    if (com == 1) {
      lcd.clear();
    }
    com = 0;
    Serial.println("Radio no disponible");
    lcd.setCursor(0, 0);
    lcd.print("No disponible");
  }

}
