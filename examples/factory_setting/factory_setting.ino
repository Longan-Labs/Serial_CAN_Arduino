// FACTORY SETTING
// SERIAL BAUDRATE: 9600
// CAN BUS BAUDRATE: 500Kb
// MASK0: 0X00
// MASK1: 0X00
// FILT0~FILT5: 0X00
// SUPPORT: joney.sui@longan-labs.cc
#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>

Serial_CAN can;

#define can_tx  2           // tx of serial can module connect to D2
#define can_rx  3           // rx of serial can module connect to D3


void setup()
{
    Serial.begin(9600);
    while(!Serial);
    
    Serial.println("BEGIN FACTORY SETTING...");
    
    can.begin(can_tx, can_rx, 9600);      // tx, rx

    if(can.factorySetting())
    {
        Serial.println("\r\nFACTORY SETTING OK");
    }
    else
    {
        Serial.println("\r\nFACTORY SETTING FAIL");
    }

    // now you can replug your serial can bus module see if factory setting correctly. 
}

void loop()
{
    //can.debugMode();
}

// END FILE