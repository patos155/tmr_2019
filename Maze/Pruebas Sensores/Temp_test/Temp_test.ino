/*-----------------------------------
 *            LIBRERIAS            *
-----------------------------------*/
#include <Wire.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_MLX90614.h>
extern "C" { 
  #include <utility/twi.h>
}


/*-----------------------------------
 *            SENSORES             *
-----------------------------------*/
/*  Temperatura infrarroja  */
const int TCA_dir = 0x70;
Adafruit_MLX90614 tempI = Adafruit_MLX90614();
Adafruit_MLX90614 tempD = Adafruit_MLX90614();


/*-----------------------------------
 *            VARIABLES            *
-----------------------------------*/

/*  Variables de temperatura  */
float ti_amb = 0;
float td_amb = 0;
float ti_obj = 0;
float td_obj = 0;


/*-----------------------------------
 *              SETUP              *
-----------------------------------*/
void setup() {
  Serial.begin(9600);

  /*  Infrarrojos de temperatura  */
  tcaselect(0);
  tempI.begin();
  tcaselect(1);
  tempD.begin();
}


/*-----------------------------------
 *              LOOP               *
-----------------------------------*/
void loop() {
  /*  Lecturas  */
  Leer();

  Imprimir();
  delay(800);
}


/*-----------------------------------
 *       FUNCIONES Y PROCESOS      *
-----------------------------------*/

void Leer(){
  tcaselect(0);
  ti_amb=tempI.readAmbientTempC();
  ti_obj=tempI.readObjectTempC();
  tcaselect(1);
  td_amb=tempD.readAmbientTempC();
  td_obj=tempD.readObjectTempC();
}

/*  Función para usar ambos sensores de temperatura infrarroja  */
void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCA_dir);
  Wire.write(1 << i);
  Wire.endTransmission();
}

void Imprimir(){
  Serial.println("\t--> IZQ <--");
  Serial.print("Temp. Amb: ");Serial.println(ti_amb);
  Serial.print("Temp. Obj: ");Serial.println(ti_obj);
  Serial.println("\t--> DER <--");
  Serial.print("Temp. Amb: ");Serial.println(td_amb);
  Serial.print("Temp. Obj: ");Serial.println(td_obj);
  Serial.println("=====================================================");
}

