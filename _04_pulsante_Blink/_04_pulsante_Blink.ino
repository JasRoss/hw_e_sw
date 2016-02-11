#define PIN_ENTRATA 2
#define SLEEP 500

void setup() {
  Serial.begin(9600);
  pinMode(PIN_ENTRATA, OUTPUT);
}

void loop() {
  digitalWrite(PIN_ENTRATA, HIGH);
  delay(SLEEP);
  digitalWrite(PIN_ENTRATA, LOW);
  delay(SLEEP);
}
