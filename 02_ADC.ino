/*
   ADC_freq = CLK / Prescaler_val
   50k < ADC_freq < 200k for the best conversion when using 10 bits.
*/


void setup() {

  Serial.begin(9600);

  // ADC A0 - A5
  ADMUX = 1 << REFS0; // Vref = 5.0V
  ADMUX |= 0;// A0 - A5: 0 - 5
  ADCSRA = 1 << ADEN; // ADC enable
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // prescaler = 128: 125 kHz
  Serial.println(ADCSRA, BIN);

}


void loop() {

  int val; // ADC result

  while (true) {
    ADCSRA |= 1 << ADSC; // start ADC
    while (ADCSRA & (1 << ADSC)) {
      // ADC now
    }
    val = ADCL; // read ADCL first
    val = (ADCH << 8) | val; // result
    Serial.println(val);
    Serial.println(val / 1024.0 * 5.0);
    delay(500);
  }

}
