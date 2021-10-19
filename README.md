# WeedPot
Arduino code for a smart pot

Author: RADULESCU Florin
Introduction

Brief presentation of the project:

    Smart pots that help grow plants in good condition
    The sensors measure the environmental conditions (soil moisture in the pot, the level of ambient light intensity, the water level at the base of the pot), which are then sent by the microcontroller to an IoT platform via a Wi-Fi module.
    The data are interpreted within the Matlab language platform and sent by e-mail in the form of graphs from the last hours

The project idea started from one of my plants, very difficult to grow, which I always have to take care of to ensure enough water, soil moisture and light.

Wikipedia link for the plant species in question: https://ro.wikipedia.org/wiki/Dionaea_muscipula

Hardware Design

Component:

    Arduino UNO R3 (ATmega328p + ATmega16u2)
    1 generic breadboard for the intermediation between Arduino and the rest of the electrical components
    1 mini breadboard used in the safe feeding set-up
    ESP8266 Wi-Fi module
    Analog module with soil moisture measurement sensor
    Analog mode with water level sensor
    Analog / digital module with sensor for measuring the intensity level of the ambient world
    Mother-to-mother wires for connections
    Dad-dad wires for connections
    1Kohmi resistors for a voltage divider
    9V battery to power the entire circuit
    A plastic tube support that protects the base plate and the main breadboard
    A plastic support in the shape of a pyramid trunk without a base for pots, water and sensors

Wiring diagram (click on the image to see the original size version of the wiring diagram):

To power the RX pin of the Wi-Fi module you can see the need to use a voltage divider, as a 5V power supply from Arduino would have had too high a voltage and would have fried the Wi-Fi mode, and one from 3.3V all from Arduino would not have had the current intensity high enough for the Wi-Fi mode to work in normal settings.

The voltage divider consists of two 1Kohmi resistors connected in parallel with the power supply to the RX pin of the Wi-Fi module from a digital pin on the Arduino. The installation reduces the voltage that reaches the Wi-Fi mode to 3.3V without affecting the current intensity in the connection.

To safely power the circuit, the 9V battery is not connected directly to the basic breadboard, but through a 1m extension to a mini-breadboard. I made this decision because due to a wire management error I managed to turn on the power supply for a few seconds and I don't want this to happen in the vicinity of the main assembly.

Software Design

List of parts of the code:

    Main Arduino code for receiving data and turning on / off the power supply of modules with integrated sensors
        Setting and starting the power supply of the pins intended for sensors
        Reading the data received from the sensors and saving them in variables
        Turn off the sensor power supply for a set period of time
        Restart the sensor power supply at the end of the period
        Repeat the read-stop-restart steps at regular intervals
    Communication with the Wi-Fi module and data transmission using special libraries for the module
        Initialize Wi-Fi connection parameters (network name, password)
        Initialize connection parameters to ThingsSpeak (data channel, APIkey)
        Connect to the Wi-Fi network and the ThingsSpeak platform
        Send read values ​​from sensors to ThingsSpeak
        Turn off the power to the module for a period of time to reduce power consumption
    Matlab code within the ThingSpeak platform for interpreting received data
        Parsing the data received on the communication channels
        Interpretation and plotting of data in the form of graphs

In order to be able to use and program the ESP8266 Wi-Fi module, it is necessary to install specific libraries within the Arduino IDE application. A tutorial in this regard (also contains the video version and instructions for mounting and testing the functionality) can be found here.

The sensor modules are powered from digital pins, so that they can be activated only when needed, to make some measurements, then they are deactivated. This practice aims to generate both lower power consumption and extend the life of the sensors (for example, the cathode of the soil moisture sensor tends to erode as long as the sensor is powered, but this does not happen when it does not receives current).

The ESP8266 Wi-Fi module does not require a power outage from the Arduino to reduce power consumption. It can be configured to enter DeepSleep mode by itself through dedicated library functions.

Obtained results

Never allow VCC and GND to touch: it may catch fire! When removing the wires from the circuit, be sure to remove the ones directly connected to the battery first to avoid an unwanted supply of an unsafe portion! Do not leave wires in the air while they are connected to the power supply!

Bibliography / Resources

    Safe use and programming of the ESP8266 module: https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/
    ThingSpeak online platform for IoT devices: https://thingspeak.com/
    Datasheet ATmega328P: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
    Export to PDF: https://ocw.cs.pub.ro/courses/pm/prj2021/abirlica/weedpot?do=export_pdf
