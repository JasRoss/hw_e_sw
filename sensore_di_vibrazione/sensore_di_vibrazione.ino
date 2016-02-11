#include <LiquidCrystal.h>

#define PIN_SENSORE A0

#define PIN_RS 2
#define PIN_E 3

#define PIN_BUS4 4
#define PIN_BUS5 5
#define PIN_BUS6 6
#define PIN_BUS7 7

#define TOLLERANZA 700

int valore_letto, numerazione;

//(rs, e, d4, d5, d6, d7)
LiquidCrystal schermo(PIN_RS, PIN_E, PIN_BUS4, PIN_BUS5, PIN_BUS6, PIN_BUS7);

void setup() {
  Serial.begin(9600);

  schermo.begin(16, 2);
  
  valore_letto = 0;
  numerazione = 0;
}

void loop() {

  schermo.clear();
  schermo.print(numerazione);
  Serial.println(valore_letto);

  valore_letto = analogRead(PIN_SENSORE);
  
  if (valore_letto <= TOLLERANZA) {
    numerazione ++;
  }
  
  if (numerazione == 6) { 
    schermo.clear();
    schermo.print(numerazione);
    numerazione = 0;
  }

  delay(500);
}
