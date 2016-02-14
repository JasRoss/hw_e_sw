/* Questo programma serve per una situzione del genere (vedi figure)


                      __led RGB
  1)                  |               Il serbatoio si riempie
  LMAX 0 _|_ _ _ _|  (V) /!\          Il led RGB è illuminato di verde
          |       |                   Il servomotore è a 0°
TUBO ON   |-------|                   LMAX è inattivo
| ____    |       |--serbatoio        Il tubo è acceso
  ____ \  |       |
       \\_|       |
        \_|_______|
          |_______| --> 0°

2)
   LMAX 1_|_______|  (R) /!\          Il serbatoio è pieno
          |       |                   Il led RGB si illumina di rosso
TUBO ON   |       |                   Il servomotore è ancora a 0°
| ____    |       |                   LAMX si attiva
  ____ \  |       |                   Il tubo è ancora acceso
       \\_|       |
        \_|_______|
          |_______| --> 0°

3)
__________________  (R/-) /!\         Il servomotore si sposta a 90°
_________________  \                  Il led RGB lampeggia di rosso
  |               \ \                 Il tubo si spegne
TUBO OFF         _|_|______________   
                | |     \____     |
                | |          \____|_
        90° <-- |_|_______________|_ \                     
                                    | |

4)
      DOPO 10 SECONDI                 Il serbatoio si riempie
                                      Il led RGB è illuminato di verde
   LMAX 0_|_ _ _ _|  (V) /!\          Il servomotore torna a 0°
          |       |                   LMAX è inattivo
TUBO ON   |       |                   Il tubo si accende
| ____    |       |
  ____ \  |       |
       \\_|-------|
        \_|_______|
          |_______| --> 0°

*/


#include <Servo.h>

#define PIN_LMAX 2
#define PIN_SERVO 8
#define PIN_LED_RED 4
#define PIN_LED_GREEN 3
#define RIPOSO 0
#define ATTIVO 90

//ATTENZIONE! La variabile booleana seguente non è effettivamente necessaria
//per questo programma! Serve solo per simulare un caso reale!
bool tubo;

Servo motor;

int i;

void setup() {
  // ...
  Serial.begin (9600);

  pinMode (PIN_LMAX, INPUT);

  pinMode (PIN_LED_RED, OUTPUT);
  pinMode (PIN_LED_GREEN, OUTPUT);

  digitalWrite (PIN_LED_RED, HIGH);
  digitalWrite (PIN_LED_GREEN, HIGH);

  motor.attach (PIN_SERVO);

}

void loop() {
  // ...
  Serial.println(digitalRead(PIN_LMAX));
  motor.write(RIPOSO);
  tubo = true;
  digitalWrite (PIN_LED_GREEN, LOW);

  if ((digitalRead(PIN_LMAX)) == HIGH) {
    
    while ((digitalRead(PIN_LMAX)) == HIGH);

    digitalWrite (PIN_LED_GREEN, HIGH);

    tubo = false;
    motor.write(ATTIVO);
   
    for (i = 0; i < 10; i++) {
      digitalWrite (PIN_LED_RED, LOW);
      delay (500);
      digitalWrite (PIN_LED_RED, HIGH);
      delay(500);
    }
  }
  delay(100);
}
