// debug mode
#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>

Serial_CAN can;

#define can_tx  2           // tx of serial can module connect to D2
#define can_rx  3           // rx of serial can module connect to D3

void setup()
{
    Serial.begin(9600);
    can.begin(can_tx, can_rx, 9600);      // tx, rx
}

void loop()
{
    can.debugMode();
}

// END FILE