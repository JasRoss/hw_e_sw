#define PIN_BUTTONS 0b00000000
#define PIN_LEDS    0b00011110

#define START       0b00000001
#define SPENTO      0b00000000

#define FILTRO      0b00001101

#define TEMPO       3000

void setup() {
  Serial.begin(9600);
  
  DDRA = PIN_BUTTONS;
  DDRC = PIN_LEDS;
}

void loop() {
  delay(50);               //serve per evitare il rimbalzo
  while(!(PINA & START));
  while(PINA & START);
  delay(50);               //serve per evitare il rimbalzo
  while(!(PINA & START));
  Serial.println(PINA & FILTRO);
  switch (PINA & FILTRO) { //FILTRO serve per "Pulire" il segnale da eventuali
    case 1:                //errori
      PORTC = 0b00000010;
      delay(TEMPO);
      PORTC = SPENTO;
    break;
    case 5:
      PORTC = 0b00000110;
      delay(TEMPO); 
      PORTC = SPENTO;
    break;
    case 9:
      PORTC = 0b00001110;
      delay(TEMPO);
      PORTC = SPENTO;
    break;
    case 13:
      PORTC = 0b00011110;
      delay(TEMPO);
      PORTC = SPENTO;
    break;
  }
}

