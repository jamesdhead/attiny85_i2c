/* ATtiny85 as an I2C Master  Ex1          BroHogan                      1/21/11
 * I2C master reading DS1621 temperature sensor. (display with leds)
 * SETUP:
 * ATtiny Pin 1 = (RESET) N/U                      ATtiny Pin 2 = (D3) LED3
 * ATtiny Pin 3 = (D4) to LED1                     ATtiny Pin 4 = GND
 * ATtiny Pin 5 = SDA on DS1621                    ATtiny Pin 6 = (D1) to LED2
 * ATtiny Pin 7 = SCK on DS1621                    ATtiny Pin 8 = VCC (2.7-5.5V)
 * NOTE! - It's very important to use pullups on the SDA & SCL lines!
 * DS1621 wired per data sheet. This ex assumes A0-A2 are set LOW for an addeess of 0x48
 * TinyWireM USAGE & CREDITS: - see TinyWireM.h
 * NOTES:
 * The ATtiny85 + DS1621 draws 1.7mA @5V when leds are not on and not reading temp.
 * Using sleep mode, they draw .2 @5V @ idle - see http://brownsofa.org/blog/archives/261
 */

#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI

#define DS1621_ADDR   0x07              // 7 bit I2C address for DS1621 temperature sensor
#define LED1_PIN         4              // ATtiny Pin 3

byte send_buf;
String h = "Hello\n\r";

void setup(){
  OSCCAL = 0x53;
  pinMode(LED1_PIN,OUTPUT);
  Blink(LED1_PIN,2);                    // show it's alive
  TinyWireM.begin();                    // initialize I2C lib
}

void loop(){
  send_buf = 0;
  
  for(int i = 0; i < h.length(); i++) { 
    send_buf = h.charAt(i);
    if(send_buf != '\0') {
      TinyWireM.beginTransmission(DS1621_ADDR);
      TinyWireM.send(send_buf);                 // Access Command Register
      TinyWireM.endTransmission();
      Blink(LED1_PIN,3);
      delay(750);
    }
     }  // blink 10's of temperature on LED 1
  delay (4000);
}

void Blink(byte led, byte times){ // poor man's GUI
  for (byte i=0; i< times; i++){
    digitalWrite(led,HIGH);
    delay (100);
    digitalWrite(led,LOW);
    delay (30);
  }
}

