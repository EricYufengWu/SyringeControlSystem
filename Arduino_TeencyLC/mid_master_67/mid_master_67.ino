/* 
Pneumatic Syringe System Master Test
This is the first working code (proof of concept) for the "mid master" of the system, 
currently using a Teensy LC.
The "mid master" obtains pressure data from the MPRLS pressure sensor and sends it to the "big master"
The "mid master" will also take commands from the "big master" and performs feedback control on the syringe system
*/

#include <i2c_t3.h>
#include <math.h>

// Function prototypes
void receiveEvent(size_t count);
void requestEvent(void);

//Create a timer callback
IntervalTimer pressure_timer;
IntervalTimer position_timer;

// Memory
#define MEM_LEN 32
char databuf_Rx[MEM_LEN];
char databuf_Tx[MEM_LEN];
char psi_cmd_raw[MEM_LEN]; //stores incomming float command temporarily
char pos_cmd_raw[MEM_LEN]; //stores incomming position command temporarily
char str[MEM_LEN];

// Constants
int count;
int pos_raw;
volatile float psi = 14.77;
float kp_psi = 400;
float ki_psi = 200;
float kd_psi = 0;
float pos = 50.00;
float kp_pos = 80;
float ki_pos = 5;
float kd_pos = 2;
volatile uint8_t received;
uint8_t target = 0x18; // target Slave address
uint8_t self = 0x68; //This should be different for each unit.
boolean frwd_flag;
boolean back_flag;
typedef struct {
    boolean flag;  //
    float val;  //
} unit_cmd;
unit_cmd pressure_cmd;


// Pin pefinition
#define MOTOR_PORT_A 3
#define MOTOR_PORT_B 4
#define BUTTON_BACK 14
#define BUTTON_FWRD 15
#define POT 16
#define LED_RED 9 
#define LED_GRE 10

void setup()
{
    pinMode(LED_BUILTIN,OUTPUT);    // LED
    digitalWrite(LED_BUILTIN,LOW);  // LED off
    pinMode(MOTOR_PORT_A,OUTPUT);   // Motor PWM pins
    pinMode(MOTOR_PORT_B,OUTPUT);   // Motor PWM pins
    pinMode(BUTTON_BACK,INPUT_PULLDOWN);
    pinMode(BUTTON_FWRD,INPUT_PULLDOWN);
    pinMode(LED_RED,OUTPUT);   // Top LED (red)
    pinMode(LED_GRE,OUTPUT);   // Bottom LED (green)
    pinMode(POT,INPUT);
    analogWrite(MOTOR_PORT_A, 0);
    analogWrite(MOTOR_PORT_B, 0);
    
    // Setup for Master mode, pins 18/19, external pullups, 400kHz, 200ms default timeout
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
    Wire.setDefaultTimeout(200000); // 200ms
    
    // Data init
    memset(databuf_Rx, 0, sizeof(databuf_Rx));
    count = 0;
    
    // Setup for Slave mode for data. Make sure the address is consistent at the master side!
    Wire1.begin(I2C_SLAVE, self, I2C_PINS_22_23, I2C_PULLUP_EXT, 400000);
    Wire1.setDefaultTimeout(200000); // 200ms
    
    // Register events
    Wire1.onReceive(receiveEvent);
    Wire1.onRequest(requestEvent);

    // Begin timer
    pressure_timer.begin(get_pressure, 50000);
    pressure_timer.priority(255);
//    position_timer.begin(get_pos, 50000);
//    position_timer.priority(254);

    // Turn Flags to false
    pressure_cmd.flag = false;
    
    Serial.begin(115200);   
}

void loop()
{
    if (pressure_cmd.flag == true){
        move_to_pressure(pressure_cmd.val);
    }

    frwd_flag = true;
    back_flag = true;
 
    float psi_copy;
    noInterrupts();
    psi_copy = psi;
    interrupts();
    get_pos();
//    Serial.print(pos);
//    Serial.print("\t");
    Serial.println(psi);
    
    if (pos_raw>1021 || psi < 1.00){
        back_flag = false;
        digitalWrite(LED_RED,HIGH);
    }
    else if (pos_raw<3 || psi > 25.00){
        frwd_flag = false;
        digitalWrite(LED_RED,HIGH);
    }
    else if (pos_raw<1021 && pos_raw>3 && psi < 25.00 && psi > 1.00){
        digitalWrite(LED_RED,LOW);
    }

    
    if (digitalRead(BUTTON_BACK)==HIGH && back_flag){
        move_motor(-255);
        digitalWrite(LED_GRE,HIGH);
        digitalWrite(LED_RED,LOW);
        //Serial.println("backward button pressed");
    } 
    else if (digitalRead(BUTTON_FWRD)==HIGH && frwd_flag){
        move_motor(255);
        digitalWrite(LED_GRE,HIGH);
        digitalWrite(LED_RED,LOW);
        //Serial.println("Forward button pressed");
    } 
    else {
        move_motor(0);
        //digitalWrite(LED_RED,LOW);
        digitalWrite(LED_GRE,LOW);
    }

    delay(10);                       // Delay to space out tests
}

///////////////////////////////////////////////////////////////////
//Function Declaration. Do not change unless it's necessary
///////////////////////////////////////////////////////////////////
//void test_function(){
//    test_val = test_val + 1.00;
//    Serial.println(test_val);
//}


float get_pressure(void){
    // Read string from Slave
    //
    digitalWrite(LED_BUILTIN,HIGH);   // LED on
    Wire.beginTransmission(target);
    Wire.write(0xAA); // command to read pressure
    Wire.write((byte)0x00);
    Wire.write((byte)0x00);
    Wire.endTransmission();
        
    // Read from Slave
    Wire.requestFrom(target, (uint8_t)4); // Read from Slave 

    Wire.read(); // First byte is status indication, so for now we get rid of it from the buffer
    uint32_t ret;
    ret = Wire.read();
    ret <<= 8;
    ret |= Wire.read();
    ret <<= 8;
    ret |= Wire.read();
    psi = (ret - 1677722) * 25;
    psi /= (float)(15099494 - 1677722);
    //Serial.println(psi);

    digitalWrite(LED_BUILTIN,LOW);    // LED off
    delay(10);
    return;
}

void get_pos(void){
    pos_raw = analogRead(POT);
    pos = -0.00000000000127508008831955*pow(pos_raw, 5)+0.00000000281124191931775*pow(pos_raw, 4)-0.00000234010387463214*pow(pos_raw, 3)+0.000894194580794215*sq(pos_raw)-0.176725701121183*pos_raw + 99.6115709415247+0.37;
    pos = round(pos);
}

// Motor forward/backward
void move_motor(int pwm_duty){
    if (pwm_duty >= 0){
        analogWrite(MOTOR_PORT_A, 0);
        analogWrite(MOTOR_PORT_B, pwm_duty);
    } else{
        analogWrite(MOTOR_PORT_A, -pwm_duty);
        analogWrite(MOTOR_PORT_B, 0);
    }
}


// "move to" functions
void move_to_pressure(float target_psi){
    float psi_copy;
    noInterrupts();
    psi_copy = psi;
    interrupts();

    Serial.print("move to pressure: ");
    Serial.println(target_psi);

    float error = target_psi - psi_copy;
    Serial.println(error);
    float prev_error = 0;
    float sum = error;
    float rate;
    int timeout = 0;
    get_pos();
    while (abs(error) >= 0.1 && timeout < 140){
        noInterrupts();
        psi_copy = psi;
        interrupts();
        Serial.print(psi_copy);
        error = target_psi - psi_copy;
        Serial.println(error);
        rate = (error-prev_error)/0.01;
        int duty = int(kp_psi * error + ki_psi * sum + kd_psi * rate);
        if (duty > 255){duty = 255;}
        else if (duty < -255){duty = -255;}
        if ((duty > 0 && pos == 100.00)||(duty < 0 && pos == 0.00)){break;}
        move_motor(duty);
        prev_error = error;
        timeout++;
        get_pos();
        delay(50);
    }
    pressure_cmd.flag = false;
    Serial.println("Done");
    return;
}
void move_to_position(float target_pos){
    noInterrupts();
    Serial.print("move to position: ");
    Serial.println(target_pos);
    get_pos();
    float error = target_pos - pos;
    float prev_error = 0;
    float sum = error;
    float rate;
    int timeout = 0;
    while (abs(error) > 0.00 && timeout < 1000){
        get_pos();
        error = target_pos - pos;
        Serial.println(error);
        rate = (error-prev_error)/0.01;
        int duty = int(kp_pos * error + ki_pos * sum + kd_pos * rate);
        if (duty > 255){duty = 255;}
        else if (duty < -255){duty = -255;}
        move_motor(duty);
        prev_error = error;
        timeout++;
        delay(10);
    }
    Serial.println("Done");
    return;
}


//buffer to float conversion
float cmd_to_float(){
    int i = 0;
    while (Wire1.available()) { // slave may send less than requested
        psi_cmd_raw[i] = Wire1.read(); // receive a byte as character
        i++;
    };
    String pos_raw_string = String(psi_cmd_raw);
    return pos_raw_string.toFloat();
}

//
// handle Rx Event (incoming I2C data) as slave
//
void receiveEvent(size_t count)
{     
    //Serial.println("RECEIVED");
    Wire1.read(databuf_Rx, 1);  // copy Rx data to databuf_Tx
    switch (databuf_Rx[0]){
        case 'L' :
            move_to_position(cmd_to_float());
            break;
        case 'P' :
            pressure_cmd.flag = true;
            pressure_cmd.val = cmd_to_float();
            break;
    }
}

//
// handle Tx Event (outgoing I2C data) as slave
//
void requestEvent(void)
{
    //Serial.println(String(psi)+String(pos));
    Serial.println("sending request");
    (String(psi)+String(pos)).getBytes(databuf_Tx, MEM_LEN);  //converts psi to string, then copies it to the data buffer.
    Wire1.write(databuf_Tx, MEM_LEN);
    Serial.println("sent request");
}
