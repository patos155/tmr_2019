/*-----------------------------------
 *            SENSORES             *
-----------------------------------*/
/*  Ultrasónicos  */
const int trig_D = 33;
const int echo_D = 32;
const int trig_R = 41;
const int echo_R = 40;
const int trig_L = 27;
const int echo_L = 26;


/*-----------------------------------
 *            VARIABLES            *
-----------------------------------*/
long D = 0;
long R = 0;
long L = 0;


/*-----------------------------------
 *              SETUP              *
-----------------------------------*/
void setup() {
  Serial.begin(9600);
  
  /*  Ultrasónicos  */
  pinMode(trig_D, OUTPUT);    //Delantero
  pinMode(echo_D, INPUT);
  digitalWrite(trig_D,LOW);
  pinMode(trig_R, OUTPUT);    //Derecho
  pinMode(echo_R, INPUT);
  digitalWrite(trig_R,LOW);
  pinMode(trig_L, OUTPUT);    //Izquierdo
  pinMode(echo_L, INPUT);
  digitalWrite(trig_L,LOW);
}


/*-----------------------------------
 *              LOOP               *
-----------------------------------*/
void loop() {
  /*  Lecturas  */
  Leer();

  /*  Muestra de valores  */
  imprimir();
  delay(800);
  
}


/*-----------------------------------------
 *       FUNCIONES Y PROCEDIMIENTOS      *
-----------------------------------------*/
void Leer(){
  D = ultra(trig_D,echo_D);
  R = ultra(trig_R,echo_R);
  L = ultra(trig_L,echo_L);
}

void imprimir(){
  Serial.print("Delante: ");Serial.println(D);
  Serial.print("Derecha: ");Serial.println(R);
  Serial.print("Izquierda: ");Serial.println(L);
  Serial.println("----------------------------------");
}

/*  Función para lectura de ultrasónicos  */
long ultra(int trigPin,int echoPin){
  long t=0;
  long d=0;

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  t=pulseIn(echoPin,HIGH);
  d = t/59;

  return d;
}
