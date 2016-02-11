//Questo programma fa riprodurre dal sette segmenti i numeri da uno a F (esadecimale)
//Usa solo le porte A e C

int valori_pulsanti [] = { //assegno i valori per l'array
	 ~0x3F,//caso 0          //i valori in questione sono tutte le combinazioni dei tasti
   ~0x06, //caso 1         
   ~0x5B, //caso 2
   ~0x4F, //caso 3
   ~0x66, //caso 4
   ~0x6D, //caso 5
   ~0x7D, //caso 6
   ~0x07, //caso 7
   ~0x7F, //caso 8
   ~0x6F, //caso 9
   ~0x77, //caso 10
   ~0x7C, //caso 11
   ~0x39, //caso 12
   ~0x5E, //caso 13
   ~0x79, // caso 14
   ~0x71  //caso 15
};

void setup() {
	DDRC = 0b00000000; //definisco che la porta C è composta unicamente da INPUT
	DDRA = 0b01111111; //definisco che la porta A è composta unicamente da OUTPUT
}

void loop() {
	PORTA = valori_pulsanti[PINC];
}
