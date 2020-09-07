#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
 * Wiring :
 * Push button connected via  pull-down resistor to Arduino Pin 2.
 * 
 * 128x64 i2c OLED display. SCL connected to A5. SDA connected to A4.
 */
 
/* Button connection to Arduino */
/* NOTE!!! Do not connect button to PIN 4. The behaviour becomes undefined for some reason */
#define BUTTON 2

#define NUM_VALUES 10

#define SCREEN_HEIGHT  64
#define SCREEN_WIDTH  128

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* Helper function to display the numbers side-by-side on the OLED separated by a vertial line in the middle. */
void show_numbers(int lucky_number, int cur_number)
{
  display.clearDisplay();
  
  display.setTextSize(5.0);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(22, 16);
  display.println(lucky_number);

  display.drawLine(64, 0, 64, 127, SSD1306_WHITE);

  display.setCursor(86, 16);
  display.println(cur_number);

  display.display();
}

#define YES 1
#define NO 0

/* TIMEOUT is the maximum time it takes for the numbers on the OLED screen to tick-away. 
 *  We set it to 1 second.
 */
#define TIMEOUT 1000

/* Helper function to determine if a button is clicked.
 *  If it was clicked, the function will wait until the button has been released before
 *  returning the value that it was Clicked.
 */
int isButtonClicked(int button)
{
  int value = digitalRead(button);
  if (!value)
    return NO;

  Serial.println("Button Pressed. Waiting for release\n");
  while(digitalRead(button))
    ;
  Serial.println("Button released!");
  return YES;
}


/* Maximum number of lives for the user */
#define MAX_ATTEMPTS 5

int lucky_number = 7; // This is the number that the user needs to match.
int state = 0; // The current number on the right-side.
int paused = 1; //Indicates if the button is in a paused state.
int timeout = TIMEOUT; //Variable to keep track of the timeout for the current epoch
int count = timeout;  //Variable to keep track of the amount of time that is pending in the current epoch
int started = 0; //If the new round is started or not.
int stopped = 0; //If the game has been stopped or not.
int failed_attempts = 0; //Number of strikes so far.
int decrement = 100; //Amount by which to decrement the timeout, each time the user gets a correct answer.
int level = 1; //The current level.

#define SUCCESS 1
#define FAILURE 0
/*
 * Helper function to evaluate if the number on the 7-segment display when the button was pressed
 * is the lucky number
 */
int evaluate(int cur_state)
{
   if (cur_state == lucky_number)
    return SUCCESS;
   return FAILURE;
}


void successIndication(void)
{

  display.clearDisplay();
  
  display.setTextSize(2.0);
  display.setTextColor(SSD1306_WHITE);

  for (int i = 0; i < 3; i++) {
    display.setCursor(16, 20);
    display.println("CORRECT!!");
    display.display();
    delay(500);
    display.clearDisplay();
    display.display();
    delay(500);
  }
}

/*
 * Helper function to indicate an incorrect attempt.
 */
int failureIndication(int failed_attempts)
{

  display.clearDisplay();
  
  display.setTextSize(2.0);
  display.setTextColor(SSD1306_WHITE);

  for (int i = 0; i < 2; i++) {
    display.setCursor(22, 20);
    display.println("WRONG!!!");
    display.display();
    delay(500);
    display.clearDisplay();
    display.display();
    delay(500);
  }

  failed_attempts++;

  return failed_attempts;
}

/* Helper function to show how many lives are left */
int show_lives_left(int failed_attempts, int max_attempts)
{
  display.clearDisplay();
  
  display.setTextSize(2.0);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(64, 12);
  display.println(max_attempts - failed_attempts);
  display.setCursor(0, 30); 
  display.print("LIVES LEFT");
  display.display();
}

void gameOverIndication()
{
  display.clearDisplay();
  
  display.setTextSize(2.0);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(4, 30);
  display.println("GAME OVER!");
  display.display();
}

/* Helper function called when the player has cleared all 10 levels */
void WinIndication()
{
  display.clearDisplay();
  
  display.setTextSize(2.0);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println("YOU WIN!!");
  display.display();
  
}

/* Helper function to show the current level */
void showLevel(int level)
{
  display.clearDisplay();
  //show_numbers(lucky_number, state);
  display.setTextSize(2.0);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(16, 0);
  display.print("LEVEL  ");
  display.println(level);
  display.setCursor(16, 20);
  display.println("CLICK");
  display.setCursor(16, 40);
  display.println("TO PLAY");
  display.display();
  
}


void setup() {
  pinMode(BUTTON, INPUT);
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showLevel(level);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

    
  while (count) {
   if (isButtonClicked(BUTTON)) { 
      paused = (paused + 1) % 2;//The button toggles between two states - Paused, Running
    }

    if (stopped && paused) { //The game has been stopped and the button is in the paused state.
      return;                //Nothing to do.
    }
    
    if (stopped && !paused) { //The user has clicked the button, while it was in stopped state. 
      stopped = 0;            // Reset the state of the game.
      timeout = TIMEOUT;
      count = timeout;
      failed_attempts = 0;
      state = 0;
      level = 1;
      return;
    }

    if (started && paused) { //The user pressed a button while the numbers were running. Evaluate what if the user stopped at the correct moment.
      started = 0;
      int result = evaluate(state);
      
      if (result == SUCCESS) {
        successIndication();
        timeout = timeout - decrement;
        if (timeout < 100) { // User has succeeded at all levels. 
          WinIndication();
          timeout = TIMEOUT;
          count = timeout;
          stopped = 1;
          level = 1;
          return;
        }
        
        count = timeout; //Replenish the timeout
        int new_number = random(0, 10); //Get a new number
        if (new_number == lucky_number) // Ensure it isn't the same as the previous
          new_number = (new_number + 4) % 10;
        lucky_number = new_number;
        level++;
        showLevel(level);
        return;
      } else { //The user failed to click the button at the right time.
        failed_attempts = failureIndication(failed_attempts); //Show failure indication
        show_lives_left(failed_attempts, MAX_ATTEMPTS);
        if (failed_attempts >= MAX_ATTEMPTS) { //All attempts exhausted
          gameOverIndication();
          timeout = TIMEOUT;
          failed_attempts = 0;
          state = 0;
          return;
        }
        return;

      }
    } else if (!started && !paused) { //The user pressed the button while the numbers were paused. Start the new epoch
      started = 1;
      count = timeout;
    } else if (!started && paused) { //The user has not pressed the button since the last pause. Do nothing
      return; 
    }
    
    // Here the epoch has started and the user hasn't paused yet. So count-down.
    count--;

    if (count == 0) { // Change the ticking number on the OLED screen to the next one.
       state = (state + 1) % NUM_VALUES;
       show_numbers(lucky_number, state);
       count = timeout;
    }

    delay(1);
  }

}
