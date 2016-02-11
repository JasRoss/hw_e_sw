#define PIN_LED_1 6
#define PIN_LED_2 5
#define PIN_LED_3 4
#define PIN_LED_4 3
#define PIN_LED_5 2
#define PIN_SENSORE A0

#define VALORE_MIN 700
#define VALORE_MEDIO_BASSO 750
#define VALORE_MEDIO 800
#define VALORE_MEDIO_ALTO 850
#define VALORE_MAX 900

float valore_letto;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_1 , OUTPUT);
  pinMode(PIN_LED_2 , OUTPUT);
  pinMode(PIN_LED_3 , OUTPUT);
  pinMode(PIN_LED_4 , OUTPUT);
  pinMode(PIN_LED_5 , OUTPUT);
  pinMode(PIN_SENSORE, INPUT);

  valore_letto = 0;
}

void loop() {
  Serial.println(valore_letto);
  
  valore_letto = analogRead(PIN_SENSORE);
  
  if(valore_letto >= VALORE_MIN) {
   digitalWrite(PIN_LED_1 , HIGH);
  } else {
    digitalWrite(PIN_LED_1 , LOW);
  }
  if (valore_letto >= VALORE_MEDIO_BASSO) {
    digitalWrite(PIN_LED_2 , HIGH);
  } else {
    digitalWrite(PIN_LED_2 , LOW);
  }
  if (valore_letto >= VALORE_MEDIO) {
    digitalWrite(PIN_LED_3 , HIGH);
  } else {
    digitalWrite(PIN_LED_3 , LOW);
  }
  if (valore_letto >= VALORE_MEDIO_ALTO) {
    digitalWrite(PIN_LED_4 , HIGH);
  } else {
    digitalWrite(PIN_LED_4 , LOW);
  }
   if (valore_letto >= VALORE_MAX) {
    digitalWrite(PIN_LED_5, HIGH);
  } else {
    digitalWrite(PIN_LED_5 , LOW);
  }
}
