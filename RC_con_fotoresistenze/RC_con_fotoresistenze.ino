/*
  Questo programma serve per controllare un servo RC di 180 gradi che funge
  da sterzo tramite due fotoresistenze
  
  Può "seguire" buio o luce a dipendenza della posizione delle resistenze
  
  L'arduino viene montato su un'automobile telecomandata che, anziché ricevere 
  i segnali dal telecomando, riceve impulsi e segnali direlttamente 
  dall'arduino.

*/

//definisco la lunghezza massima del periodo T (per ulteriore comprensione
//guardare lo schema alla fne del programma)
#define T 20000  

//definisco un intervallo da 0 a 1023 (ovvero i valori letti dai pin A0 e A1)
#define R1MAX 0
#define R1MIN 1023

//definisco un intervallo da 1500 a 500 (ovvero un intervallo di sterzo da 0
//  90 gradi)
#define R2MAX 1500
#define R2MIN 500

//definisco un intervallo da 1500 a 2000 (ovvero un intervallo si sterzo da
//90 a 180 gradi)
#define R3MIN 1500
#define R3MAX 2000

//definisco un valore standard da utilizzare nel caso in cui la macchinina deve
//procedere in linea retta
#define GRADI90 1500

//definisco i pin delle due fotoresistenze
#define PIN_FOTORESISTENZA1 A0
#define PIN_FOTORESISTENZA2 A1

//definisco il numero del pin del servo RC
#define PIN_RC 9

/*definisco delle variabili float che comprendono:

  valore_comprato_float: rappresenta il valore letto sul pin delle 
                       fotoresistenze che verrà comparato

  t1:                     rappresenta il valore della lunghezza del periodo
                          t1 (per ulteriore comprensione guardare lo schema alla
                          fine del programma)

  foto_1:                 qui verranno "salvati" i valori letti sulla prima
                          fotoresistenza

  foto_2:                 qui verranno "salvati" i valori letti sulla seconda
                          fotoresistenza

  lmin:                   è il valore minimo del intervallo della comparazione

  lmax:                   è il valore massimo del intervallo della comparazione

*/

float valore_comparato_float, t1, foto_1, foto_2, lmin, lmax;

//scrivo una funzione che compara dei valori (questa funzione equivale alla 
//funzione map)
float floatmap(float valore_mappato, float r1min, float r1max, float r2min, float r2max) {
  return (((r2max-r2min)*(valore_mappato-r1min))/(r1max-r1min))+r2min;
}


void setup() {
  Serial.begin(9600);

  //definisco quali pin sono degli INPUT e quali degli  OUTPUT
  pinMode(PIN_FOTORESISTENZA1, INPUT);
  pinMode(PIN_FOTORESISTENZA2, INPUT);
  pinMode(PIN_RC, OUTPUT);

  //definisco i valori iniziali delle vaiabili
  valore_comparato_float = 0;
  foto_1 = 0;
  foto_2 = 0;
}

void loop() {

  //assegno i valori corretti alle variabili foto_1 e foto_2
  foto_1 = analogRead(PIN_FOTORESISTENZA1);
  foto_2 = analogRead(PIN_FOTORESISTENZA2);

  if (foto_1 > foto_2) {

    //foto_1 - foto_2 o foto_2 - foto_1 sono un delta e saranno questi a venire
    //comparati
    valore_comparato_float = foto_1-foto_2; 
    lmin = R2MIN;                          
    lmax = R2MAX;
  } else if (foto_2 > foto_1) {
    valore_comparato_float = foto_2-foto_1;
    lmin = R3MIN;
    lmax = R3MAX;
  } else {
    t1 = GRADI90;
  }
  
  t1 = floatmap(valore_comparato_float, R1MIN, R1MAX, lmin, lmax);

  //utilizzo un sistema bloccante per generare un onda quadra in grado di
  //pilotare correttaemnte il servo RC
  digitalWrite(PIN_RC, HIGH);
  delayMicroseconds(t1);
  digitalWrite(PIN_RC, LOW);
  delayMicroseconds((T-t1));

/*
  Debug:
  Serial.println(t1);
*/

}

/*

Duty cycle:

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


   Schema fotoresistenze:

  +5V ____ _________________________
          |                         | 
          |                         |
          |                         |
         | |  R1                   | |  R2
         | |                       | |
          |                         |
          |______                   |______ 
          |      |                  |      |
          |      |                  |      |
         (F)1    |                  (F)2   |
          |     PIN_FOTORESITENZA1  |     PIN_FOTORESITENZA2
          |                         |
          |                         |
  GND_____|_________________________|


Schema servo RC:

PIN_RC __  _________ +5V
         ||
         ||
         ||
       __||__
      |      |
      |      |
      |      |
      |      |
      | (   )------
      |______|
          |
          |
   GND____|


Angolazioni del servo RC a 180 gradi:

PIN_RC __  _________ +5V          PIN_RC __  _________ +5V
         ||                                ||
         ||                                ||
         ||                                ||
       __||__                            __||__
      |      |                          |      |
      |      |                          |      |
      |      |                          |   |  |
      |      |                          |   |  |
      | (   )------                     | (   )|
      |______|                          |______|
          |                                 |                                
          |                                 | 
          |                                 | 
   GND____|    180                   GND____|    90


   PIN_RC  ___________ +5V
         ||
         ||
         ||
       __||__
      |      |
      |      |
      |      |
      |      |
 ------(   ) |
      |______|
          |
          |
   GND____|    0

*/



