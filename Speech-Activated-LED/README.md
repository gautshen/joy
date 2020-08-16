## Speech Activated RGB LED
    
This contains the Juptyer Notebook with the Python code for lighting
up an RGB Anode LED connected to an Arduino UNO board, based on
voice-commands.
    
This uses the speech_recognition Python module which picks up the
commands from the Microphone and parses them using the
recognize_google() API. On parsing the text, it checks if any specific
colours are mentioned. In that case, the Python program sends a Byte
to the serial port of the Arduino which encodes the colour to light up
the LED with.
    
The Arduino sketch simply listens on the Serial port. When there is
something to be read, it will read the byte sent by the Python
program, and then based on the value of the Byte, it will light up the
Common-Anode RGB LED.


Wiring Diagram
=================
```
    3   5V   5   6
    *   *    *   *
    |   |    |   |
    Rs  |   Rs   Rs
    |   |    |   |
 ---|---|----|---|--------
    R   A    G   B       
   (Common Anode LED)    
 -------------------------
```

**Legend**:
Rs: 220 Ohm 1/4 Watt Resistor

3 : Pin 3 of Arduino UNO

5 : Pin 5 of Arduino UNO

6 : Pin 6 of Arduino UNO

R : Red Pin of the RGB LED

A : Common-Anode Pin of the RGB LED

G : Green Pin of the RGB LED

B : Blue Pin of the RGB LED

Rest of the code is self-explanatory.
