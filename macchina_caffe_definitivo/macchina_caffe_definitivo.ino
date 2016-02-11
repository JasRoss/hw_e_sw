/* Questo programma funziona come una macchinetta per preparare bevande, in questo caso si può scegliere tra caffe e the.
   Ci sono due tasti per la scelta della bevanda, quattro che simulano l'entrata dei soldi (accettate monete da 1Fr.,50ct.,20ct. e 10ct.)
   e uno per il resto.
   Inoltre c'è un led RGB che indica lo stato della preparazione (Blu), se il credito non è sufficente (Rosso) o se lo è (Verde).
   Per ultino ci sono due piccoli led che indicano la bevanda scelta.
   Per migliori comprensioni in contemporanea al'arduino è consigliato l'utilizzo del monitor seriale.

       Tabella degli stati
       (Ogni stato esegue un'operazione diversa)

       Stato   Operazione

        0       Mostra scritta iniziale:
                Il messaggio di benvenuto sarà alternato con uno
                che spiega come vedere i prezzi.
                Il messaggio cambia un tempo definito in 
                precedenza.

                
        1       Cambia ligua:
                Premendo il pulsante dedicato la lingua varierà
                da italiano a inglese o viceversa.


        2       Procedimento:
                Si controlla se il credito a disposizione
                è sufficente per l'acquisto della bevanda scelta.
                Se mancano monete il programma andrà allo stato
                numero 5,ovvero allo stato "mancanza credito", 
                se ce ne sono a sufficenza si procede e si prepara
                la bevanda.

        3       Mancanza credito:
                Appare sullo schermo una scritta che avvisa il cliente
                che manca credito e poi specifica quanto bisogna ancora
                inserire.
                Per attirare l'attenzione del cliente lampeggerà un
                led RGB rosso.                          

        4       Resto:
                Viene calcolato il resto e mostrato a video quanto 
                ammonta, dicendo al cliente che è possibile ritirlarlo.

        5       TIMEOUT PREZZI:
                Controlla da quanto tempo non si stanno
                premendo bottoni dopo la visione dei 
                prezzi.
                Se il tempo è maggiore rispetto a un valore 
                definito in precedenza il programma ritornerà
                alla situazione del primo stato ("mostra scritta
                iniziale").
                
        6       TIMEOUT MONETA:
                Controlla da quanto tempo non si stanno
                premendo bottoni dopo aver inserito la moneta.
                Se il tempo è maggiore rispetto a un valore 
                definito in precedenza il programma controlla
                il valore del conto.
                Se il conto è maggiore di 0 andrà allo
                stato numero 6, cioé allo stato "resto",
                mentre se è pari a 0 il programma ritornerà
                al primo stato ("mostra scritta iniziale").                             


       Tabella dei pin

       N° sull'arduino:        Gruppo:       Numero in codice:        Utilizzo:              Osservazioni:

             22                   A             0b00000001            Tasto caffe                INPUT
             23                   A             0b00000010            Tasto the                  INPUT
             24                   A             0b00000100            Tasto 1Fr.                 INPUT
             25                   A             0b00001000            Tasto 50ct.                INPUT
             26                   A             0b00010000            Tasto 20ct.                INPUT
             27                   A             0b00100000            Tasto 10ct.                INPUT
             28                   A             0b01000000            Tasto Resto                INPUT
             29                   A             0b10000000            Tasto selezione lingua     INPUT

             30                   C                  -                Pin led caffe              OUTPUT
             31                   C                  -                Pin led the                OUTPUT
             32                   C                  -                Pin led RGB RED            OUTPUT
             33                   C                  -                Pin led RGB GREEN          OUTPUT
             34                   C                  -                Pin led RGB BLUE           OUTPUT

*/

#define SIZE_TESTO 13                                           /*Definisco la grandezza di un array chiamato testo, che conterrà tutte le frasi 
                                                                  in italiano e in inglese, che verranno stampate a video*/
#define PREZZO_CAFFE 1.20                                       //Definisco i prezzi delle bevande
#define PREZZO_THE 1.10

#define FR1 1                                                   //Definisco  il valore di ogni moneta
#define CT50 0.50
#define CT20 0.20
#define CT10 0.10

#define TIME_LED_BLINK 1000                                     //Definisco un valore tempo che verrà applicato facendo lampeggiare un led  
#define TIME_LED_ON 4000                                        //Definisco un valore tempo per cui un led rimarrà acceso o spento
#define TIME_VIEWING_TESTO 2000                                 //Definisco un valore tempo che verrà applicato facendo "lampeggiare" delle scritte

#define TIMEOUT_PREZZI 5000                                     //Definisco un valore tempo che l'arduino utilizzerà (vedi utilizzo alla riga 170)
#define TIMEOUT_MONETA 10000                                    //Definisco un valore tempo che l'arduino utilizzerà (vedi utilizzo lla riga 181)

#define PIN_LED_CAFFE 30
#define PIN_LED_THE 31
#define PIN_LED_RED 32
#define PIN_LED_GREEN 33
#define PIN_LED_BLUE 34


int tempo_attuale, stato_precedente_A, stato, i, led;                /*Creo delle variabili (tempo_attuale, stato_precedente_A,
                                                                      stato e i)
                                                                      La prima variabile viene combinata con TIMEOUT_PREZZI e con
                                                                      TIMEOUT_MONETA (Vedi funzionamento dalla riga 85)
                                                                      La variabile stato_precedente_A serve per fare un programma non bloccante
                                                                      (vedi funzionamento completo alle righe 77 e 78)
                                                                      La variabile stato induca in quale degli switch (vedi più in basso) dovrà
                                                                      "cadere" il programma
                                                                      La variabile i serve in due funzioni for (vedi funzionamento alla 
                                                                      righe 163 e 168)
                                                                      Infine led serve per sapere quale dei due led (led del caffe o del the)
                                                                      deve essere spento*/

                                                                
                                                                
char* lingua_attuale = "italiano";                                   //Vengono create delle variabili di tipo testo, e altri tre array di testo                                                                                                               
char* testo[SIZE_TESTO];                                             //Tutti questi variabili e array sono fondamentali per il cambio della
char* italiano[] =                                                   //lingua oppure per le srcitte da stampare a video (per la funzione cambio
{                                                                    //lingua guardare alle righe 220 e 226)*/
  "Benvenuti alla nostra macchina del caffe",
  "Premere il bottone corrispondente se si desiderano vedere i prezzi",
  "Il caffe costa ",
  "Il the costa ",
  "Conto attuale: ",
  "Ha scelto il caffe",
  "Ha scelto il the",
  "Bevanda in preparazione",
  "Ora e possibile ritirare la sua bevanda",
  "Siamo spiacenti, conto insufficiente. Inserire altra moneta",
  "Mancano ",
  "Prego ritiri il suo resto di ",
  "Arrivederci",
};
char* english[] =                                                    /*Da notare che le frasi sono nello stesso ordine sia in italiano che in inglese,
                                                                      questo per facilitare la programmazione*/
{
  "Welcome to our coffee machine",
  "Press the according button for see the price of drink",
  "The coffee costs ",
  "The tea costs ",
  "Current credit: ",
  "You have chosen the coffee",
  "You have chosen the tea",
  "We are preparing your drink",
  "Now you can take your drink",
  "We are sorry, but you haven't enough credit. Please insert other coins",
  "You need to insert ",
  "Now you can take your change than ",
  "Goodbye",
};

float credito, moneta_mancante, prezzo;                              /*Vengono create delle variabili di tipo float, ovvero credito (a cui verrà  
                                                                       assegnato il valore del credito appunto), moneta_mancante (a cui verrà 
                                                                       assegnato, dopo un breve calcolo, il valore della moneta da inserire se 
                                                                       questa è insufficiente) e prezzo (che contiene solamente i valori dei 
                                                                       costi delle bevande)*/
                                                    

void setup() {
  Serial.begin(9600);
  DDRA = 0b00000000;
  DDRC = 0b11111000;

  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_GREEN, HIGH);
  digitalWrite(PIN_LED_BLUE, HIGH);
  
  led = 0;
  stato = 0;                                                        //Appunto: stato 0 = Mostra scritta iniziale
  credito = 0;
  moneta_mancante = 0;
  prezzo = 0;
  stato_precedente_A = 1;
  tempo_attuale = 0;
  for (i = 0; i < SIZE_TESTO; i++) {                                //In questo modo la lungua iniziale sarà l'italiano
   testo[i] = italiano[i];
  }
}


void loop() {

  if (stato_precedente_A != PINA /* || stato == 2 || stato == 3*/ ) { //Questo if a la funzione di rendere non bloccante il programma. Continua a leggere   
                                                                      //i valori di PINA e se il valore ricevuto equivale al precedente salta l'intero 
                                                                      //programma sottostante e ricomincia a leggere i valori, il programma continua anche se 
                                                                      //lo stato è 2 o 3
    
    // Debug
    // Serial.print("PINA          : ");
    // Serial.println(PINA, BIN);
    // Serial.print("PREV_PINA     : ");
    // Serial.println(stato_precedente_A, BIN);
    // Serial.println("Stato         : " + stato);
    // Serial.println("tempo_attuale : " +  tempo_attuale);

    stato_precedente_A = PINA;                                                                                       
    Serial.println(lingua_attuale);
    Serial.println(tempo_attuale);
    switch (PINA) {
      case 0b10000000: /*tasto selezione lingua*/
        stato = 1;                                                    //Appunto: stato 1 = Cambia lingua
        break;
      case 0b00000001: /*tasto caffe*/
         prezzo = PREZZO_CAFFE;
         if (credito == 0) {
          tempo_attuale = millis();
          Serial.print(testo[2]);                                     //Appunto: viene mostrata la scritta : Il caffe costa * Fr.
          Serial.print(prezzo);
          Serial.println("Fr.");
          stato = 5;                                                  //Appunto: stato 5 = TIMEOUT PREZZI
        } else {
          digitalWrite(PIN_LED_CAFFE, HIGH);
          led = PIN_LED_CAFFE;          
          Serial.println(testo[5]);                                   //Appunto: viene mostrata la scritta : Ha scelto il caffe
          stato = 2;                                                  //Appunto: stato 4 = Procedimento
        }
        break;
      case 0b00000010: /*tasto the*/
         prezzo = PREZZO_THE;
         if (credito == 0) {
          tempo_attuale = millis();
          Serial.print(testo[3]);                                     //Appunto: viene mostrata la scritta : Il the costa * Fr.
          Serial.print(prezzo);
          Serial.println("Fr.");
          stato = 5;                                                  //Appunto: stato 5 = TIMEOUT PREZZI
        } else {
          digitalWrite(PIN_LED_THE, HIGH);
          led = PIN_LED_THE;                       
          Serial.println(testo[6]);                                  //Appunto: viene mostrata la scritta : Ha scelto il the
          stato = 2;                                                 //Appunto: stato 4 = Procedimento
        }
        break;
      case 0b00000100: /*tasto 1Fr.*/
        tempo_attuale = millis();
        credito += FR1;
        Serial.print(testo[4]);                                     //Appunto: viene mostrata la scritta : Conto attuale: * Fr.
        Serial.print(credito);
        Serial.println("Fr.");
        stato = 6;                                                  //Appunto: stato 3 = TIMEOUT MONETA
        break;
      case 0b00001000: /*tasto 50ct.*/
        tempo_attuale = millis();
        credito += CT50;
        Serial.print(testo[4]);                                     //Appunto: viene mostrata la scritta : Conto attuale: * Fr.
        Serial.print(credito);
        Serial.println("Fr.");
        stato = 6;                                                  //Appunto: stato 3 = TIMEOUT MONETA
        break;
      case 0b00010000: /*tasto 20ct.*/
        tempo_attuale = millis();
        credito += CT20;
        Serial.print(testo[4]);                                     //Appunto: viene mostrata la scritta : Conto attuale: * Fr.
        Serial.print(credito);
        Serial.println("Fr.");
        stato = 6;                                                  //Appunto: stato 3 = TIMEOUT MONETA
        break;
      case 0b00100000: /*tasto 10ct.*/
        tempo_attuale = millis();
        credito += CT10;
        Serial.print(testo[4]);                                     //Appunto: viene mostrata la scritta : Conto attuale: * Fr.
        Serial.print(credito);
        Serial.println("Fr.");
        stato = 6;                                                  //Appunto: stato 3 = TIMEOUT MONETA
        break;
      case 0b01000000: /*tasto resto*/
         stato = 4;                                                 //Appunto: stato 6 = Resto
        break;
    }
    
    switch (stato) {
      case 0: /*Mostra scritta iniziale*/        
        Serial.println(testo[0]);                                   //Appunto: vengono mostrate le scritte : Benvenuti alla nostra macchina del caffe                            
        Serial.println(testo[1]);                                   //e Premere il bottone corrispondente se si desiderano vedere i prezzi 
        break;
      case 1: /*Cambia lingua*/
        if (lingua_attuale == "italiano") {
          lingua_attuale = "english";
          for (i = 0; i < SIZE_TESTO; i++) {
            testo[i] = english[i];
          }
        } else if (lingua_attuale == "english") {
          lingua_attuale = "italiano";
          for (i = 0; i < SIZE_TESTO; i++) {
            testo[i] = italiano[i];
          }
        }
        stato = 0;                                                  //Appunto: stato 0 = Mostra scritta iniziale
        stato_precedente_A = 1;
        break;
     s case 2: /*Procedimento*/
        if (credito >= prezzo) {
          credito -= prezzo;
          digitalWrite(PIN_LED_GREEN, LOW);                                
          delay(TIME_LED_ON);
          digitalWrite(PIN_LED_GREEN, HIGH);                               
          Serial.println(testo[7]);                                 //Appunto: viene mostrata la scritta :  Bevanda in preparazione
          digitalWrite(PIN_LED_BLUE, LOW);                                
          delay(TIME_LED_ON);
          digitalWrite(PIN_LED_BLUE, HIGH);                              
          digitalWrite(led, LOW);                 
          Serial.println(testo[8]);                                 //Appunto: viene mostrata la scritta :  Ora e possibile ritirare la sua bevanda
          if (credito == 0) {
            Serial.println(testo[12]);                              //Appunto: viene mostrata la scritta : Arrivederci
            delay(TIME_VIEWING_TESTO);
            moneta_mancante = 0;
            stato = 0;                                              //Appunto: stato 0 = Mostra scritta iniziale
            stato_precedente_A = 1;
          } else {
            stato = 4;                                              //Appunto: stato 6 = Resto
          }
        } else {
          stato = 3;                                                //Appunto: stato 5 = Mancanza credito
        } 
       break;
      case 3: /*Mancanza credito*/
        Serial.println(testo[9]);                                   //Appunto: viene mostrata la scritta : Siamo spiacenti, conto insufficiente. Inserire altra moneta
        moneta_mancante = prezzo - credito;
        Serial.print(testo[10]);                                    //Appunto: viene mostrata la scritta : Mancano * Fr.
        Serial.print(moneta_mancante);
        Serial.println("Fr.");
        digitalWrite(PIN_LED_RED, LOW);                                
        delay(TIME_LED_BLINK);
        digitalWrite(PIN_LED_RED, HIGH);                                
        delay(TIME_LED_BLINK);
        digitalWrite(PIN_LED_RED, LOW);                                
        delay(TIME_LED_BLINK);
        digitalWrite(PIN_LED_RED, HIGH);                                
        break;
      case 4: /*Resto*/
        Serial.print(testo[11]);                                    //Appunto: viene mostrata la scritta : Prego ritiri il suo resto di * Fr.
        Serial.print(credito);
        Serial.println("Fr.");
        delay(TIME_VIEWING_TESTO);
        Serial.println(testo[12]);                                  //Appunto: viene mostrata la scritta : Arrivederci
        delay(TIME_VIEWING_TESTO);    

        credito = 0;
        moneta_mancante = 0;
        stato = 0;                                                  //Appunto: stato 0 = Mostra scritta iniziale
        stato_precedente_A = 1;                    
        break;
    }
  }

  if (stato == 5) {
    if (TIMEOUT_PREZZI < (millis() - tempo_attuale)) {
      stato = 0;                                                    //Appunto: stato 0 = Mostra scritta iniziale
      stato_precedente_A = 1;
    }
  } else if (stato == 6) {
      if (TIMEOUT_MONETA < (millis() - tempo_attuale)) {                                                    
        if(credito == 0) {
          stato = 0;                                                //Appunto: stato 0 = Mostra scritta iniziale
          stato_precedente_A = 1;
        } else {
        stato = 4;                                                  //Appunto: stato 4 = Resto      
      }
    }
  } 
  delay(75);                                                        //Questo delay serve per evitare "superstati" mentre il cliente sta togliendo                                                          
}                                                                   //il dito dal pulsante

