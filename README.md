# RPI UHF-RFID

This repository contains a few small programs used to test components of an RFID ticketing system on a Raspberry PI 4B.

## Libraries

[ThingMagic Mercury API](https://www.jadaktech.com/products/thingmagic-rfid/thingmagic-mercury-api/) - Designed to control every aspect of ThingMagic RFID readers through various commands, including: Advanced Read Functionality, Advanced Tag Operations, Privacy and Security and Performance, and Memory Optimization.

[PiGPIO](https://abyz.me.uk/rpi/pigpio/) - A Raspberry Pi library which allows control of the General Purpose Input Outputs (GPIO).

## Installation

Instructions for compiling the Mercury API can be found [here](https://www.jadaktech.com/products/thingmagic-rfid/thingmagic-mercury-api/). Scroll down to Support Documentation and look for ThingMagic Mercury API Compilation under User Manuals, Guides & Drawings.

Instructions for hooking up the RFID reader can be found [here](https://learn.sparkfun.com/tutorials/simultaneous-rfid-tag-reader-hookup-guide/all).


## Materials Used

[Raspberry Pi 4B](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)

[SparkFun Simultaneous RFID Reader - M6E Nano](https://www.sparkfun.com/products/14066) - UHF RFID Reader

[SparkFun Serial Basic Breakout - CH340G](https://www.sparkfun.com/products/14050) - USB-to-Serial adapter which allows RPI to connect to reader via USB

[Super-bright 5mm IR LED - 940nm](https://www.adafruit.com/product/387?gclid=CjwKCAjw7--KBhAMEiwAxfpkWL_GouOGbUwtxk4ekROBLFYxH7ntr63XdovG1E-UPKBHUviJtRKxhhoCprcQAvD_BwE) - IR LED for break beam

[IR Receiver Diode - TSOP38238](https://www.sparkfun.com/products/10266) - IR Receiver for break beam

#### The following are optional and were used to increase tag read distance for the RFID reader

[UHF RFID Antenna (RP-TNC)](https://www.sparkfun.com/products/14131) - Antenna to increase read distance

[Interface Cable for RP-TNC to RP-SMA](https://www.sparkfun.com/products/14132) - Male RP-TNC to Male RP-SMA cable to connect reader to antenna

[Interface Cable RP-SMA to U.FL](https://www.sparkfun.com/products/662) - Adapter for board/antenna connection
