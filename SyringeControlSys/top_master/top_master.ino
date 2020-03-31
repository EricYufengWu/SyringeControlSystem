/* 
Adapted from Wire Master Reader by Nicholas Zambetti <http://www.zambetti.com>
Pneumatic Syringe System Master Test
This is the first working code (proof of concept) for the "big master" of the system, currently using an Arduino Nano.
This code reads pressure data which is sent from the "mid master". 
*/

#include <Wire.h>
char data[32]; //initialize character array for wire.read
float psi = 0.00;  //

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(0x66, 6);    // request 6 bytes from slave device 0x66

//  while (Wire.available()) { // slave may send less than requested
//    char c = Wire.read(); // receive a byte as character
//    Serial.print(c);         // print the character
//  }

  int i = 0;
  while (Wire.available()) { // slave may send less than requested
    data[i] = Wire.read(); // receive a byte as character
    i++;
  }
  
  String myString = String(data);
  psi = myString.toFloat();
  Serial.print("Reading from MPRLS: ");
  Serial.println(psi);

  delay(100);
}
