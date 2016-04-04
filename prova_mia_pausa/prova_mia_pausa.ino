#define PIN_LED 13
#define PAUSA_MS 500

int i;
float ciclims, ciclistandad;


void setup() {
  pinMode(PIN_LED, OUTPUT);
  ciclims = 0;
  ciclistandad = 1000000/7;
  i = 0;
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
  miaPausaMs(PAUSA_MS);
  digitalWrite(PIN_LED, LOW);
  miaPausaMs(PAUSA_MS);
}

void miaPausaMs(int pausaMs) {
	ciclims = ciclistandad*pausaMs;
	for ( i = 0; i < ciclims; i++) {
		asm volatile("nop");
	}
}

