/*
  1)
  LMAX 0 _|_ _ _ _|  (V) /!\ 
          |       |
TUBO ON   |-------|
| ____    |       |
  ____ \  |       |
       \\_|       |
        \_|_______|
          |_______| --> 0°

2)
   LMAX 1_|_______|  (R) /!\
          |       |
TUBO ON   |       |
| ____    |       |
  ____ \  |       |
       \\_|       |
        \_|_______|
          |_______| --> 0°

3)
__________________  (R/-) /!\
_________________  \
  |               \ \
TUBO OFF         _|_|______________   
                | |_____          |
                | |     \____     |
                | |          \____|_
        90° <-- |_|_______________|_ \                     
                                    | |

4)
      DOPO 10 SECONDI

   LMAX 0_|_ _ _ _|  (V) /!\ 
          |       |
TUBO ON   |       |
| ____    |       |
  ____ \  |       |
       \\_|-------|
        \_|_______|
          |_______| --> 0°

*/


#include <Servo.h>

#define PIN_LMAX
#define PIN_SERVO
#define PIN_LED_RED
#define PIN_LED_GREEN
#define PIN_LED_BLUE
#define RIPOSO 0
#define ATTIVO 90

//ATTENZIONE! La variabile booleana seguente non è effettivamente necessaria
//per questo programma! Serve solo per simulare un caso reale!
bool tubo;

Servo motor;

int i;

void setup() {
  // ...
  Serial.bregin (9600);

  pinMode (PIN_LMAX, INPUT);

  pinMode (PIN_LED_RED, OUTPUT);
  pinMode (PIN_LED_GREEN, OUTPUT);

  digitalWrite (PIN_LED_RED, 1);
  digitalWrite (PIN_LED_GREEN, 1);
  digitalWrite (PIN_LED_BLUE, 1);

  motor.attach (PIN_SERVO);

}

void loop() {
  // ...
  motor.write(0);
  digitalWrite (PIN_LED_GREEN, LOW);

  if ((digitalRead(PIN_LMAX)) == 1) {
    
    while ((digitalRead(PIN_LMAX)) == 1);

    digitalWrite (PIN_LED_GREEN, HIGT);

    motor.write(90);
    for (i = 0; i < 10; i++) {
      digitalWrite (PIN_LED_RED, LOW);
      delay (500);
      digitalWrite (PIN_LED_RED, HIGT);
      delay(500);
    }
  }
}
