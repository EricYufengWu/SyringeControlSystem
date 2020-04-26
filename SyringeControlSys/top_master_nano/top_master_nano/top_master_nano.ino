/* 
Adapted from Wire Master Reader by Nicholas Zambetti <http://www.zambetti.com>
Pneumatic Syringe System Master Test
This is the first working code (proof of concept) for the "big master" of the system, currently using an Arduino Nano.
This code reads pressure data which is sent from the "mid master". 
*/

#include <Wire.h>
char data[32]; //initialize character array for wire.read
float psi = 0.00;  //
uint8_t ADDRESS[20];

void setup() {
    Wire.begin();        // join i2c bus (address optional for master)
    Serial.begin(9600);  // start serial for output
    scan_address();
}

void loop() {
    Serial.print("Reading from MPRLS 1: ");
    Serial.print(get_data(ADDRESS[0]));
    Serial.print("\tReading from MPRLS 2: ");
    Serial.println(get_data(ADDRESS[1]));
    delay(100);
}

///////////////////////////////////////////////////////////////////
Function Declaration. Do not change unless it's necessary
///////////////////////////////////////////////////////////////////

float get_data(uint8_t addr){
    Wire.requestFrom(addr, 6);    // request 6 bytes from slave device 0x66

    int i = 0;
    while (Wire.available()) { // slave may send less than requested
      data[i] = Wire.read(); // receive a byte as character
      i++;
    }

    String myString = String(data);
    psi = myString.toFloat();
    return psi;
}

void move_pressure(uint8_t addr, float psi){    
}

void move_position(uint8_t addr, float pos){
}

void scan_address(){
    
    byte error, address; //variable for error and I2C address
    int nDevices;
  
    Serial.println("Scanning...");
  
    nDevices = 0;
    for (address = 1; address < 127; address++ )
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
  
      if (error == 0){
          Serial.print("Unit #");
          Serial.print(nDevices+1);
          Serial.print(" found at address 0x");
          ADDRESS[nDevices] = address;
          if (address < 16)
              Serial.print("0");
          Serial.println(address, HEX);
          nDevices++;
      }
      else if (error == 4){
          Serial.print("Unknown error at address 0x");
          if (address < 16)
              Serial.print("0");
          Serial.println(address, HEX);
      }
    }
    if (nDevices == 0){
        Serial.println("No I2C devices found, check connection and reboot?\n");
        while (1) {delay(10);}
    }    
    else{
        Serial.println("done\n");
    }
    delay(3000);
}
