#define PIN_LED1 4
#define PIN_LED2 3
#define PIN_LED3 2
#define PIN_BTN 5
#define SLEEP1 500
#define SLEEP2 800
#define SLEEP3 1000

void sequenza() {
    digitalWrite(PIN_LED1, HIGH);
    delay(SLEEP1);
    digitalWrite(PIN_LED1, LOW);
    delay(SLEEP1);
    digitalWrite(PIN_LED2, HIGH);
    delay(SLEEP2);
    digitalWrite(PIN_LED2, LOW);
    delay(SLEEP1);
    digitalWrite(PIN_LED3, HIGH);
    delay(SLEEP3);
    digitalWrite(PIN_LED3, LOW);
    delay(SLEEP1);
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BTN, INPUT);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
}

void loop() {

  while (digitalRead(PIN_BTN) == LOW);
  
  while (digitalRead(PIN_BTN) == HIGH) {
    sequenza();
  }
}
