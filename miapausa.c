#define TEMPO_PER_1_CICLO 1 //(esempio!!)

void miaPausaMs(int pausaMs) {

}

void miaPausaMicros(int pausaMicros) {


}

/*
	int i = 0;
	int tempo = 0;
	int tempo_impiegato = 0;
	pausaMs = 1;

	tempo = millis();

	while(i < pausaMs) {
		i++;
	}

	tempo_impiegato = millis() - tempo;

	Serial.println(tempo_impiegato);
*/

/*
	calcolare lo scalino necessario per la capire quale valore di pausaMs o 
	pausaMicro utilzzare

	so quanto tempo ci mette a fare 1 ciclo (es 1 ms) quindi per dover attendere
	12 ms bisogna fare 12/2ms = 6 clicli
*/
