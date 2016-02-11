#define PIN_LED_RED 22
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

#define COSTO_CAFFE 1.20
#define COSTO_THE 1.10

#define SLEEP_UNO 1000
#define SLEEP_DUE 2000

int conto, resto, moneta_mancante;
int scelta;

void manca_credito(char*);

void setup() {
  Serial.begin(9600);

  pinMode(PIN_LED_RED, INPUT);
  pinMode(PIN_LED_GREEN, INPUT);
  pinMode(PIN_LED_BLUE, INPUT);
  pinMode(PIN_LED_CAFFE, INPUT);
  pinMode(PIN_LED_THE, INPUT);
  pinMode(TASTO_CAFFE, INPUT);
  pinMode(TASTO_THE, INPUT);
  pinMode(UNFR, INPUT);
  pinMode(CINQUANTACT, INPUT);
  pinMode(VENTICT, INPUT);
  pinMode(DIECICT, INPUT);

  scelta = 0;
  conto = 0;
  resto = 0;
  moneta_mancante = 0;
}

void loop() {
  Serial.println("LA MACCHINA DEL CAFFE JASMINE&CO VI DA IL BENVENUTO");
  Serial.println("Se desidera vedere i prezzi schiacciare il pulsante corrispondente");
  
  while (digitalRead(UNFR) == LOW || digitalRead(CINQUANTACT) == LOW || digitalRead(VENTICT) == LOW || digitalRead(DIECICT) == LOW) {
    if (digitalRead(TASTO_CAFFE) == HIGH) {
      Serial.print("Il caffé costa ");
      Serial.println(COSTO_CAFFE);
    } else if (digitalRead(TASTO_THE) == HIGH) {
      Serial.print("Il the costa ");
      Serial.println(COSTO_THE);
    }
  }
  
  do { 
    if (digitalRead(UNFR) == HIGH) {
      conto += 1;
      Serial.print("Il suo conto è di ");
      Serial.print(conto);
      Serial.println("Fr.");
    }
    if (digitalRead(CINQUANTACT) == HIGH) {
      conto += 0.5;
      Serial.print("Il suo conto è di ");
      Serial.print(conto);
      Serial.println("Fr.");
    }
    if (digitalRead(VENTICT) == HIGH) {
      conto += 0.2;
      Serial.print("Il suo conto è di ");
      Serial.print(conto);
      Serial.println("Fr.");
    }
    if (digitalRead(DIECICT) == HIGH) {
      conto += 0.1;
      Serial.print("Il suo conto è di ");
      Serial.print(conto);
      Serial.println("Fr.");
    }

    while (digitalRead(UNFR) == HIGH || digitalRead(CINQUANTACT) == HIGH || digitalRead(VENTICT) == HIGH || digitalRead(DIECICT) == HIGH);
   
    if (digitalRead(TASTO_CAFFE) == HIGH) {
      scelta = 1;
      Serial.println("Ha scelto il caffé");
      digitalWrite(PIN_LED_CAFFE, HIGH);
      
      if (conto >= COSTO_CAFFE) {
        digitalWrite(PIN_LED_GREEN, HIGH);
        delay(SLEEP_UNO);
        digitalWrite(PIN_LED_GREEN, LOW);
        Serial.println("Caffé in preparazione");
        digitalWrite(PIN_LED_BLUE, HIGH);
        delay(SLEEP_DUE);
        digitalWrite(PIN_LED_BLUE, LOW);

        if (conto > COSTO_CAFFE) {
          resto = conto - COSTO_CAFFE;
          Serial.println("Prego ritirare il resto");
          Serial.print("RESTO = ");
          Serial.println(resto);
        }
        Serial.println("Ora è possibile prendere la bevanda");
      }
      else {
        digitalWrite(PIN_LED_RED, HIGH);
        delay(SLEEP_UNO);
        digitalWrite(PIN_LED_RED, LOW);
        delay(SLEEP_UNO);
        digitalWrite(PIN_LED_RED, HIGH);
        delay(SLEEP_UNO);
        digitalWrite(PIN_LED_RED, LOW);
        Serial.println("Spiacenti, conto insufficente. Inserire altra moneta");
        moneta_mancante = COSTO_CAFFE - conto;
        Serial.print("Mancano ");
        Serial.print(moneta_mancante);
        Serial.println("Fr");
    
      }
    } else if (digitalRead(TASTO_THE) == HIGH) {
      scelta = 2;
      Serial.println("Ha scelto il the");

      if (conto>=COSTO_THE) {
        digitalWrite(PIN_LED_GREEN, HIGH);
        delay(SLEEP_UNO);
        digitalWrite(PIN_LED_GREEN, LOW);
        Serial.println("The in preparazione");
        digitalWrite(PIN_LED_BLUE, HIGH);
        delay(SLEEP_DUE);
        digitalWrite(PIN_LED_BLUE, LOW);

        if (conto>COSTO_CAFFE) {
          resto = conto - COSTO_CAFFE;
          Serial.println("Prego ritirare il resto");
          Serial.print("RESTO = ");
          Serial.println(resto);
        }
        Serial.println("Ora è possibile prendere la bevanda");
      }
      else {
        digitalWrite(PIN_LED_RED, HIGH);
        delay(SLEEP_UNO);
        digitalWrite(PIN_LED_RED, LOW);
        delay(SLEEP_UNO);
        digitalWrite(PIN_LED_RED, HIGH);
        delay(SLEEP_UNO);
        digitalWrite(PIN_LED_RED, LOW);
        Serial.println("Spiacenti, conto insufficente. Inserire altra moneta");
        moneta_mancante = COSTO_CAFFE - conto;
        Serial.print("Mancano ");
        Serial.print(moneta_mancante);
        Serial.println("Fr");
      }
    }
  } while (scelta = 0 || digitalRead(TASTO_RESTO) == LOW);
  
  if (digitalRead(TASTO_RESTO) == HIGH && resto > 0) {
    Serial.println("Prego, ritirare la monteta");
  }

  scelta = 0;
  resto = 0;
  moneta_mancante = 0;
  conto = 0;
}

void manca_credito(char* bevanda) {

}
