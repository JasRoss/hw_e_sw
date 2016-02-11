
/* Questo programma funziona come un cronometro
   Si possono prendere solo due tempi, ma si possono facilmente aggiungerne
   altri nel programma
   Il funzionamento è molto semplice: oscurando la fotoresistenza (regolandone
   la sensibitià tramite un potenziometro) si "prende" il primo tempo,
   oscurandola una seconda volta si "prende" il secondo e una terza
   oscurazione azzera tutti i risultati
   Questo programma funziona solo con i secondi, ma si può facilmente cambiarli
   con millisecondi o altro
*/

#include <LiquidCrystal.h>

//definisco i numeri dei pin e le tolleranze
//definisco il pin del sensore
#define PIN_SENSORE A0       
//i sei pin seguenti servono unicamente per far funzionare il display
#define PIN_RS 2              
#define PIN_E 3

#define PIN_BUS4 4
#define PIN_BUS5 5
#define PIN_BUS6 6
#define PIN_BUS7 7
//definicso una tolleranza o un valore standard per la fotoresistenza
#define TOLLERANZA 700

//credo quattro diverse variabili tempo1, tempo2, tempo_attuale e
//bottone_premuto
//le prime tre servono per mostrare sul display i tempi mentre l'ultima
//serve per sapere quante volte è stato oscurata la fotoresistenza
int tempo1, tempo2, tempo_attuale, bottone_premuto;

LiquidCrystal schermo(PIN_RS, PIN_E, PIN_BUS4, PIN_BUS5, PIN_BUS6, PIN_BUS7);

void setup() {
  // ...
  Serial.begin(9600);

  schermo.begin(16, 2);

  pinMode(PIN_SENSORE, INPUT);

  tempo1 = 0;
  tempo2 = 0;
  tempo_attuale = 0;
  bottone_premuto = 0;
}

void loop() {
  // ...
  Serial.println(analogRead(PIN_SENSORE));
  
  if (bottone_premuto == 6) {
  	tempo_attuale = 0;
  	tempo1 = 0;
  	tempo2 = 0;
  	bottone_premuto = 0;
  } else {
  	if ((analogRead(PIN_SENSORE)) > TOLLERANZA) {
      bottone_premuto ++;

  	  while((analogRead(PIN_SENSORE)) > TOLLERANZA);
    }
      if(bottone_premuto == 2) {
        tempo1 = tempo_attuale;
        bottone_premuto = 3;
      } else if(bottone_premuto == 4) {
        tempo2 = tempo_attuale;
        bottone_premuto = 5;
      } 
    
    tempo_attuale ++;
	}
  //debug	
  Serial.print("Tempo: ");
  Serial.println(tempo_attuale);
  Serial.print("1: ");
  Serial.println(tempo1);
  Serial.print("2: ");
  Serial.println(tempo2);
  //display
  schermo.clear();
  schermo.print("Tempo: ");
  schermo.print(tempo_attuale);

  schermo.setCursor(0, 1);
  schermo.print("T1: ");
  schermo.print(tempo1);
  schermo.print(" T2: ");
  schermo.print(tempo2);  
  
  delay(1000); 
}
