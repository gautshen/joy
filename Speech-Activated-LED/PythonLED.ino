#define RED_PIN    3
#define GREEN_PIN  5
#define BLUE_PIN 6


void glowLEDs(int red, int green, int blue)
{
  digitalWrite(RED_PIN, red);
  digitalWrite(GREEN_PIN, green);
  digitalWrite(BLUE_PIN, blue);
  delay(500);
}

void glowAnodeLED(int red, int green, int blue)
{
  analogWrite(RED_PIN, 255 - red);
  analogWrite(GREEN_PIN, 255 - green);
  analogWrite(BLUE_PIN, 255 - blue);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  glowAnodeLED(0, 0, 0);
  Serial.begin(9600);

}

void loop() {
  byte val;
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    val = Serial.read();

    switch (val) {
    case 'R':
      //glowLEDs(HIGH, LOW, LOW);
      glowAnodeLED(255, 0, 0);
      break;
    case 'G':
      //glowLEDs(LOW, HIGH, LOW);
      glowAnodeLED(0, 255, 0);
      break;
    case 'B':
      glowAnodeLED(0, 0, 255);
      //glowLEDs(LOW, LOW, HIGH);
      break;
    case 'C':
      glowAnodeLED(0, 255, 255);
      //glowLEDs(LOW, HIGH, HIGH);
      break;
    case 'M':
      glowAnodeLED(255, 0, 255);
      //glowLEDs(HIGH, LOW, HIGH);
      break;
    case 'Y':
      glowAnodeLED(255, 255, 0);
      //glowLEDs(HIGH, HIGH, LOW);
      break;
    case 'W':
      glowAnodeLED(255, 255, 255);
      //glowLEDs(HIGH, HIGH, HIGH);
      break;
    case 'O':
      glowAnodeLED(0, 0, 0);
      //glowLEDs(LOW, LOW, LOW);
      break;
    }

  }

}
