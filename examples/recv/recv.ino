// RECV EXAMPLE OF SERIAL CAN MODULE
// unsigned char recv(unsigned long *id, uchar *buf);
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

unsigned long id = 0;
unsigned char dta[8];

// send(unsigned long id, byte ext, byte rtrBit, byte len, const byte *buf);
void loop()
{
    if(can.recv(&id, dta))
    {
        Serial.print("GET DATA FROM ID: ");
        Serial.println(id);
        for(int i=0; i<8; i++)
        {
            Serial.print("0x");
            Serial.print(dta[i], HEX);
            Serial.print('\t');
        }
        Serial.println();
    }
}

// END FILE