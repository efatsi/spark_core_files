int bluePin  = A4;
int redPin   = A5;
int greenPin = A6;

int min       = 0;
int max       = 30;
int fadeSpeed = 40;

String color = "off";

int currentRed   = min;
int currentGreen = min;
int currentBlue  = min;

int targetRed   = min;
int targetGreen = min;
int targetBlue  = min;

void setup() {
  pinMode(redPin,   OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin,  OUTPUT);

  Spark.function("setColor", setColor);
}

void loop() {
  if (color == "party") {
    party();
  } else {
    display();
  }
}

void display() {
  if (needsFading()) {
    fade();
  }
}

bool needsFading() {
  return (
    (targetRed   != currentRed)   ||
    (targetGreen != currentGreen) ||
    (targetBlue  != currentBlue)
  );
}

void fade() {
  int redDiff   = targetRed   - currentRed;
  int greenDiff = targetGreen - currentGreen;
  int blueDiff  = targetBlue  - currentBlue;

  int maxDiff = max(abs(redDiff), max(abs(blueDiff), abs(greenDiff)));

  for (int i = 1; i <= maxDiff; i++) {
    analogWrite(redPin,   currentRed   + (i * (redDiff   / maxDiff)));
    analogWrite(greenPin, currentGreen + (i * (greenDiff / maxDiff)));
    analogWrite(bluePin,  currentBlue  + (i * (blueDiff  / maxDiff)));
    delay(fadeSpeed);
  }

  currentRed   = targetRed;
  currentGreen = targetGreen;
  currentBlue  = targetBlue;
}

int setColor(String command) {
  color = command;
  assignTargets();

  return 1;
}

void party() {
  // whatever to red
  set(max, min, min);
  fade();

  // red to red/green
  set(max, max, min);
  fade();

  // red/green to green
  set(min, max, min);
  fade();

  // green to green/blue
  set(min, max, max);
  fade();

  // green/blue to blue
  set(min, min, max);
  fade();

  // blue to red/blue
  set(max, min, max);
  fade();

  if (color != "party") {
    assignTargets();
  }
}

void assignTargets() {
  if (color == "red") {
    set(max, min, min);
  }
  else if (color == "green") {
    set(min, max, min);
  }
  else if (color == "blue") {
    set(min, min, max);
  }
  else if (color == "red_green") {
    set(max, max, min);
  }
  else if (color == "red_blue") {
    set(max, min, max);
  }
  else if (color == "green_blue") {
    set(min, max, max);
  }
  else if (color == "white") {
    set(max, max, max);
  }
  else if (color == "off") {
    set(min, min, min);
  }
}

void set(int r, int g, int b) {
  targetRed   = r;
  targetGreen = g;
  targetBlue  = b;
}
