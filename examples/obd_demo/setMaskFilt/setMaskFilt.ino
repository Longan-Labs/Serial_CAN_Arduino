/*************************************************************************************************
    setting for the OBD demos
    Loovee, Longan Labs 2022
***************************************************************************************************/

#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>

#define STANDARD_CAN_11BIT      1       // That depands on your car. some 1 some 0. 

Serial_CAN can;

#define can_tx  2       // tx of serial can module, the yellow cable
#define can_rx  3       // rx of serial can module, the white cable

#define PID_ENGIN_PRM       0x0C
#define PID_VEHICLE_SPEED   0x0D
#define PID_COOLANT_TEMP    0x05

#if STANDARD_CAN_11BIT
#define CAN_ID_PID          0x7DF
#else
#define CAN_ID_PID          0x18db33f1
#endif

#if STANDARD_CAN_11BIT
unsigned long mask[4] = 
{
    0, 0x7FC,                // ext, maks 0
    0, 0x7FC,                // ext, mask 1
};

unsigned long filt[12] = 
{
    0, 0x7E8,                // ext, filt 0
    0, 0x7E8,                // ext, filt 1
    0, 0x7E8,                // ext, filt 2
    0, 0x7E8,                // ext, filt 3
    0, 0x7E8,                // ext, filt 4
    0, 0x7E8,                // ext, filt 5
};

#else
unsigned long mask[4] =
{
    1, 0x1fffffff,               // ext, maks 0
    1, 0x1fffffff,
};
 
unsigned long filt[12] =
{
    1, 0x18DAF110,                // ext, filt
    1, 0x18DAF110,                // ext, filt 1
    1, 0x18DAF110,                // ext, filt 2
    1, 0x18DAF110,                // ext, filt 3
    1, 0x18DAF110,                // ext, filt 4
    1, 0x18DAF110,                // ext, filt 5
};
#endif



void setup() {
    Serial.begin(115200);
    while(!Serial);
    
    can.begin(can_tx, can_rx, 38400);      // tx, rx

    Serial.println(can.canRate(CAN_RATE_500) ? "set can rate ok" : "set can rate fail");
    Serial.println(can.setMask(mask) ? "set mask ok" : "set mask fail");
    Serial.println(can.setFilt(filt) ? "set filt ok" : "set filt fail");
}

void loop() {

}

// END FILE