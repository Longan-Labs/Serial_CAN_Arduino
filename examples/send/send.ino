// SEND EXAMPLE OF SERIAL CAN MODULE
// unsigned char send(unsigned long id, uchar ext, uchar rtrBit, uchar len, const uchar *buf);
// SUPPORT: joney.sui@longan-labs.cc
#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>

Serial_CAN can;

#define can_tx  2           // tx of serial can module connect to D2
#define can_rx  3           // rx of serial can module connect to D3

void setup()
{
    Serial.begin(9600);
    can.begin(can_tx, can_rx, 9600);      // tx, rx
    Serial.println("begin");
}

unsigned char dta[8] = {1, 2, 3, 4, 5, 6, 7, 8};

// send(unsigned long id, byte ext, byte rtrBit, byte len, const byte *buf);
void loop()
{
    can.send(0x55, 0, 0, 8, dta);   // SEND TO ID:0X55
    delay(100);
}

// END FILE