#define PIN_MIS 3
#define PIN_LED 4

int on;
void setup() {
  Serial.begin(9600);
  pinMode(PIN_MIS, INPUT);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  on = digitalRead(PIN_MIS);
  Serial.println(on);
  
  if (on == HIGH) {
    digitalWrite(PIN_LED, HIGH);
  } else {
    digitalWrite(PIN_LED, LOW);
  }
  
  delay(100);
}
