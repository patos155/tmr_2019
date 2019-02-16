#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3F, 16, 2); //

struct package
{
  float temperatura;
  int gas1;
  int gas2;
  int gas3;
};

typedef struct package Package;
Package data;


int joystick = 0;
int pos = 0;
int valjoy = 0;
int com = 0;

int temp;

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00001
  radio.openReadingPipe(1, addresses[0]); // 00002
  radio.setPALevel(RF24_PA_MAX);
  // Inicializar el LCD
  lcd.init();
  //Encender la luz de fondo.
  lcd.backlight();
}

void loop() {
  //Valor obtenido del joystick
  valjoy = analogRead(joystick);

  //Posicion del joystick
  if (valjoy < 509) {
    pos = 1;
  }
  if (valjoy > 509) {
    pos = -1;
  }
  if (valjoy >= 500 && valjoy <= 515) {
    pos = 0;
  }
  //  Serial.println(pos);

  delay(5);
  radio.stopListening();
  radio.write(&pos, sizeof(pos));
  delay(5);
  radio.startListening();
  if (radio.available()) {

    while (radio.available()) {
      radio.read(&data, sizeof(data));
    }

    Serial.println(data.temperatura);
    Serial.println(data.gas1);
    Serial.println(data.gas2);
    Serial.println(data.gas3);

    if (com == 0) {
      lcd.clear();
    }
    com = 1;

    // Cursor en la primera posición de la primera fila
    lcd.setCursor(0, 0);
    lcd.print("Tmp:");
    lcd.print(data.temperatura);
    //    lcd.print("C"); // "337" -> "°"
    // Cursor en la 11° posición de la primera fila
    lcd.setCursor(9, 0);
    lcd.print("Gas 1:");
    lcd.print(data.gas1);//1 decimal
    lcd.print("  ");
    // Cursor en la primera posición de la 2° fila
    lcd.setCursor(0, 1);
    lcd.print("Gas 2:");
    lcd.print(data.gas2); //1 decimal
    lcd.print("  ");
    // Cursor en la 11° posición de la 2° fila
    lcd.setCursor(9, 1);
    lcd.print("Gas 3:");
    lcd.print(data.gas3);
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
