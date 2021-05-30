/*
   Parameter setting
   (0) set Kp = Ki = Kd = 0
   (1) increase Kp, the output will be larger
   (2) increase Ki, the output will be the target value
   (3) increase Kd, the output will be the target value faster

   This code is an PID tutorial using DAC circuit.
   PWM output -> DAC -> ADC input
   anarogWrite() -> LPF -> anarogRead()
   fc = 100 Hz
*/

#define Kp 0.5 // proportional 
#define Ki 0.3 // integral
#define Kd 0.05 // differential

#define INPUT_PIN 0 // analog input
#define OUTPUT_PIN 6 // analog(PWM) output


void setup() {

  Serial.begin(9600);
  delay(500);

}


void loop() {

  // initialize variables
  float val_tgt; // target values
  float val; // output values
  unsigned long t; // current times
  float u; // control values

  val_tgt = 4.0;
  val = 0;
  t = 0;
  u = 0;

  while (true) {
    // get the output(FB) value and the current time
    val = get_output();
    t = micros();
    // updata the control value "u"
    u = PID(val_tgt, val, t);
    // control an unit using "u"
    ctrl(u);

    delay(500); // please delete this
  }

}


float get_output() {

  float val = 0;

  val = analogRead(INPUT_PIN);
  val = val / 1024.0 * 5.0; // convert to voltage

  return val;

}


void ctrl(float u) {

  int duty = 0;

  duty = constrain(u, 0, 255); // convert to the PWM value
  analogWrite(OUTPUT_PIN, duty);

}


float PID(float r, float y, unsigned long t) {
  /*
     r: reference(target) value
     y: output value
     t: current time [us]
  */

  float dt = 0; // difference time
  float e = 0; // error
  static float e_i = 0; // error, integral
  float e_d = 0; // error, differential
  float u = 0; // operation amount
  static float e_pre = 0; // prebious error
  static unsigned long t_pre = 0; // previous time

  // P
  e = r - y;

  // I
  dt = (t - t_pre) / 1000000.0; // [us] -> [s]
  e_i = e_i + e * dt;

  // D
  e_d = (e - e_pre) / dt;

  // keep prebious values
  e_pre = e;
  t_pre = t;

  // PID
  u = Kp * e + Ki * e_i + Kd * e_d;

  // show datas
  int buf[] = {y,
               Kp * e,
               Ki * e_i,
               Kd * e_d,
               u
              };
  for (int i = 0; i < 5; i++) {
    Serial.print(buf[i]);
    Serial.print("\t");
  }
  Serial.println("");

  //Serial.println(val_cur);

  return u;

}
