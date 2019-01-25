/*-----------------------------------
 *            LIBRERIAS            *
-----------------------------------*/
#include <SPI.h>
#include <SD.h>


/*-----------------------------------
 *            SENSORES             *
-----------------------------------*/
/*  SD  */
File archivo;
const int pinSD=46;


/*-----------------------------------
 *              SETUP              *
-----------------------------------*/
void setup() {
  /*  SD  */
  SD.begin(pinSD);
  archivo = SD.open("Test_SD.txt",FILE_WRITE);
  archivo.write("\n=======================================================================================\n");
  archivo.close();

  for(int i=1;i<=15;i++){
    grabar(i);
  }

}


/*-----------------------------------
 *              LOOP               *
-----------------------------------*/
void loop() {
  
}


/*-----------------------------------------
 *       FUNCIONES Y PROCEDIMIENTOS      *
-----------------------------------------*/
void grabar(int cont){
  archivo = SD.open("Test_SD.txt",FILE_WRITE);
  archivo.write("Linea ");
  archivo.println(cont);
  archivo.close();
}
