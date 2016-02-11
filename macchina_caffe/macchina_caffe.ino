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
#define SLEEP_DUE 4000

char bevanda;
int scelta;
float conto, resto, moneta_mancante;

void setup() {
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_GREEN, HIGH);
  digitalWrite(PIN_LED_BLUE, HIGH);
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
  scelta = 0;
  conto = 0;
  resto = 0;
  moneta_mancante = 0;
}

void loop() {
  Serial.println("");
  Serial.println("");
  Serial.println("Se desidera vedere i prezzi schiacciare il pulsante corrispondente");
  Serial.println("");
  Serial.println("");

  while (digitalRead(UNFR) == LOW && digitalRead(CINQUANTACT) == LOW && digitalRead(VENTICT) == LOW && digitalRead(DIECICT) == LOW) {

    if (digitalRead(TASTO_CAFFE) == HIGH) {
      Serial.print("Il caffe costa ");
      Serial.println(COSTO_CAFFE);
      Serial.println("");
    } else if (digitalRead(TASTO_THE) == HIGH) {
      Serial.print("Il the costa ");
      Serial.println(COSTO_THE);
      Serial.println("");
    }
    while (digitalRead(TASTO_CAFFE) == HIGH || digitalRead(TASTO_THE) == HIGH);
  }

  while (digitalRead(TASTO_RESTO) == LOW) {

    if (digitalRead(UNFR) == HIGH) {
      conto += 1;
      Serial.print("Il suo conto e di ");
      Serial.print(conto);
      Serial.println("Fr.");
    }
    if (digitalRead(CINQUANTACT) == HIGH) {
      conto += 0.5;
      Serial.print("Il suo conto e di ");
      Serial.print(conto);
      Serial.println("Fr.");
    }
    if (digitalRead(VENTICT) == HIGH) {
      conto += 0.2;
      Serial.print("Il suo conto e di ");
      Serial.print(conto);
      Serial.println("Fr.");
    }
    if (digitalRead(DIECICT) == HIGH) {
      conto += 0.1;
      Serial.print("Il suo conto e di ");
      Serial.print(conto);
      Serial.println("Fr.");
    }

    while (digitalRead(UNFR) == HIGH || digitalRead(CINQUANTACT) == HIGH || digitalRead(VENTICT) == HIGH || digitalRead(DIECICT) == HIGH);

    if (digitalRead(TASTO_CAFFE) == HIGH) {
      digitalWrite(PIN_LED_THE, LOW);
      scelta = 1;
      Serial.println("Ha scelto il caffe");
      digitalWrite(PIN_LED_CAFFE, HIGH);
      if (conto >= COSTO_CAFFE) {
        digitalWrite(PIN_LED_GREEN, LOW);
        delay(SLEEP_UNO);
        digitalWrite(PIN_LED_GREEN, HIGH);
        Serial.println("Caffe in preparazione");
        digitalWrite(PIN_LED_BLUE, LOW);
        delay(SLEEP_DUE);
        digitalWrite(PIN_LED_BLUE, HIGH);
        digitalWrite(PIN_LED_CAFFE, LOW);
        Serial.println("Ora e possibile prendere la bevanda");
        conto -= COSTO_CAFFE;
        Serial.print("Il suo conto attuale e di ");
        Serial.print(conto);
        Serial.println(" Fr");
        if (conto == 0) {
          Serial.println("Se ha terminato gli acquisti la preghiamo di premere il tasto resto");
        }
        if (conto > COSTO_CAFFE) {
          resto = conto - COSTO_CAFFE;
          if (digitalRead(TASTO_RESTO) == HIGH) {
            Serial.println("Prego ritirare il resto");
            Serial.print("RESTO = ");
            Serial.println(resto);
            resto = 0;
          }
        }
      } else {
        Serial.println("Spiacenti, conto insufficente. Inserire altra moneta");
        moneta_mancante = COSTO_CAFFE - conto;
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
    } else if (digitalRead(TASTO_THE) == HIGH) {
      digitalWrite(PIN_LED_CAFFE, LOW);
      scelta = 2;
      Serial.println("Ha scelto il the");
      digitalWrite(PIN_LED_THE, HIGH);
      if (conto >= COSTO_THE) {
        digitalWrite(PIN_LED_GREEN, LOW);
        delay(SLEEP_UNO);
        digitalWrite(PIN_LED_GREEN, HIGH);
        Serial.println("The in preparazione");
        digitalWrite(PIN_LED_BLUE, LOW);
        delay(SLEEP_DUE);
        digitalWrite(PIN_LED_BLUE, HIGH);
        digitalWrite(PIN_LED_THE, LOW);
        Serial.println("Ora e possibile prendere la bevanda");
        conto -= COSTO_THE;
        Serial.print("Il suo conto attuale e di ");
        Serial.print(conto);
        Serial.println(" Fr");
        if (conto == 0) {
          Serial.println("Se ha terminato gli acquisti la preghiamo di premere il tasto resto");
        }
        if (conto > COSTO_THE) {
          resto = conto - COSTO_THE;
          if (digitalRead(TASTO_RESTO) == HIGH) {
            Serial.println("Prego ritirare il resto");
            Serial.print("RESTO = ");
            Serial.println(resto);
            resto = 0;
          }
        }
      } else {

        Serial.println("Spiacenti, conto insufficente. Inserire altra moneta");
        moneta_mancante = COSTO_THE - conto;
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
      if (digitalRead(TASTO_RESTO) == HIGH) {
        Serial.println("");
        Serial.print("Prego, ritiri i suoi ");
        Serial.print(resto);
        Serial.println(" Fr");
      }
    }

  }
  if (digitalRead(TASTO_RESTO) == HIGH) {
    if (conto == 0) {
      Serial.println("Arrivederci");
    } else {
      Serial.println("");
      Serial.print("Prego, ritiri i suoi ");
      Serial.print(conto);
      Serial.println(" Fr");
      Serial.println("Arrivederci!");
      scelta = 0;
      conto = 0;
      resto = 0;
    }
  }
  while (digitalRead(TASTO_RESTO) == HIGH);
  moneta_mancante = 0;
  conto = 0;
}


