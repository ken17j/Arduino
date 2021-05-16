/*
   Fast PWM mode
   PWM_freq = CLK_freq / (Prescaler_val * (1 + TOP_val))
   ex)      = 16M / (1 * (1 + ICR1))
   D5, D6: using timer0 (delay(), millis(), micros(), ...etc also use this timer)
   D9, D10: using timer1
   D3, D11: using timer2
*/

void setup() {

  Serial.begin(9600);

  // D5, D6
  /*
     PWM_freq = 16M / (64 * (1 + 255))
     PWM_duty = OCR0A / 255
     PWM_duty = OCR0B / 255

     memo: I don't change here because other functions are affected.
  */

  // D9, D10
  /*
    PWM_freq = 16M / (1 * (1 + ICR1))
    PWM_duty = OCR1A / ICR1
    PWM_duty = OCR1B / ICR1

    memo: OCR1A/B must be changed after TCCR1A/B.
          In the case of before that, OCR1AH/BH don't be changed.
  */
  DDRB |= _BV(PB1); // D9, output
  DDRB |= _BV(PB2); // D10, output
  ICR1 = 0xFFFF; // Top, 16 bits
  TCCR1A = 1 << COM1A1; // D9, None-inverted mode
  TCCR1A |= 1 << COM1B1; // D10, None-inverted mode
  TCCR1A |= 1 << WGM11; // Fast PWM, using ICR1 as Top
  TCCR1B = (1 << WGM12) | (1 << WGM13);
  OCR1A = 0x7FFF; // D9, duty 50%, 16 bits
  OCR1B = 0x3FFF; // D10, duty 25%, 16 bits
  TCCR1B |= 1 << CS10; // no prescaling, start the timer(PWM output)
  /*
    Serial.print("ICR1:\t");
    Serial.println(ICR1, BIN);
    Serial.print("OCR1A:\t");
    Serial.println(OCR1A, BIN);
    Serial.print("OCR1B:\t");
    Serial.println(OCR1B, BIN);
    Serial.print("TCCR1A:\t");
    Serial.println(TCCR1A, BIN);
    Serial.print("TCCR1B:\t");
    Serial.println(TCCR1B, BIN);
  */

  // D3, D11
  /*
     PWM_freq = 16M / (1 * (1 + 255))
     PWM_duty = OCR2A / 255
     PWM_duty = OCR2B / 255
  */
  DDRD |= _BV(PD3); // D3, output
  DDRB |= _BV(PB3); // D11, output
  TCCR2A = 1 << COM2A1; // D11, None-inverted mode
  TCCR2A |= 1 << COM2B1; // D3, None-inverted mode
  TCCR2A |= (1 << WGM20) | (1 << WGM21); // Fast PWM, using 0xFF as Top
  //TCCR2B = (1 << WGM22);
  OCR2A = 0x7F; // D11, duty 50%
  OCR2B = 0x3F; // D3, duty 25%
  TCCR2B = 1 << CS20; // no prescaling, start the timer(PWM output)
  //TCCR2B = 1 << CS21;

}

void loop() {
  // put your main code here, to run repeatedly:
  while (true) {
    // nop
  }

}
