#define PIN_BUTTONS 0b00000000
#define PIN_LEDS 		0b00011110

#define START 			0b00000001

#define TEMPO 			3000

void setup() {
	DDRA = PIN_BUTTONS;
	DDRC = PIN_LEDS;
}

void loop() {
	while(!(PINA & START));
	while(PINA & START);
	switch (PINA) {
		case 0b00000001:
			PINC = 0b00000010;
			dalay(TEMPO);
			PINC = 0b00000000;
		break;
		case 0b00000101:
			PINC = 0b00000110;
			delay(TEMPO); 
			PINC = 0b00000000;
		break:
		case 0b00001001:
			PINC = 0b00001110;
			delay(TEMPO);
			PINC = 0b00000000;
		break;
		case 0b00001101:
			PINC = 0b00011110;
			dalay(TEMPO);
			PINC = 0b00000000;
		break;
	}
}
