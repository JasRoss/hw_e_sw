#define PIN_BUTTONS 0b00000000		//NOT alt+n+space ~ 
#define PIN_LEDS 		0b00011110

#define ACCESO 			0b00011110
#define SPENTO 			0b00000000

#define START 			0b00000001
#define S0 					0b00000100
#define S1 					0b00001000

#define HZ_1 500
#define HZ_0_5 1000

#define CICLI 10

int i;

void setup() {
	Serial.begin(9600);

	DDRA = PIN_BUTTONS;		//bit 0: START
												//bit 1: S0
												//bit 2: S1

	DDRC = PIN_LEDS;  		//bit 1: Led1
												//bit 2: Led2
												//bit 3: Led3
												//bit 4: Led4
}

void loop() {
  Serial.println(PINA);
	while(!(PINA & START));
	while(PINA & START);

	if(PINA & S0) {
		for(i = 0; i < CICLI; i++) {
			PORTC = ACCESO;
			delay(HZ_1);
			PORTC = SPENTO;
			delay(HZ_1);
		}
	} else if(PINA & S1) {
		for(i = 0; i <CICLI; i++) {
			PORTC = ACCESO;
			delay(HZ_0_5);
			PORTC = SPENTO;
			delay(HZ_0_5);
		}
	}
}
