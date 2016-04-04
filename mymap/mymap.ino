#define R1MAX 10
#define R1MIN 0

#define R2MAX 100
#define R2MIN 0

#define PIN_FOTORESISTENZA1 2
#define PIN_FOTORESISTENZA2 3

float valore_comparato_float, val_float;

float floatmap(float r1max, float r1min, float r2max, float r2min, float valore_comparato_1) {
  return ((r2max-r2min)*(valore_comparato_1))/(r1max-r1min);
}

void setup() {
	Serial.begin(9600);
  pinMode(PIN_FOTOREISTENZA1, INPUT);
}

void loop() {
  
 val_float = floatmap(R1MAX, R1MIN, R2MAX, R2MIN, valore_comparato_float);

}


