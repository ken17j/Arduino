void setup() {

  Serial.begin(9600);

}

void loop() {

  String serial_val; // serial values
  int num_val;

  while (true) {
    serial_val = serial_rx();
    Serial.println(serial_val);
    num_val = serial_val.toInt(); // convert to a numerical value
    Serial.println(num_val);
  }

}


String serial_rx() {

  int n = 0; // the lenth of serial datas
  char rx = 0; // a serial value
  String val = ""; // all serial datas

  // wait until to get serial datas
  while (Serial.available() < 1) {
    // nop
  }
  delay(100);

  // get serial datas as the character string
  n = Serial.available();
  for (int i = 0; i < n; i++) {
    rx = Serial.read();
    val.concat(rx);
  }
  val.trim(); // delete spaces and newlines at the first and the end

  return val;

}
