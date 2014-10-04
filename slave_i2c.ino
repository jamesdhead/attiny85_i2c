/* ATtiny85 as an I2C Slave            BroHogan                           1/12/11
 * Example of ATtiny I2C slave receiving and sending data to an Arduino master.
 * Gets data from master, adds 10 to it and sends it back.
 * SETUP:
 * ATtiny Pin 1 = (RESET) N/U                      ATtiny Pin 2 = (D3) N/U
 * ATtiny Pin 3 = (D4) to LED1                     ATtiny Pin 4 = GND
 * ATtiny Pin 5 = I2C SDA on DS1621  & GPIO        ATtiny Pin 6 = (D1) to LED2
 * ATtiny Pin 7 = I2C SCK on DS1621  & GPIO        ATtiny Pin 8 = VCC (2.7-5.5V)
 * NOTE! - It's very important to use pullups on the SDA & SCL lines!
 * Current Rx & Tx buffers set at 32 bytes - see usiTwiSlave.h
 * Credit and thanks to Don Blake for his usiTwiSlave code. 
 * More on TinyWireS usage - see TinyWireS.h
 */


#include "TinyWireS.h"                  // wrapper class for I2C slave routines

//#include <TinyDebugSerial.h>
//TinyDebugSerial mySerial = TinyDebugSerial();

#include <SoftwareSerial.h>
SoftwareSerial mySerial(-1,3);



#define I2C_SLAVE_ADDR  0x07            // i2c slave address (38)
#define LED1_PIN         4              // ATtiny Pin 3

void setup(){
  OSCCAL = 0x36;                        // ATtiny85
  pinMode(LED1_PIN,OUTPUT);             // for general DEBUG use
  Blink(LED1_PIN,2);                    // show it's alive
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
  mySerial.begin(9600);
  mySerial.println("Hello, world?"); 
}


void loop(){
  byte byteRcvd = 0;
  char c = 0;
  if (TinyWireS.available()){           // got I2C input!
    byteRcvd = TinyWireS.receive();     // get the byte from master
    Blink(LED1_PIN,3);
    c = byteRcvd;                      // master must wait for this to finish before calling Wire.requestFrom
    mySerial.print(c);
  }
}

void Blink(byte led, byte times){ // poor man's display
  for (byte i=0; i< times; i++){
    digitalWrite(led,HIGH);
    delay (100);
    digitalWrite(led,LOW);
    delay (30);
  }
}

