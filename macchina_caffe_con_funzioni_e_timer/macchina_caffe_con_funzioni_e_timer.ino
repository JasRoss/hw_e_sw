//Questo programma funziona come una macchinetta per preparare bevande, in questo caso si può scegliere tra caffè e the
//Ci sono due tasti per la scelta della bevanda, quattro che simulano l'entrata dei soldi (accettate monete da 1Fr.,50ct.,20ct. e 10ct.)
//e uno per il resto
//Inoltre c'è un led RGB che indica lo stato della preparazione (Blu), se il credito non è sufficente (Rosso) o se lo è (Verde)
//Per ultino ci sono due piccoli led che indicano la bevanda scelta
//Per migliori comprensioni in contemporanea al'arduino è consigliato l'utilizzo del monitor seriale

#define PIN_LED_RED 22                        //definisco tutti in pin che utilizzo
#define PIN_LED_GREEN 23
#define PIN_LED_BLUE 24
#define PIN_LED_CAFFE 25
#define PIN_LED_THE 26

#define TASTO_CAFFE 30
#define TASTO_THE 31

#define UNFR 32
#define CINQUANTACT 33
#define VENTICT 34
#define DIECICT 35

#define TASTO_RESTO 40

#define COSTO_CAFFE 1.20                      //definisco i prezzi
#define COSTO_THE 1.10
#define SLEEP_UNO 1000                        //definisco i tempi di attesa diversi
#define SLEEP_DUE 4000

#define TIME_PRIMO_STEP 10000
#define TIME_SECONDO_STEP 120000

char bevanda;                                 //creo le variabili necessarie
float conto, resto, moneta_mancante, costo;
int scelta, led, tempo_attuale;

void procedimento (char* bevanda) {          //creo una funzione per la procedura della preparazione della bevanda
  if (bevanda == "caffe") {
    costo = COSTO_CAFFE;
    led = PIN_LED_CAFFE;
  } else {
    if (bevanda == "the") {
      costo = COSTO_THE;
      led = PIN_LED_THE;
    }
  }
  Serial.print("Ha scelto il ");
  Serial.println(bevanda);
  digitalWrite(led, HIGH);

  if (conto >= costo) {
    digitalWrite(PIN_LED_GREEN, LOW);
    delay(SLEEP_UNO);
    digitalWrite(PIN_LED_GREEN, HIGH);
    Serial.println("Bevanda in preparazione");
    digitalWrite(PIN_LED_BLUE, LOW);
    delay(SLEEP_DUE);
    digitalWrite(PIN_LED_BLUE, HIGH);
    digitalWrite(led, LOW);
    Serial.println("Ora e possibile prendere la bevanda");

    conto -= costo;
    Serial.print("Il suo conto attuale e di ");
    Serial.print(conto);
    Serial.println(" Fr");
    if (conto == 0) {
      Serial.println("Se ha terminato gli acquisti la preghiamo di premere il tasto resto");
    }
    if (conto > costo) {
      resto = conto - costo;
      if (digitalRead(TASTO_RESTO) == HIGH) {
        Serial.println("Prego ritirare il resto");
        Serial.print("RESTO = ");
        Serial.println(resto);
        resto = 0;
      }
    }

  } else {
    if (conto != 0) {
      mancanza_credito ();
    }
  }
}

void mancanza_credito () {                   //creo una funzione per i calcoli e la procedura in caso di denaro mancante
  Serial.println("Spiacenti, conto insufficente. Inserire altra moneta");
  moneta_mancante = costo - conto;
  Serial.print("Mancano ");
  Serial.print(moneta_mancante);
  Serial.println("Fr");
  digitalWrite(PIN_LED_RED, LOW);
  delay(SLEEP_UNO);
  digitalWrite(PIN_LED_RED, HIGH);
  delay(SLEEP_UNO);
  digitalWrite(PIN_LED_RED, LOW);
  delay(SLEEP_UNO);
  digitalWrite(PIN_LED_RED, HIGH);

}

void credito () {                            //creo una funzione per mostrare il conto
  Serial.print("Il suo conto e di ");
  Serial.print(conto);
  Serial.println("Fr.");
}

void setup() {                               //definisco la modalità dei piedini (es. INPUT o OUTPUT) e il valore iniziale delle variabili
  Serial.begin(9600);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_CAFFE, OUTPUT);
  pinMode(PIN_LED_THE, OUTPUT);
  pinMode(TASTO_CAFFE, INPUT);
  pinMode(TASTO_THE, INPUT);
  pinMode(UNFR, INPUT);
  pinMode(CINQUANTACT, INPUT);
  pinMode(VENTICT, INPUT);
  pinMode(DIECICT, INPUT);
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_GREEN, HIGH);
  digitalWrite(PIN_LED_BLUE, HIGH);

  conto = 0;
  resto = 0;
  moneta_mancante = 0;
}

void loop() {                                //questa parte di programma verrà continuamente ripetuta e sarà il funzionamento completo del monitor e delle memorie della macchinetta
 
  Serial.println("\n\nSe desidera vedere i prezzi schiacciare il pulsante corrispondente\n\n");

  while (digitalRead(UNFR) == LOW && digitalRead(CINQUANTACT) == LOW && digitalRead(VENTICT) == LOW && digitalRead(DIECICT) == LOW) {

    tempo_attuale = millis();

    if (digitalRead(TASTO_CAFFE) == HIGH) {
      Serial.print("Il caffe costa ");
      Serial.println(COSTO_CAFFE);
      Serial.println("");

      while (digitalRead(TASTO_CAFFE) == HIGH);

    } else if (digitalRead(TASTO_THE) == HIGH) {
      Serial.print("Il the costa ");
      Serial.println(COSTO_THE);
      Serial.println("");

      while (digitalRead(TASTO_THE) == HIGH);
    }

    delay(100);                              //questo delay serve per un problema legato al fatto che l'arduino esegue i cicli talmente in fretta che,
                                             //nello stesso istante in qui si toglieva il dito dai pulsanti, l'arduino li contava come una sorta di
                                             //"superstato" e li considerana come un pulsanate premuto nuovamente
  }                                          
  if (millis() > tempo_attuale + TEMPO_PRIMO_STEP) {
    
    while (digitalRead(TASTO_RESTO) == LOW) {

      if (digitalRead(UNFR) == HIGH) {
        conto += 1;
        credito ();

        while (digitalRead(UNFR) == HIGH);
      }

      if (digitalRead(CINQUANTACT) == HIGH) {
        conto += 0.5;
        credito ();

        while (digitalRead(CINQUANTACT) == HIGH);
      }

      if (digitalRead(VENTICT) == HIGH) {
        conto += 0.2;
        credito ();

        while (digitalRead(VENTICT) == HIGH);
      }

      if (digitalRead(DIECICT) == HIGH) {
        conto += 0.1;
        credito ();

        while (digitalRead(DIECICT) == HIGH);
      }

      if (digitalRead(TASTO_CAFFE) == HIGH) {
        digitalWrite(PIN_LED_THE, LOW);
        procedimento("caffe");
      } else if (digitalRead(TASTO_THE) == HIGH) {
        digitalWrite(PIN_LED_CAFFE, LOW);
        procedimento ("the");
      }

      delay(100);                              //questo delay serve per un problema legato al fatto che l'arduino esegue i cicli talmente in fretta che,
                                               //nello stesso istante in qui si toglieva il dito dai pulsanti, l'arduino li contava come una sorta di
                                               //"superstato" e li considerana come un pulsanate premuto nuovamente
                                               // /!\ DEVO INSERIRE IL millis() CON LA DEFINIZIONE TIME_SECONDO_STEP E LA VARIABILE tempo_attuale
    }

    if (digitalRead(TASTO_RESTO) == HIGH) {
      if (conto == 0) {
        Serial.println("\nArrivederci!");
      } else {
        Serial.print("\nPrego, ritiri i suoi ");
        Serial.print(conto);
        Serial.println(" Fr");
        Serial.println("Arrivederci!");
        conto = 0;
        resto = 0;
      }
    }

    while (digitalRead(TASTO_RESTO) == HIGH);
    moneta_mancante = 0;
    conto = 0;
  }
}

