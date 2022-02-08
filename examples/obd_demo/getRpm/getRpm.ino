/*************************************************************************************************
    OBD-II_PIDs TEST CODE
    Loovee, Longan Labs 2022

    Query
    send id: 0x7df
      dta: 0x02, 0x01, PID_CODE, 0, 0, 0, 0, 0

    Response
    From id: 0x7E9 or 0x7EA or 0x7EB
      dta: len, 0x41, PID_CODE, byte0, byte1(option), byte2(option), byte3(option), byte4(option)

    https://en.wikipedia.org/wiki/OBD-II_PIDs
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


void sendPid(unsigned char __pid) {
    unsigned char tmp[8] = {0x02, 0x01, __pid, 0, 0, 0, 0, 0};
    
#if STANDARD_CAN_11BIT
    can.send(CAN_ID_PID, 0, 0, 8, tmp);   // SEND TO ID:0X55
#else
    can.send(CAN_ID_PID, 1, 0, 8, tmp);   // SEND TO ID:0X55
#endif
}

bool getRPM(int *r)
{
    sendPid(PID_ENGIN_PRM);
    unsigned long __timeout = millis();

    while(millis()-__timeout < 1000)      // 1s time out
    {
        unsigned long id  = 0;
        unsigned char buf[8];

        if (can.recv(&id, buf)) {                // check if get data

            if(buf[1] == 0x41)
            {
                *r = (256*buf[3]+buf[4])/4;
                return 1;
            }
        }
    }

    return 0;
}

void setup() {
    Serial.begin(115200);
    while(!Serial);
    
    can.begin(can_tx, can_rx, 9600);      // tx, rx
    Serial.println("begin");
}

void loop() {

    int __rpm = 0;
    int ret = getRPM(&__rpm);
    if(ret)
    {
        Serial.print("Engin Speed: ");
        Serial.print(__rpm);
        Serial.println(" rpm");
    }
    delay(500);
}

// END FILE