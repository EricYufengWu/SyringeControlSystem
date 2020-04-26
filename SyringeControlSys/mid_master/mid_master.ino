/* 
Pneumatic Syringe System Master Test
This is the first working code (proof of concept) for the "mid master" of the system, 
currently using a Teensy LC.
The "mid master" obtains pressure data from the MPRLS pressure sensor and sends it to the "big master"
The "mid master" will also take commands from the "big master" and performs feedback control on the syringe system
*/

#include <i2c_t3.h>

// Function prototypes
void receiveEvent(size_t count);
void requestEvent(void);

// Memory
#define MEM_LEN 32
char databuf_1[MEM_LEN];
char databuf_2[MEM_LEN];

// Constants
int count;
float psi = 14.77;
volatile uint8_t received;
uint8_t target = 0x18; // target Slave address
#define MOTOR_PORT_A 3
#define MOTOR_PORT_B 4
#define BUTTON_BACK 14
#define BUTTON_FWRD 15
#define POT 16
#define LED_TOP 9 
#define LED_BOT 10

void setup()
{
    pinMode(LED_BUILTIN,OUTPUT);    // LED
    digitalWrite(LED_BUILTIN,LOW);  // LED off
    pinMode(MOTOR_PORT_A,OUTPUT);   // Motor PWM pins
    pinMode(MOTOR_PORT_B,OUTPUT);   // Motor PWM pins
    pinMode(BUTTON_BACK,INPUT_PULLDOWN);
    pinMode(BUTTON_FWRD,INPUT_PULLDOWN);
    pinMode(LED_TOP,OUTPUT);   // Top LED (red)
    pinMode(LED_BOT,OUTPUT);   // Bottom LED (green)
    
    //pinMode(POT,INPUT);
    analogWrite(MOTOR_PORT_A, 0);
    analogWrite(MOTOR_PORT_B, 0);
    
    // Setup for Master mode, pins 18/19, external pullups, 400kHz, 200ms default timeout
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
    Wire.setDefaultTimeout(200000); // 200ms
    
    // Data init
    memset(databuf_1, 0, sizeof(databuf_1));
    count = 0;
    
    // Setup for Slave mode for data. Make sure the address is consistent at the master side!
    Wire1.begin(I2C_SLAVE, 0x67, I2C_PINS_22_23, I2C_PULLUP_EXT, 400000);
    Wire1.setDefaultTimeout(200000); // 200ms
    // register events
    Wire1.onReceive(receiveEvent);
    Wire1.onRequest(requestEvent);

    Serial.begin(115200);
      
}

void loop()
{
    Serial.print(analogRead(POT));
    Serial.print("\t");
    write_pressure();
//    delay(10);                       // Delay to space out tests
    while (analogRead(POT)>1021 || analogRead(POT)<3){
        if (analogRead(POT)>1022){     //1023 faces torwards the motor side
            move_forward(50);
        } else{
            move_backward(50);
        }
    }
    if (digitalRead(BUTTON_BACK)==HIGH || psi > 25.00){
        move_backward(255);
        digitalWrite(LED_BOT,HIGH);
        Serial.println("backward button pressed");
    } 
    else if (digitalRead(BUTTON_FWRD)==HIGH && psi < 25.00){
        move_forward(255);
        digitalWrite(LED_TOP,HIGH);
        Serial.println("Forward button pressed");
    } 
    else {
        stop_motor();
        digitalWrite(LED_TOP,LOW);
        digitalWrite(LED_BOT,LOW);
    }

}



void write_pressure(void){
 
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
    Serial.println(psi);

    digitalWrite(LED_BUILTIN,LOW);    // LED off

    delay(10);
}

// Motor forward/backward
void move_forward(int pwm_duty){
    analogWrite(MOTOR_PORT_A, 0);
    analogWrite(MOTOR_PORT_B, 255);
}
void move_backward(int pwm_duty){
    analogWrite(MOTOR_PORT_A, 255);
    analogWrite(MOTOR_PORT_B, 0);
}
void stop_motor(void){
    analogWrite(MOTOR_PORT_A, 0);
    analogWrite(MOTOR_PORT_B, 0);
}

//
// handle Rx Event (incoming I2C data) as slave
//
void receiveEvent(size_t count)
{
    Wire1.read(databuf_2, count);  // copy Rx data to databuf_2
    received = count;           // set received flag to count, this triggers print in main loop
}

//
// handle Tx Event (outgoing I2C data) as slave
//
void requestEvent(void)
{
    String(psi).getBytes(databuf_2, MEM_LEN);  //converts psi to string, then copies it to the data buffer.
    Wire1.write(databuf_2, MEM_LEN);
}
