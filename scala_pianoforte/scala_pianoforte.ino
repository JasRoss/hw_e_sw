//Questo circuito funziona un po' come un pianoforte elettronico programmato tramite arduino
//Ogni tasto (ce ne sono 7 in tutto, come la scala del pianoforte) emette una frequenza diversa
//che riprofuce le sette note, ovvero do, re, mi, fa, sol, la si
//ATTENZIONE! Può essere premuto in solo tasto per volta!

//Per cominciare definisco tutti i valri più importanti, come il numero dei pin che utilizzo e 
//che cosa rappresentano

#define PIN_DO 2       //definisco che al pin 2 è "assegnata" la nota DO; questo pin sarà un INPUT
#define PIN_RE 3       //definisco che al pin 3 è "assegnata" la nota RE; questo pin sarà un INPUT
#define PIN_MI 4       //definisco che al pin 4 è "assegnata" la nota MI; questo pin sarà un INPUT
#define PIN_FA 5       //definisco che al pin 5 è "assegnata" la nota FA; questo pin sarà un INPUT
#define PIN_SOL 6      //definisco che al pin 6 è "assegnata" la nota SOL; questo pin sarà un INPUT
#define PIN_LA 7       //definisco che al pin 7 è "assegnata" la nota LA; questo pin sarà un INPUT
#define PIN_SI 8       //definisco che al pin 8 è "assegnata" la nota SI; questo pin sarà un INPUT
#define SLEEP 100      //definisco l'attesa prima di ripetere il loop (vedi loop in basso)
#define PIN_TONE 9     //definisco che al pin 9 è "assegnato" lo speaker; questo pin sarà un OUTPUT
#define FREQ_DO 262    //da qui in seguito definisco le frequenze di ogni nota
#define FREQ_RE 294
#define FREQ_MI 330
#define FREQ_FA 349
#define FREQ_SOL 392
#define FREQ_LA 440
#define FREQ_SI 494

int tasto_premuto;    //Creo la variabile tasto_premuto, che mi dice quale tasto sto premendo

void setup() {
  Serial.begin(9600);
  pinMode(PIN_DO,INPUT);
  pinMode(PIN_RE,INPUT);
  pinMode(PIN_MI,INPUT);
  pinMode(PIN_FA,INPUT);
  pinMode(PIN_SOL,INPUT);
  pinMode(PIN_LA,INPUT);
  pinMode(PIN_SI,INPUT);
  pinMode(PIN_TONE,OUTPUT);
  tasto_premuto = 0;
}

void loop() {                             //In questo loop vengono letti i valori in entrata sui sette pin e emesse le frequenze corrispondenti
  digitalRead(PIN_DO);
  if (digitalRead(PIN_DO) == HIGH) {
    tasto_premuto = 1;
  }
  digitalRead(PIN_RE);
  if (digitalRead(PIN_RE) == HIGH) {
    tasto_premuto = 2;
  }
  digitalRead(PIN_MI);
  if (digitalRead(PIN_MI) == HIGH) {
    tasto_premuto = 3;
  }
  digitalRead(PIN_FA);
  if (digitalRead(PIN_FA) == HIGH) {
    tasto_premuto = 4;
  }
  digitalRead(PIN_SOL);
  if (digitalRead(PIN_SOL) == HIGH) {
    tasto_premuto = 5;
  }
  digitalRead(PIN_LA);
  if (digitalRead(PIN_LA) == HIGH) {
    tasto_premuto = 6;
  }
  digitalRead(PIN_SI);
  if (digitalRead(PIN_SI) == HIGH) {
    tasto_premuto = 7;
  }
  
  if (tasto_premuto!= 0){ 
    switch (tasto_premuto) {
     case 1:
       tone(PIN_TONE, FREQ_DO);
       break;
     case 2:
       tone(PIN_TONE, FREQ_RE);
       break;
     case 3:
       tone(PIN_TONE, FREQ_MI);
       break;
     case 4:
       tone(PIN_TONE, FREQ_FA);
       break;
     case 5:
       tone(PIN_TONE, FREQ_SOL);
       break;
     case 6:
       tone(PIN_TONE, FREQ_LA);
       break;
     case 7:
       tone(PIN_TONE, FREQ_SI);
       break;
    }
  } else {
    noTone(PIN_TONE);                //Grazie a questo comendo posso spegnere lo speaker
  }
  
  tasto_premuto = 0;                 //faccio tornare tasto_premuto a 0 così se nella prossima lettura dei valori non sto premendo
                                     //alcun pulsante non verrà emesso alcun suono                            
  delay(SLEEP);                                   
}
