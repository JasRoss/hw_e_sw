/*Programma bloccante che serve per comandare un servo RC in grado di ruotare 
  180 gradi
  Può solamente essere a 0, a 45, a 90, a 135 o a 180 gradi e varia in base al
  valore letto sul potenziometro
*/

#define T 20000               //definisco la lunghzza massima del periodo
#define TOLLERANZA_0_5 205    //definisco le varie tolleranze per il valore del
#define TOLLERANZA_1_0 410    //potenziometro
#define TOLLERANZA_1_5 515    //ogni determinato valore viene impiegato per 
#define TOLLERANZA_2_0 620    //capire quale valore di tempo assegnare a t1

#define PIN_POTENZIOMETRO A0  //definisco i pin del potenziometro e del servo
#define PIN_SERVO_RC      2

float valore_potenziometro, t1;

void setup() {
  pinMode(PIN_POTENZIOMETRO, INPUT);
  pinMode(PIN_SERVO_RC, OUTPUT);

  valore_potenziometro = 0;

  //imposto un valore iniziale al servomotore, che sara impostato a 90 gradi
  t1 = 1500;                 
}

void loop() {
  //programma bloccante
  digitalWrite(PIN_SERVO_RC, HIGH);
  delayMicroseconds(t1);
  digitalWrite(PIN_SERVO_RC, LOW);
  delayMicroseconds((T-t1));

  valore_potenziometro = analogRead(PIN_POTENZIOMETRO);
  
  //viene assegnato il giusto valore a t1 in base al valore del potenziometro
  if(valore_potenziometro <= TOLLERANZA_0_5) {
    t1 = 500;
  } else if (valore_potenziometro <= TOLLERANZA_1_0) {  
    t1 = 1000;
  } else if (valore_potenziometro <= TOLLERANZA_1_5) {
    t1 = 1500;
  }  else if (valore_potenziometro <= TOLLERANZA_2_0) {
    t1 = 2000;
  } else {
    t1 = 2500;
  }
}


/*
      t1
   0.5-2.5ms 
    |-----|
     _____               _____               _____
    |     |             |     |             |     |
    |     |             |     |             |     |
    |     |             |     |             |     |
    |     |_____________|     |_____________|     |_____________

    |-------------------|
              20ms
               T
*/
