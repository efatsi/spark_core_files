// #include <string.h>
// #define LIB_DOMAIN "traffic-room.herokuapp.com"

// TCPClient client;

int redPin   = A4;
int greenPin = A5;
int bluePin  = A6;

int min       = 0;
int max       = 50;
int fadeSpeed = 15;

String color     = "off";

bool bePartying  = false;
int partyTracker = rand() % 1000;
int tempRed      = 0;
int tempGreen    = 0;
int tempBlue     = 0;

void setup() {
  // client.connect(LIB_DOMAIN, 80);
  // client.println("GET /softreset HTTP/1.0");
  // client.println("Host: " LIB_DOMAIN);
  // client.println("Content-Length: 0");
  // client.println();
  // client.flush();

  pinMode(redPin,   OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin,  OUTPUT);

  Spark.function("setColor", setColor);
}

void loop() {
  display();
}

int setColor(String command) {
  color = command;
  return 1;
}

void display() {
  if (color == "party") {
    party();
  }
  else if (color == "r") {
    analogWrite(redPin,   max);
    analogWrite(greenPin, min);
    analogWrite(bluePin,  min);
  }
  else if (color == "g") {
    analogWrite(redPin,   min);
    analogWrite(greenPin, max);
    analogWrite(bluePin,  min);
  }
  else if (color == "b") {
    analogWrite(redPin,   min);
    analogWrite(greenPin, min);
    analogWrite(bluePin,  max);
  }
  else if (color == "rg") {
    analogWrite(redPin,   max);
    analogWrite(greenPin, max);
    analogWrite(bluePin,  min);
  }
  else if (color == "rb") {
    analogWrite(redPin,   max);
    analogWrite(greenPin, min);
    analogWrite(bluePin,  max);
  }
  else if (color == "bg") {
    analogWrite(redPin,   min);
    analogWrite(greenPin, max);
    analogWrite(bluePin,  max);
  }
  else if (color == "rgb") {
    analogWrite(redPin,   max);
    analogWrite(greenPin, max);
    analogWrite(bluePin,  max);
  }
  else {
    analogWrite(redPin,   min);
    analogWrite(greenPin, min);
    analogWrite(bluePin,  min);
  }
}

void party() {
  partyTracker = (partyTracker + 2) % 1000;

  // red on, green up
  if (partyTracker < 170) {
    tempRed   = 1000;
    tempGreen = partyTracker * 1000 / 170;
    tempBlue  = 0;
  }
  // green on, red down
  else if (partyTracker < 330) {
    tempRed   = 1000 - ((partyTracker - 170) * 1000 / 160);
    tempGreen = 1000;
    tempBlue  = 0;
  }
  // green on, blue up
  else if (partyTracker < 500) {
    tempRed   = 0;
    tempGreen = 1000;
    tempBlue  = (partyTracker - 330) * 1000 / 170;
  }
  // blue on, greem down
  else if (partyTracker < 670) {
    tempRed   = 0;
    tempGreen = 1000 - ((partyTracker - 500) * 1000 / 170);
    tempBlue  = 1000;
  }
  // blue on, red up
  else if (partyTracker < 830) {
    tempRed   = (partyTracker - 670) * 1000 / 160;
    tempGreen = 0;
    tempBlue  = 1000;
  }
  // red on, blue down
  else if (partyTracker < 1000) {
    tempRed   = 1000;
    tempGreen = 0;
    tempBlue  = 1000 - ((partyTracker - 830) * 1000 / 170);
  }

  analogWrite(redPin,   tempRed   * max / 1000);
  analogWrite(greenPin, tempGreen * max / 1000);
  analogWrite(bluePin,  tempBlue  * max / 1000);

  delay(fadeSpeed);
}
