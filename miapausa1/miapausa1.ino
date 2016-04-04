//Questo programma funziona come un delay, ma è utilizzabile anche all'interno
//di programmi con interrupt

//So che ogni 7ms vengono eseguiti 1000000 cicli (non so esattamente quanto sia
//precisa questa stima, in fondo al programma si vede il modo utilizzato per 
//giungere a queste conclusioni)

#define PAUSA_MS 500						//inizialmente vengono definiti i tempi di attesa
#define PAUSA_MICROS 2

int i;												//creo le variabili necessarie
int tempo = 0;
int tempo_impiegato = 0;

int ciclims, ciclimicros;

  
void setup() {
  Serial.begin(9600);
}

void loop() {
  miaPausaMs(PAUSA_MS);
  miaPausaMicros(PAUSA_MICROS);
}

//Funzione miaPausaMs: funziona come un delay normale
void miaPausaMs(int pausaMs) {
//Il calcolo seguente non è stato fatto rientrare nel conteggio dei cicli, per
//"calibrare" la funzione, ma, dopo alcune prove, ho notato che ci vogliono
//un'enorme sequenza di cicli per ottenere un risultato visibile (tramite 
//il monitor seriale), periò non fa quasi differenza
//La stessa cosa vale per il calcolo di ciclimircos
	ciclims = (1000000*pausaMs)/7;			
  for(i=0; i < ciclims; i++);
}

//Funzione miaPausaMicros: funziona come un delayMircoseconds()
void miaPausaMicros(int pausaMicros) {
	ciclimicros = (1000000*1000*pausaMicros)/7;
	for(i=0; i < ciclimicros; i++);
}

/*

	Come ho capito che ogni 1000000 cicli passano 7ms (valore non 
	esattamente preciso):

	pausaMs = 1000000			-> ho notato che togliendo anche solo  uno zero, non 
													 si otteneva alcun risultato visibile

	tempo = millis();
	for(i=0; i < pausaMs; i++);
	  
	tempo_impiegato = millis() - tempo;

	Serial.println(tempo_impiegato);

 	while(1);

  */
