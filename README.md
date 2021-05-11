# Longan Labs Serial CAN Bus Module Library

[![Actions Status](https://github.com/arduino/arduino-cli-example/workflows/test/badge.svg)](https://github.com/arduino/arduino-cli-example/actions)
[![Spell Check](https://github.com/arduino/compile-sketches/workflows/Spell%20Check/badge.svg)](https://github.com/arduino/compile-sketches/actions?workflow=Spell+Check)
[![codecov](https://codecov.io/gh/arduino/compile-sketches/branch/main/graph/badge.svg?token=Uv6f1ebMZ4)](https://codecov.io/gh/arduino/compile-sketches)

The Serial CAN Bus module provides your Arduino with CAN Bus capabilities and allows you to hack your vehicle. It lets you to read and write messages to the CAN Bus. The Serial CAN Bus module can be connected to your Arduino through the on-board Grove connector.

CAN Bus is a messaging protocol system that lets various microcontrollers and sensors within a vehicle to talk to each other. CAN provides long distance, medium communication speed, and high reliability.

The Serial CAN Bus module is based on MCP2515 CAN controller and MCP2551 CAN transceiver provides speed up to 1Mb/s. It also has a terminal block so you can connect to your vehicle’s OBD-II port with two wires.

With this library, you can,

1. Send a CAN2.0 frame
2. Receive a CAN2.0 frame
3. Get data from OBD-II
4. Set the masks and filters, there're 32 masks and filters. 

## Installation

1. [Download the library](https://github.com/Longan-Labs/Serial_CAN_Arduino/archive/refs/heads/master.zip)
2. Extract the zip file
3. In the Arduino IDe, navigate to Sketch > Include Library > Add .ZIP Library

## Respository Contents

* [**/examples**](./examples) - Example sketches for the library (.ino). Run these from the Arduino IDE.
* [**/src**](./src) - Source files for the library (.cpp, .h).
* [**keywords.txt**](./keywords.txt) - Keywords from this library that will be highlighted in the Arduino IDE.
* [**library.properties**](./library.properties) - General library properties for the Arduino package manager.

## Functions

- begin()
- send()
- recv()
- canRate()
- baudRate()
- setMask()
- setFilt()
- factorySetting()
- debugMode()

## Examples

here are many examples implemented in this library. One of the examples is below. You can find other examples [here](./examples)

```Cpp
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
```

## Get a Dev Board

If you need a Dev board, plese try,

- [Serial CAN Bus Module](https://www.longan-labs.cc/1030001.html)

You can get others CAN Dev board below,

- [CAN Bus Shield for Arduino](https://www.longan-labs.cc/1030016.html)
- [CANBed V1](https://www.longan-labs.cc/1030008.html)
- [CANBed M0](https://www.longan-labs.cc/1030014.html)
- [OBD-II CAN Bus GPS Dev Kit](https://www.longan-labs.cc/1030003.html)

## License

```
MIT License

Copyright (c) 2018 @ Longan Labs

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## Contact us

If you have any question, please feel free to contact [support@longan-labs.cc](support@longan-labs.cc)


[![Analytics](https://ga-beacon.appspot.com/UA-101965714-1/Longan_CANFD)](https://github.com/igrigorik/ga-beacon)
