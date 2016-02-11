// Questo programma funziona rilevando dei valori analogici da un sensore termico, che in base alla temeratura rilevata accende uno dei tre led disponibili
// il primo led indica una temperatura alta, il secondo una standard (vedi le tolleranze e la temperatura predefinita definite nel programma sottostante)
// e il terzo una temperatura più bassa

#define PIN_SENS A0 // definisco i pin con i quali lavoro, ovvero A0 per la lettura del valore analogico del sensore,
#define PIN_LED1 7 // il 7 per l'output del primo led,
#define PIN_LED2 6 // il 6 per l'output del secondo led,
#define PIN_LED3 5 // il 5 per l'output del terzo led
#define TOLLERANZA 0.15 // inoltre definisco i valori delle tolleranze di temperatura, cioé quelle in cui devo "stare" per ottenere una temperatura media
#define TEMP_PRED 21.9 // temperatura media definita
#define SLEEP 250 // tempo definito che indica quanto tempo aspettare per iniziare un nuovo ciclo (serve per non creare problemi al monitor)

int misura;         
float temperatura_c;

// Conversione segnale analogico in temperatura : 3.73 / 1024 * A0 * 10 = t °C

void setup() {
  Serial.begin(9600);
  pinMode(PIN_SENS, INPUT);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
}

void loop() {
  digitalWrite(PIN_LED1, LOW);                    // a ogni ciclo di questo loop vengono analizzati i dati e accesi i led corrispondenti
  digitalWrite(PIN_LED2, LOW);
  digitalWrite(PIN_LED3, LOW);
  misura = analogRead(PIN_SENS);
  temperatura_c = 3.73/1024*10*misura;
  
  if (temperatura_c > TEMP_PRED - TOLLERANZA && temperatura_c < TEMP_PRED + TOLLERANZA ) {
    digitalWrite(PIN_LED2, HIGH);
  } else {
    if (temperatura_c < TEMP_PRED - TOLLERANZA) {
      digitalWrite(PIN_LED1, HIGH);
    } else {
      digitalWrite(PIN_LED3, HIGH);
    }
  }
  
  Serial.print("Temperatura attuale = ");
  Serial.println(temperatura_c);
  delay(SLEEP);
}
