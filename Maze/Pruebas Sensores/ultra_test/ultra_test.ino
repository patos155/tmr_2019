/*  Ultrasónicos  */
const int trig_D = 33;
const int echo_D = 32;
const int trig_R = 53;
const int echo_R = 52;
const int trig_L = 27;
const int echo_L = 26;

/*  Distancia de paredes  */
const int p_d = 5;
const int p_l = 6;

/*  Variable de paredes  */
int adelante = 0;
int derecha = 0;
int izquierda = 0;

long D = 0;
long R = 0;
long L = 0;

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

void loop() {
  /*  Lecturas  */
  Leer();

  /*  Muestra de valores  */
  imprimir();

  /*  << Funcionamiento >>  */

  /*
      |       |     |       |
      |   1   |     |   1   |
      |0     0|     |0     1
      |       |     |       |
  */
  if( ((adelante==1) && (izquierda==0) && (derecha==0)) || ((adelante==1) && (izquierda==0) && (derecha==1)) ){
    //moverse(1,1);       //Moverse hacia adelante
  }

  /*
      |-------|
      |   0   |
      |0     1
      |       |
  */
  if( ((adelante==0) && (izquierda==0) && (derecha==1)) ){
    //giroD();
  }

  /*
      |-------|
      |   0   |
       1     0|
      |       |
  */
  if( ((adelante==0) && (izquierda==1) && (derecha==0)) ){
    //giroI();
  }

  /*
      |-------|
      |   0   |
       1     1
      |       |
  */
  if( ((adelante==0) && (izquierda==1) && (derecha==1)) ){
    //giroI();
  }

  /*     
         
          1   
       1     1
      |       |
  */
  if( ((adelante==1) && (izquierda==1) && (derecha==1)) ){
    //giroI();
  }

  /*
      |-------|
      |   0   |
      |0     0|
      |       |
  */
  if( ((adelante==0) && (izquierda==0) && (derecha==0)) ){
    //giroU();
  }

}

void Leer(){

  D = ultra(trig_D,echo_D);
  R = ultra(trig_R,echo_R);
  L = ultra(trig_L,echo_L);
  
  /*  Lectura de ultrasónicos y determinación de situación  */
  if(ultra(trig_D,echo_D)<p_d){
    adelante=0;
  }else{
    adelante=1;
  }

  if(ultra(trig_R,echo_R)<p_l){
    derecha=0;
  }else{
    derecha=1;
  }

  if(ultra(trig_L,echo_L)<p_l){
    izquierda=0;
  }else{
    izquierda=1;
  }
}

void imprimir(){
  Serial.print("Delante: ");Serial.println(D);
  Serial.print("Derecha: ");Serial.println(R);
  Serial.print("Izquierda: ");Serial.println(L);
  Serial.println("----------------------------------");

  delay(800);
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
