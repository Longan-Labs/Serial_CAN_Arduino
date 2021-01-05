/* CONFIG SERIAL BAUDRATE EXAMPLE OF SERIAL CAN MODULE
   SUPPORT: joney.sui@longan-labs.cc
*/

#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>

Serial_CAN can;

#define can_tx  2           // tx of serial can module connect to D2
#define can_rx  3           // rx of serial can module connect to D3

void setup()
{
    Serial.begin(9600);
    while(!Serial);
    Serial.println("START to set the serial baud rate...");
    can.begin(can_tx, can_rx, 57600);      // tx, rx

    if(can.baudRate(SERIAL_RATE_57600))
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