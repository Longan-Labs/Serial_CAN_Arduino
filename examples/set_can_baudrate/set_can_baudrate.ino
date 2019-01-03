/* CONFIG CAN BUS BAUDRATE EXAMPLE OF SERIAL CAN MODULE
   No. of rate as bellow,
   #define CAN_RATE_5      1
   #define CAN_RATE_10     2
   #define CAN_RATE_20     3
   #define CAN_RATE_25     4
   #define CAN_RATE_31_2   5
   #define CAN_RATE_33     6
   #define CAN_RATE_40     7
   #define CAN_RATE_50     8
   #define CAN_RATE_80     9
   #define CAN_RATE_83_3   10
   #define CAN_RATE_95     11
   #define CAN_RATE_100    12
   #define CAN_RATE_125    13
   #define CAN_RATE_200    14
   #define CAN_RATE_250    15
   #define CAN_RATE_500    16
   #define CAN_RATE_666    17
   #define CAN_RATE_1000   18
   SUPPORT: joney.sui@longan-labs.cc
*/

#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>

Serial_CAN can;

#define can_tx  2           // tx of serial can module connect to D3
#define can_rx  3           // rx of serial can module connect to D2

void setup()
{
    Serial.begin(9600);
    can.begin(can_tx, can_rx, 9600);      // tx, rx

    if(can.canRate(CAN_RATE_500))
    {
        Serial.println("set can rate ok");
    }
    else
    {
        Serial.println("set can rate fail");
    }
}


unsigned long id = 0;
unsigned char dta[8];

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