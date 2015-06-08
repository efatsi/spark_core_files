int min = 0;
int max = 40;
int fadeSpeed = 15;

int bluePin  = A4;
int greenPin = A6;
int redPin   = A5;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  int i;

  // start with just red
  analogWrite(redPin, max);
  analogWrite(bluePin, min);
  analogWrite(greenPin, min);

  // red to red/blue
  for (i = min; i < max; i++) {
    analogWrite(bluePin, i);
    delay(fadeSpeed);
  }
  // red/blue to blue
  for (i = max; i > min; i--) {
    analogWrite(redPin, i);
    delay(fadeSpeed);
  }
  // blue to blue/green
  for (i = min; i < max; i++) {
    analogWrite(greenPin, i);
    delay(fadeSpeed);
  }
  // blue/green to green
  for (i = max; i > min; i--) {
    analogWrite(bluePin, i);
    delay(fadeSpeed);
  }
  // green to green/red
  for (i = min; i < max; i++) {
    analogWrite(redPin, i);
    delay(fadeSpeed);
  }
  // green/red to red
  for (i = max; i > min; i--) {
    analogWrite(greenPin, i);
    delay(fadeSpeed);
  }
}
