# Match the numbers
## A game using a 128x64 OLED screen, Arduino UNO and a push button.
    
This contains a sketch for a game named **Match the Numbers**. The
OLED screen is split into two parts - left and right. A number remains
fixed on the left side of the screen, while another numbers keeps
ticking away on the right side of the screen. The objective is to
press the push-button when both the numbers match.
    
Every correct answer takes the player to the next level, where the
speed with which the number on the right ticks away is greater than
the previous level.
    
Every wrong answer, and the player loses a life.
    
The objective is to clear all 10 levels.
    

### Wiring Details

Connect a push-button to PIN 2 of the Arduino via a pull-down
resistor.

Connect the VCC and GND of the OLED display to the +ve and -ve rails
of the breadboard respectively.

Connect SCK of the OLED display to Arduino PIN A5.
Connect SDA of the OLED display to Arduino PIN A4.

Don't forget to connect the +ve rail to the VCC of the Arduino and the
-ve rail of the breadboard to the GND of the Arduino!

Have fun!
