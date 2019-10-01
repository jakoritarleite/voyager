# Follower Line Car

Just a car made with Arduino Nano to follow the white line. Depending of the version I'll PID to control it, but I don't really know.
*I pretend to add an AI to learn and choose the best values to the car but just in the future.*

>  I'll add how to pin everything in arduino with this project but for now I just have how to do that with bluetooth.

**Use bluetooth in Arduino with Python:**


**1.**  You need to connect bluetooth tx, rx, vcc and gnd to arduino "ports". Same as the following scheme:

![BluetoothArduinoScheme](http://arduinolearning.com/wp-content/uploads/2016/05/arduino-and-hc05_bb.png)

**2.**  Now you need to configure the code at your arduino:

```c++
#include <SoftwareSerial.h> //Use this to add bluetooth lib
int pinRX = 0; //Set pinRX to 0(Same as arduino port you'll use)
int pinTX = 1; //Set pinTX to 1
SoftwareSerial Bluetooth(pinRX, pinTX); //"Configure the bluetooth to use pins 0 and 1"
```

**3.** Now switch to python to configure everything.

[![Python Version][python-image]][python-url]

```python
from bluetooth import *
nearby = discover_devices(lookup_names = True)

for name, addr in nearby:
		print("{} . {}". format(addr, name))

address = input(str(f"[>] "))

sock = BluetoothSocket( RFCOMM )
sock.connect((address, 1))

while True:
    data = sock.recv(2**10)
    print(data)

```


[python-image]: https://img.shields.io/pypi/pyversions/3?color=orange&style=flat-square
[python-url]: https://www.python.org/downloads/release/python-374/