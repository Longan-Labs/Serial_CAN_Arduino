/************************************************************************************************* 
  OBD-II_PIDs TEST CODE
  Joney @ Dec 2017
  
  Query
  send id: 0x7df
      dta: 0x02, 0x01, PID_CODE, 0, 0, 0, 0, 0
  Response
  From id: 0x7E9 or 0x7EA or 0x7EB
      dta: len, 0x41, PID_CODE, byte0, byte1(option), byte2(option), byte3(option), byte4(option)
      
  https://en.wikipedia.org/wiki/OBD-II_PIDs
  
  Input a PID, then you will get reponse from vehicle, the input should be end with '\n'
***************************************************************************************************/
#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
Serial_CAN can;

#define can_tx  2           // tx of serial can module connect to D2
#define can_rx  3           // rx of serial can module connect to D3

#define PID_ENGIN_PRM       0x0C
#define PID_VEHICLE_SPEED   0x0D
#define PID_COOLANT_TEMP    0x05

#define CAN_ID_PID          0x7DF

unsigned char PID_INPUT;
unsigned char getPid    = 0;

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

void set_mask_filt()
{
    /*
     * set mask, set both the mask to 0x3ff
     */
     
    if(can.setMask(mask))
    {
        Serial.println("set mask ok");
    }
    else
    {
        Serial.println("set mask fail");
    }
    
    /*
     * set filter, we can receive id from 0x04 ~ 0x09
     */
    if(can.setFilt(filt))
    {
        Serial.println("set filt ok");
    }
    else 
    {
        Serial.println("set filt fail");
    }
    
}

void sendPid(unsigned char __pid)
{
    unsigned char tmp[8] = {0x02, 0x01, __pid, 0, 0, 0, 0, 0};
    Serial.print("SEND PID: 0x");
    Serial.println(__pid, HEX);
    
    can.send(CAN_ID_PID, 0, 0, 8, tmp);   // SEND TO ID:0X55

}

void setup()
{
    Serial.begin(115200);
    can.begin(can_tx, can_rx, 9600);      // tx, rx
    
    // set baudrate of CAN Bus to 500Kb/s
    if(can.canRate(CAN_RATE_500))
    {
        Serial.println("set can rate ok");
    }
    else
    {
        Serial.println("set can rate fail");
    }
    
    set_mask_filt();
    
    Serial.println("begin");
    
}


void loop()
{
    taskCanRecv();
    taskDbg();
    
    if(getPid)          // GET A PID
    {
        getPid = 0;
        sendPid(PID_INPUT);
        PID_INPUT = 0;
    }
}

void taskCanRecv()
{
    unsigned char len = 0;
    unsigned long id  = 0;
    unsigned char buf[8];

    if(can.recv(&id, buf))                   // check if get data
    {
        Serial.println("\r\n------------------------------------------------------------------");
        Serial.print("Get Data From id: 0x");
        Serial.println(id, HEX);
        for(int i = 0; i<len; i++)          // print the data
        {
            Serial.print("0x");
            Serial.print(buf[i], HEX);
            Serial.print("\t");
        }
        Serial.println();
    }
}

void taskDbg()
{
    while(Serial.available())
    {
        char c = Serial.read();
        
        if(c>='0' && c<='9')
        {
            PID_INPUT *= 0x10;
            PID_INPUT += c-'0';
            
        }
        else if(c>='A' && c<='F')
        {
            PID_INPUT *= 0x10;
            PID_INPUT += 10+c-'A';
        }
        else if(c>='a' && c<='f')
        {
            PID_INPUT *= 0x10;
            PID_INPUT += 10+c-'a';
        }
        else if(c == '\n')      // END
        {
            getPid = 1;
        }
    }
}
// END FILE