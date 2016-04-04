#include <avr/delay.h>

#define PIN_LED 5
#define PIN_INTERRUPT	2

#define F_CPU 16000000UL 

volatile int led = LOW;

void setup () {
	pinMode(PIN_LED, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPT), variazione, FALLING);
}

void loop() {
	digitalWrite(PIN_LED, led);
}

void variazione () {
  _delay_ms(10)  ;
	led  = !led;
}
