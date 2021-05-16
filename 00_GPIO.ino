/*
   Fast GPIO control
   pinMode()
   digitalWrite()
   digitalRead()

   DDR 0, PORT 0: INPUT Hi-Z
   DDR 0, PORT 1: INPUT PULL-UP
   DDR 0, PORT 0: OUTPUT LOW
   DDR 0, PORT 1: OUTPUT HIGH
*/

void setup() {

  // Serial communication
  Serial.begin(9600);

  // pins set
  // INPUT: 0, OUTPUT: 1
  // D0 - D7: DDRD[0] - DDRD[7]
  DDRD |= B11111111;
  // D8 - D13: DDRB[0] - DDRB[5]
  DDRB |= B00111111;
  // D14 - D19: DDRC[0] - DDRC[5]
  DDRC |= B00111111;

  // output
  // LOW: 0, HIGH: 1
  // D0 - D7: PORTD[0] - PORTD[7]
  PORTD &= ~B11111111;
  // D8 - D13: PORTB[0] - PORTB[5]
  PORTB &= ~B00111111;
  // D14 - D19: PORTC[0] - PORTC[5]
  PORTC &= ~B00111111;

}


void loop() {

  while (true) {

    // using the PORTX
    // digitalWrite HIGH
    PORTD |= B00000000; // D0 - D7: PORTD[0] - PORTD[7]
    PORTB |= B00100000; // D8 - D13: PORTB[0] - PORTB[5]
    PORTC |= B00000000; // D14 - D19: PORTC[0] - PORTC[5]
    //Serial.println(PORTB, BIN);
    delay(500);

    // digitalWrite LOW
    PORTD &= ~B00000000; // D0 - D7: PORTD[0] - PORTD[7]
    PORTB &= ~B00100000; // D8 - D13: PORTB[0] - PORTB[5]
    PORTC &= ~B00000000; // D14 - D19: PORTC[0] - PORTC[5]
    delay(500);

    // using the _BV(X)
    // digitalWrite HIGH
    PORTB |= _BV(5); // D13: PORTB[5]
    delay(500);
    // digitalWrite LOW
    PORTB &= ~_BV(5); // D13: PORTB[5]
    delay(500);

    // digitalRead
    int val = PINB & _BV(5);
    //Serial.println(val);

  }
}
