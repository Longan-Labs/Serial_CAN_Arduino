/* 
  CONFIG SERIAL BAUDRATE EXAMPLE OF SERIAL CAN MODULE
  SUPPORT: support@longan-labs.cc
*/

#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>

Serial_CAN can;

#define can_tx  2       // tx of serial can module, the yellow cable
#define can_rx  3       // rx of serial can module, the white cable

void setup()
{
    Serial.begin(9600);
    while(!Serial);
    Serial.println("START to set the serial baud rate...");
    can.begin(can_tx, can_rx, 9600);      // set this baudrate to the current baudrate

    if(can.baudRate(SERIAL_RATE_38400))     // SERIAL_RATE_9600, SERIAL_RATE_19200, SERIAL_RATE_38400
    {
        Serial.println("set baud rate ok");
    }
    else
    {
        Serial.println("set baud rate fail");
    }
}


void loop()
{

}


// END FILE
