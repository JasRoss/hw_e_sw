//Questo programma fa riprodurre dal sette segmenti i numeri da uno a F (esadecimale)

#define ZERO 0 //definisco gli stati possibili dei pulsanti
#define UNO 1  //(per vedere il calcolo eseguito per trasformare il numero binario in
#define DUE 2  //in numero decimale andare alla riga 49)
#define TRE 3
#define QUATTRO 4
#define CINQUE 
#define SEI 6
#define SETTE 7
#define OTTO 8
#define NOVE 9
#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15

#define PIN_BUTTON1 2 //definisco i pin dei pulsanti
#define PIN_BUTTON2 3
#define PIN_BUTTON3 4
#define PIN_BUTTON4 5


int valore_pulsanti;  //creo una variabile che contiene i valori dei pulsanti

void setup() {	

	DDRA = 0b01111111;  //definisco che la porta A è composta da 7 bit di OUTPUT

	pinMode (PIN_BUTTON1, INPUT); //definisco che i pin dei pulsanti sono INPUT
	pinMode (PIN_BUTTON2, INPUT);
	pinMode (PIN_BUTTON3, INPUT);
	pinMode (PIN_BUTTON4, INPUT);

	valore_pulsanti = 0;          //assegno 0 come valore iniziale alla variabile 

}

void loop() {
	valore_pulsanti = (digitalRead(PIN_BUTTON1) + digitalRead(PIN_BUTTON2)*2
										+ digitalRead(PIN_BUTTON3)*4 + digitalRead(PIN_BUTTON4)*8);

	switch (valore_pulsanti) {
		//(Appunti miei che non centrano col programma)
		//'~' funziona come NOT (tasti: alt n)
		case 0:
			PORTA = ~0x3F; // 0011 1111
		break;
		case 1:
			PORTA = ~0x06;
		break;
		case 2:
			PORTA = ~0x5B;
		break;
		case 3:
			PORTA = ~0x4F;
		break;
		case 4:
			PORTA = ~0x66;
		break;
		case 5:
			PORTA = ~0x6D;
		break;
		case 6:
			PORTA = ~0x7D;
		break;
		case 7:
			PORTA = ~0x07;
		break;
		case 8:
			PORTA = ~0x7F;
		break;
		case 9:
			PORTA = ~0x6F;
		break;
		case 10:
			PORTA = ~0x77;
		break;
		case 11:
			PORTA = ~0x7C;
		break;
		case 12:
			PORTA = ~0x39;
		break;
		case 13:
			PORTA = ~0x5E;
		break;
		case 14:
			PORTA = ~0x79;
		break;
		case 15:
			PORTA = ~0x71;
		break;
	}
  delay(250);
}
