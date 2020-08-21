/*
 * Match-the-Number!
 * 
 * Objective: A Number will appear on the Serial console of the Arduino. 
 *            The seven-segment display will keep showing numbers from 0-9 repeatedly at a certain frequency
 *            Objective is to click the button when the number on the 7-segment matches 
 *            the number on the Serial Console.
 *            
 *            On a correct match, the Green LED glows. A new number appears on the Serial Console. 
 *               - The frequency with with the numbers appear on the 7-segment display increases
 *            On an incorrect match, the Red LED glows to indicate 1 strike.
 *            
 *            5 strikes, and the 7-Segment display shows E,n,d.
 * 
 */

/*
 *                                               -|-|---|--|-|--  
 *              |----A----|                      |G F Comm A B |
 *              F         B                      |             |
 *              |         |                      |             |
 *              |----G----|                      |             |
 *              |         |                      |             |
 *              E         C                      |             |
 *              |----D----| DP                   |E D Comm C Dp|
 *                                               -|-|--|---|-|--
 */

/*   7-Segment Display connection to Arduino */
#define COM    12
#define A_PIN  11
#define B_PIN  10
#define C_PIN  9
#define D_PIN  8
#define E_PIN  7
#define F_PIN  6
#define G_PIN  5

/*   Button connection to Arduino */
#define BUTTON 4

/* Green and Red LEDs connection to Arduino */
#define GREEN_LED 3
#define RED_LED 2

/* Numbers to print on 7-segment display [0-9] */
#define NUM_VALUES 10

/* Since we are using a common Anode 7-segment display, the Common-Anode, "Comm" will have a positive signal.
 * Thus the A,B,C,D,E,F,G segments need to be sent a LOW to make them lightup, and HIGH to make turn them off.
 * 
 * Use #macros ANODE_HIGH and ANODE_LOW to capture this.
 */
#define ANODE_HIGH   LOW
#define ANODE_LOW    HIGH

struct seven_segment {
  int a;
  int b;
  int c;
  int d;
  int e;
  int f;
  int g;
};


/*
 *              |----A----|
 *              F         B
 *              |         |
 *              |----G----|
 *              |         |
 *              E         C
 *              |----D----| DP 
 */
struct seven_segment seven_segment[NUM_VALUES] = {
  {.a = ANODE_HIGH, .b = ANODE_HIGH, .c = ANODE_HIGH, .d = ANODE_HIGH, .e = ANODE_HIGH, .f = ANODE_HIGH, .g = ANODE_LOW},  //0
  {.a = ANODE_LOW,  .b = ANODE_HIGH, .c = ANODE_HIGH, .d = ANODE_LOW,  .e = ANODE_LOW,  .f = ANODE_LOW,  .g = ANODE_LOW},  //1
  {.a = ANODE_HIGH, .b = ANODE_HIGH, .c = ANODE_LOW,  .d = ANODE_HIGH, .e = ANODE_HIGH, .f = ANODE_LOW,  .g = ANODE_HIGH}, //2
  {.a = ANODE_HIGH, .b = ANODE_HIGH, .c = ANODE_HIGH, .d = ANODE_HIGH, .e = ANODE_LOW,  .f = ANODE_LOW,  .g = ANODE_HIGH}, //3
  {.a = ANODE_LOW,  .b = ANODE_HIGH, .c = ANODE_HIGH, .d = ANODE_LOW,  .e = ANODE_LOW,  .f = ANODE_HIGH, .g = ANODE_HIGH}, //4
  {.a = ANODE_HIGH, .b = ANODE_LOW,  .c = ANODE_HIGH, .d = ANODE_HIGH, .e = ANODE_LOW,  .f = ANODE_HIGH, .g = ANODE_HIGH}, //5
  {.a = ANODE_HIGH, .b = ANODE_LOW,  .c = ANODE_HIGH, .d = ANODE_HIGH, .e = ANODE_HIGH, .f = ANODE_HIGH, .g = ANODE_HIGH}, //6
  {.a = ANODE_HIGH, .b = ANODE_HIGH, .c = ANODE_HIGH, .d = ANODE_LOW,  .e = ANODE_LOW,  .f = ANODE_LOW,  .g = ANODE_LOW},  //7
  {.a = ANODE_HIGH, .b = ANODE_HIGH, .c = ANODE_HIGH, .d = ANODE_HIGH, .e = ANODE_HIGH, .f = ANODE_HIGH, .g = ANODE_HIGH}, //8
  {.a = ANODE_HIGH, .b = ANODE_HIGH, .c = ANODE_HIGH, .d = ANODE_HIGH, .e = ANODE_LOW,  .f = ANODE_HIGH, .g = ANODE_HIGH}, //9
};

/* This turns off the 7-Segment-display */
void switchOffSevenSegment()
{
  digitalWrite(COM, LOW); //clear the current output  
}

/* This lights up the 7-segment display with the values in @seg */
void set_value(struct seven_segment seg)
{
  switchOffSevenSegment();
  digitalWrite(COM, HIGH); //Enable output
  digitalWrite(A_PIN, seg.a);
  digitalWrite(B_PIN, seg.b);
  digitalWrite(C_PIN, seg.c);
  digitalWrite(D_PIN, seg.d);
  digitalWrite(E_PIN, seg.e);
  digitalWrite(F_PIN, seg.f);
  digitalWrite(G_PIN, seg.g);
}


/* This is the Lucky-Number that will appear on the Serial Console */
int lucky_number = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(COM, OUTPUT);
  pinMode(A_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  pinMode(C_PIN, OUTPUT);
  pinMode(D_PIN, OUTPUT);
  pinMode(E_PIN, OUTPUT);
  pinMode(F_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  set_value(seven_segment[0]);
  Serial.begin(9600);
  lucky_number = random(0, 10);
  char val = '0' + lucky_number;
  Serial.println(val);
}

#define YES 1
#define NO 0

/* TIMEOUT is the maximum time between any two consecutive numbers are displayed on the 7-segment display. 
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

  while(digitalRead(button))
    ;
  return YES;
}


/* Maximum number of strikes */
#define MAX_ATTEMPTS 5


int state = 0; // The current value of the 7-Segment display
int paused = 1; //Indicates if the button is in a paused state.
int timeout = TIMEOUT; //Variable to keep track of the timeout for the current epoch
int count = timeout;  //Variable to keep track of the amount of time that is pending in the current epoch
int started = 0; //If the new round is started or not.
int stopped = 0; //If the game has been stopped or not.
int failed_attempts = 0; //Number of strikes so far.
int decrement = 100; //Amount by which to decrement the timeout, each time the user gets a correct answer.

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

/*
 * Helper function to flash the Green LED, when the user presses the button at the correct time.
 */
void successIndication(void)
{
  //do nothing for now. But eventually glow a green LED.
  for (int i = 0; i < 3; i++) {
    digitalWrite(GREEN_LED, HIGH);
    delay(200);
    digitalWrite(GREEN_LED, LOW);
    delay(200);
  }
}


/*
 * Helper function to flash the Red LED, when the user presses the button at the incorrect time.
 */
int failureIndication(int failed_attempts)
{
  //Do nothing.
  for (int i = 0; i < 3; i++) {
    digitalWrite(RED_LED, HIGH);
    delay(200);
    digitalWrite(RED_LED, LOW);
    delay(200);
  }
  failed_attempts++;

  return failed_attempts;
}


/*
 * Helper function to indicate that the game has ended. This will print the letters E,n,d on the 7-segment display.
 */
void resetIndication(void)
{
  struct seven_segment end_val[3] = {{.a = ANODE_HIGH, .b = ANODE_LOW,  .c = ANODE_LOW, .d = ANODE_HIGH,
                                      .e = ANODE_HIGH, .f = ANODE_HIGH, .g = ANODE_HIGH}, //E
                                     {.a = ANODE_LOW,  .b = ANODE_LOW,  .c = ANODE_HIGH, .d = ANODE_LOW,
                                      .e = ANODE_HIGH, .f = ANODE_LOW,  .g = ANODE_HIGH}, //n
                                     {.a = ANODE_LOW,  .b = ANODE_HIGH, .c = ANODE_HIGH, .d = ANODE_HIGH,
                                      .e = ANODE_HIGH, .f = ANODE_LOW,  .g = ANODE_HIGH} // d 
                                    };
  for (int i = 0; i < 3; i++) {
   
    set_value(end_val[i]);
    digitalWrite(GREEN_LED, HIGH);
    delay(200);
    digitalWrite(GREEN_LED, LOW);
    delay(200);
    digitalWrite(RED_LED, HIGH);
    delay(200);
    digitalWrite(RED_LED, LOW);
    delay(200);
  }
  
}


/*
 * The main loop
 */

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
      return;
    }

    if (started && paused) { //The user pressed a button while the numbers were running. Evaluate what the current number is.
      started = 0;
      int result = evaluate(state);
      
      if (result == SUCCESS) {
        successIndication();
        timeout = timeout - decrement;
        if (timeout < 100) { // User has succeeded at all levels. 
          resetIndication();
          switchOffSevenSegment(); //End game
          timeout = TIMEOUT;
          count = timeout;
          stopped = 1;
          return;
        }
        count = timeout; //Replenish the timeout
        int new_number = random(0, 10); //Get a new number
        if (new_number == lucky_number) // Ensure it isn't the same as the previous
          new_number = (new_number + 4) % 10;
        lucky_number = new_number;
        char val = '0' + lucky_number;

        Serial.println(lucky_number); //Print the number on the serial console
        return;
      } else {
        failed_attempts = failureIndication(failed_attempts); //Show failure indication
        if (failed_attempts >= MAX_ATTEMPTS) { //All attempts exhausted
          resetIndication();
          timeout = TIMEOUT;
          failed_attempts = 0;
          state = 0;
          return;
        }
      }
    } else if (!started && !paused) { //The user pressed the button while the numbers were paused. Start the new epoch
      started = 1;
      count = timeout;
    } else if (!started && paused) { //The user has not pressed the button since the last pause. Do nothing
      return; 
    }
    
    // Here the epoch has started and the user hasn't paused yet. So count-down.
    count--;

    if (count == 0) { // Change the number on the 7-segment display to the next one.
       state = (state + 1) % NUM_VALUES;
       set_value(seven_segment[state]);
       count = timeout;
    }

    delay(1);
  }

}
