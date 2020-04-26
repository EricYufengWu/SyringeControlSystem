/* 
Adapted from Wire Master Reader by Nicholas Zambetti <http://www.zambetti.com>
Pneumatic Syringe System Master Test
This is the first working code (proof of concept) for the "big master" of the system, currently using an Arduino Nano.
This code reads pospsi_raw data which is sent from the "mid master". 
*/

#include <Wire.h>
char psi_raw[32]; //initialize character array for wire.read
char pos_raw[32];
uint8_t ADDRESS[20];
typedef struct {
    float psi;  //
    float pos;  //
} unit_data;
unit_data dataset[20];

void setup() {
    Wire.begin();        // join i2c bus (address optional for master)
    Serial.begin(9600);  // start serial for output
    scan_address();
}

void loop() {
    //    get_data(0);
    get_data_all();
    Serial.print("-Unit#0- Pressure: ");
    Serial.print(dataset[0].psi); 
    Serial.print(" Position: "); 
    Serial.print(dataset[0].pos);
    Serial.print("\t -Unit#1- Pressure: ");
    Serial.print(dataset[0].psi); 
    Serial.print(" Position: "); 
    Serial.println(dataset[0].pos);
    delay(100);
}

///////////////////////////////////////////////////////////////////
//Function Declaration. Do not change unless it's necessary
///////////////////////////////////////////////////////////////////

// Get data form all units once
void get_data_all(){   
    for (int j = 0; j < sizeof(ADDRESS); j++ ){
        if (ADDRESS[j] != 0){
            Wire.requestFrom(ADDRESS[j], 10);    // request X bytes from slave device

            int i = 0;
            while (Wire.available()) { // slave may send less than requested
                if (i < 5){
                    psi_raw[i] = Wire.read(); // receive a byte as character
                } else{
                    pos_raw[i-5] = Wire.read();
                }
                i++;
            }
            String psi_raw_string = String(psi_raw);
            String pos_raw_string = String(pos_raw);
            dataset[j].psi = psi_raw_string.toFloat();
            dataset[j].pos = pos_raw_string.toFloat();
        } else{
            break;
        }
    }
    return;    
}

// Get data from specific unit(num starts from 0)
void get_data(int unit_num){
    Wire.requestFrom(ADDRESS[unit_num], 10);    // request X bytes from slave device

    int i = 0;
    while (Wire.available()) { // slave may send less than requested
        if (i < 5){
            psi_raw[i] = Wire.read(); // receive a byte as character
        } else{
            pos_raw[i-5] = Wire.read();
        }
        i++;
    }
    String psi_raw_string = String(psi_raw);
    String pos_raw_string = String(pos_raw);
    dataset[unit_num].psi = psi_raw_string.toFloat();
    dataset[unit_num].pos = pos_raw_string.toFloat();
    return;
}

void move_to_pressure(uint8_t addr, float psi){    
}

void move_to_position(uint8_t addr, float pos){
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
            Serial.print(nDevices);
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
