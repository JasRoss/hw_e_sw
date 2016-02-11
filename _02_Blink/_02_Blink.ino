#define MAX 1000
#define MIN 100
#define INC 100
#define PIN_LED 13

boolean incremento;
int alt;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  incremento = false;
  alt = 100;
}

void loop() {
  if(incremento) {
    if(alt <= MAX) {
      digitalWrite(PIN_LED, HIGH);
      delay(alt);
      digitalWrite(PIN_LED, LOW);
      delay(alt);
      alt = alt + INC;
    } else {
      incremento = false;
    }
  } else {
    if(alt >= 100) {
      digitalWrite(PIN_LED, HIGH);
      delay(alt);
      digitalWrite(PIN_LED, LOW);
      delay(alt);
      alt = alt - INC;
    } else {
      incremento = true;
    }
  }
}

