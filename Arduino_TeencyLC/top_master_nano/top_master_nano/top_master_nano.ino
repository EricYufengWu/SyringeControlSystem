/* 
Adapted from Wire Master Reader by Nicholas Zambetti <http://www.zambetti.com>
Pneumatic Syringe System Master Test
This is the first working code (proof of concept) for the "big master" of the system, currently using an Arduino Nano.
This code reads pospsi_raw data which is sent from the "mid master". 
*/

#include <Wire.h>
#define MEM_LEN 32
#define INPUT_LEN 8
#define MAX_UNIT 20

char psi_raw[MEM_LEN]; //stores incomming pressure command temporarily
char pos_raw[MEM_LEN]; //stores incomming position command temporarily
char databuf_psi[MEM_LEN]; //stores outgoing char array temporarily
char databuf_pos[MEM_LEN];
char input[INPUT_LEN];
uint8_t ADDRESS[MAX_UNIT];

typedef struct {
    float psi;  //
    float pos;  //
} unit_data;
unit_data dataset[MAX_UNIT];

void setup() {
    Wire.begin();        // join i2c bus (address optional for master)
    Serial.begin(9600);  // start serial for output
    scan_address();
}

void loop() {
//    get_data_all();
//    Serial.print("-Unit#0- Pressure: ");
//    Serial.print(dataset[0].psi); 
//    Serial.print(" Position: "); 
//    Serial.print(dataset[0].pos);
//    Serial.print("\t -Unit#1- Pressure: ");
//    Serial.print(dataset[1].psi); 
//    Serial.print(" Position: "); 
//    Serial.println(dataset[1].pos);
//    move_to_position(0,90.00);  //floating number, but intergers only (mm)
//    move_to_pressure(1,15.00);
//    delay(1000);

// Serial Input mode for position
// Format: "unit#-cmd-value"
// unit#: int value starting from 0
// cmd: G: get data; P: move to pressure; L: move to location
    String input_target;
    int target;
    String input_type;
    String input_value;

    if(Serial.available()){
        input_target = Serial.readStringUntil('-');
        target = input_target.toInt();
        input_type = Serial.readStringUntil('-');
        input_value = Serial.readStringUntil('\n');
        if (input_type == "g" || input_type == "G"){
            get_data(target);
            Serial.print("Unit#");
            Serial.print(target);
            Serial.print(" Pressure: ");
            Serial.print(dataset[target].psi); 
            Serial.print(" Position: "); 
            Serial.print(dataset[target].pos);
        } else if (input_type == "a" || input_type == "A"){
            get_hex_address(target);
        } else if (input_type == "l" || input_type == "L"){
            float input_cmd = input_value.toFloat();
            move_to_position(target,input_cmd);
        } else if (input_type == "p" || input_type == "P"){
            float input_cmd = input_value.toFloat();
            move_to_pressure(target,input_cmd);
        }
     Serial.println("");   
        
//        Serial.print(target);
//        Serial.print("\t");
//        Serial.print(input_type);
//        Serial.print("\t");
//        Serial.println(input_cmd);
//        
    }
    delay(10);
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

void get_hex_address(int addr){
    uint8_t ADD = ADDRESS[addr];
    Serial.print("0x");
    if (ADD < 16)
        Serial.print("0");
    Serial.println(ADD, HEX);
}

void move_to_pressure(int addr, float psi){
    if (psi >= 5.00 && psi <= 25.00){
        Serial.print("Unit#");
        Serial.print(addr);
        Serial.print(" to pressure: ");
        Serial.println(psi);
        String(psi).getBytes(databuf_psi, MEM_LEN);
        Wire.beginTransmission(ADDRESS[addr]); // transmit to device
        Wire.write("P");
        Wire.write(databuf_psi, MEM_LEN);
        Wire.endTransmission();
    }
}

void move_to_position(int addr, float pos){
    if (pos >= 0.00 && pos <= 100.00){
        Serial.print("Unit#");
        Serial.print(addr);
        Serial.print(" to position: ");
        Serial.println(pos);
        String(pos).getBytes(databuf_pos, MEM_LEN);
        Wire.beginTransmission(ADDRESS[addr]); // transmit to device
        Wire.write("L");
        Wire.write(databuf_pos, MEM_LEN);
        Wire.endTransmission();
    }
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
