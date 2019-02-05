/*-----------------------------------
 *            SENSORES             *
-----------------------------------*/
/*  infrarrojos  */
const int infra_L = A11;
const int infra_R = A12;


/*-----------------------------------
 *            VARIABLES            *
-----------------------------------*/
/*  Variables de infrarrojos  */
int inf_L = 0;
int inf_R = 0;


/*-----------------------------------
 *              SETUP              *
-----------------------------------*/
void setup() {
  Serial.begin(9600);
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
  inf_L = analogRead(infra_L);
  inf_R = analogRead(infra_R);
}

void Imprimir(){
  Serial.print("Infra. Izq: ");Serial.println(inf_L);
  Serial.print("Infra. Der: ");Serial.println(inf_R);
  Serial.println("=====================================================");
}

