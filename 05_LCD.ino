/*
   Using Teensy 4.0.
   The LCD module is AQM0802A-FLW-GBW.
*/

#include <Wire.h>
#include <WireIMXRT.h>
#include <WireKinetis.h>

#define ADDR 0x3E // Slave address (7bit).


void setup() {
  Serial.begin(9600);  // Serial communication.
  Wire.begin();  // I2C.
  delay(1000);
  init_lcd();
  clear_display();
}


void loop() {
  String val;

  val = "ISHII";
  display_chars(0, val);  // On line 0.
  val = "KEN";
  display_chars(1, val);  // On line 1.
  delay(1000);
  clear_display();
  delay(1000);
}


void send_cmd(byte data) {
  // Write a command data.
  Wire.beginTransmission(ADDR);  // The addres is 7bit without R/W.
  delay(1);
  Wire.write(0x00);
  delay(1);
  Wire.write(data);
  delay(1);
  Wire.endTransmission();
  delay(1);
}


void send_data(byte data) {
  // Write a character data.
  Wire.beginTransmission(ADDR);  // The addres is 7bit without R/W.
  delay(1);
  Wire.write(0x40);
  delay(1);
  Wire.write(data);
  delay(1);
  Wire.endTransmission();
  delay(1);
}


void init_lcd() {
  // Initialize the LCD.
  send_cmd(0x38);  // Function set.
  send_cmd(0x39);  // Start the extended command.
  send_cmd(0x14);  // Internal OSC frequency.
  send_cmd(0x70);  // Contrast set.
  send_cmd(0x56);  // Power / ICON / Contrast control.
  send_cmd(0x6C);  // Follower control.
  delay(300);
  send_cmd(0x38);  // Finish the extended command.
  send_cmd(0x0C);  // Display ON.
  send_cmd(0x01);  // Clear the display.
  delay(100);
}


void clear_display() {
  // Clear the display.
  send_cmd(0x01);  // Clear the display.
}


void display_chars(int line, String val) {
  // Display characters.
  byte buf[8] = "        ";

  // Select the line.
  if (line == 0) {
    send_cmd(0x80);  // Move the cursor to (0, 0).
  }
  else {
    send_cmd(0xC0);  // Move the cursor to (0, 1).
  }
  // Display characters.
  val.getBytes(buf, 8);  // Copy val to buf.
  for (int i = 0; i < 8; i++) {
    send_data(val[i]);
  }

}
