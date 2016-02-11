#define MAX 1000
#define MIN 100
#define INC 50
#define LED_PIN 13

int i;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void blink(int t) {
  Serial.print("Il tempo d'attesa attuale corrisponde a ");
  Serial.println(t);
  digitalWrite(LED_PIN, HIGH);
  delay(t);
  digitalWrite(LED_PIN, LOW);
  delay(t);
}

void loop() {
  for (i = MIN; i <= MAX; i = i + INC) {
    blink(i);
  }
  for (i = MAX; i >= MIN; i = i - INC){
    blink(i);
  }
}
