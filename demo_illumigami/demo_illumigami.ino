int bluePin  = A4;
int redPin   = A5;
int greenPin = A6;

int min       = 0;
int max       = 120;
int fadeSpeed = 10;

String color = "off";

int currentRed   = min;
int currentGreen = min;
int currentBlue  = min;

int targetRed   = min;
int targetGreen = min;
int targetBlue  = min;

bool connectedToInternet = false;
SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  pinMode(redPin,   OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin,  OUTPUT);

  attemptConnection("sleep");
}

void attemptConnection(String delayMethod) {
  for (int i=0; i<2; i++) {
    if (!Spark.connected()) {
      Spark.connect();

      if (delayMethod == "sleep") {
        delay(4000);
      } else {
        party();
      }
    }
  }

  if (Spark.connected()) {
    connectedToInternet = true;

    Spark.function("setColor", setColor);
    Spark.subscribe("graba/buttonPress", grabaReaction, MY_DEVICES);

    color = "green";
    assignTargets();
  }
}

void loop() {
  if (connectedToInternet) {
    if (color == "party") {
      party();
    } else {
      display();
    }
  } else {
    party();
    setColor("off");
    delay(2000);
    setColor("green");
    delay(2000);
    setColor("yellow");
    delay(2000);
    setColor("red");
    delay(2000);
    setColor("green_blue");
    attemptConnection("party");
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
  fadeWith(fadeSpeed);
}

void slowFade() {
  fadeWith(fadeSpeed * 2);
}

void fadeWith(int speed) {
  int redDiff   = targetRed   - currentRed;
  int greenDiff = targetGreen - currentGreen;
  int blueDiff  = targetBlue  - currentBlue;

  int maxDiff = max(abs(redDiff), max(abs(blueDiff), abs(greenDiff)));

  for (int i = 1; i <= maxDiff; i++) {
    analogWrite(redPin,   currentRed   + (i * (redDiff   / maxDiff)));
    analogWrite(greenPin, currentGreen + (i * (greenDiff / maxDiff)));
    analogWrite(bluePin,  currentBlue  + (i * (blueDiff  / maxDiff)));
    delay(speed);
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
  slowFade();

  // red to red/green
  set(max, max, min);
  slowFade();

  // red/green to green
  set(min, max, min);
  slowFade();

  // green to green/blue
  set(min, max, max);
  slowFade();

  // green/blue to blue
  set(min, min, max);
  slowFade();

  // blue to red/blue
  set(max, min, max);
  slowFade();

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

void grabaReaction(const char *name, const char *data) {
  String response = String(data);

  if (response == "free") {
    color = "green";
  } else {
    color = "red";
  }

  assignTargets();
}
