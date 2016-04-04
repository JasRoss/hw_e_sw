//Questo programma serve per calcolare intensità, resistenza e potenza di
//circuito
//Programma scritto da Rosselli Jasemine e Plum Ryan

#define RESISTENZA_CONOSCIUTA 10000.0
#define TENSIONE_TOTALE 5

#define PIN_SENSORE A0

float resistenza2, tensione1, tensione2, potenza2, potenza1, intensita;

void setup() {

	Serial.begin(9600);

	pinMode (PIN_SENSORE, INPUT);

	resistenza2 = 0;
	tensione1 = 0;
	tensione2 = 0;
	potenza2 = 0;
	potenza1 = 0;
	intensita = 0;

}

void loop() {

	tensione2 = (analogRead(PIN_SENSORE)*5)/1023;

	tensione1 = TENSIONE_TOTALE - tensione2;

	intensita = (tensione1/RESISTENZA_CONOSCIUTA)*1000;

	resistenza2 = tensione2/(intensita/1000);

	potenza2 = tensione2*intensita;

	potenza1 = tensione1*intensita;

	Serial.print("Esempio circuito:\n\n");
	Serial.print("     + 5V ___\n             |\n             |\n            | |\n\
            | |    R1 (conosciuta)\n            | |\n\
             |\n             |\n            | | \n\
            | |--> R2 (variabile)\n            | |\n\
             |\n        -  __|\n\n\n");
	Serial.print("R1 = ");
	Serial.print(RESISTENZA_CONOSCIUTA);
	Serial.println(" [ohm]");
	Serial.print("R2 = ");
	Serial.print(resistenza2);
	Serial.println(" [ohm]");
	Serial.print("T1 = ");
	Serial.print(tensione1);
	Serial.println(" [V]");
	Serial.print("T2 = ");
	Serial.print(tensione2);
	Serial.println(" [V]");
	Serial.print("I = ");
	Serial.print(intensita);
	Serial.println(" [mA]");
	Serial.print("P1 = ");
	Serial.print(potenza1);
	Serial.println(" [mW]");
	Serial.print("P2 = ");
	Serial.print(potenza2);
	Serial.println(" [mW]");
  Serial.println();
  Serial.println(); 
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  
	/* + 5V ___
             |
	           |
            | | 
            | |    R1 (conosciuta)
					  | |
             |
	 				   |
	 				  | |
            | |--> R2 (variabile)
					  | |
					   |
        -  __|

	*/

  delay(1000);

}
