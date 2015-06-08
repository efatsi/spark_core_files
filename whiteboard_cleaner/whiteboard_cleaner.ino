#include "IRremote.h"
#include "Stepper.h"
#include "math.h"

IRsend irsend(D4);
int relayPin = A0;

Stepper stepper1(D0, D1);
Stepper stepper2(D2, D3);

float currentX = 26;
float currentY = 0;

float targetX = 26;
float targetY = 0;

bool stepper1updated;
bool stepper2updated;

bool cleaning = false;

void setup()
{
  Serial.begin(9600);
  Spark.function("coordinates", coordinates);
  Spark.function("moveBoth", moveBoth);
  Spark.function("setMiddle", setMiddle);
   // Spark.function("clean", clean);
  Spark.function("irTest", irTest);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
}

void loop() {
  stepper1updated = stepper1.update();
  stepper2updated = stepper2.update();

  if (stepper1updated || stepper2updated) {
    // no op, one or both steppers moving
  } else {
    // steppers idle
    analyzeSituation();
  }
}

int coordinates(String input) {
  int loc1 = 0;
  int loc2 = 0;
  float x;
  float y;

  loc1 = input.indexOf(",");
  x    = input.substring(0, loc1).toFloat();

  loc2 = input.indexOf(",", loc1 + 1);
  y    = input.substring(loc1 + 1, loc2).toFloat();

  setTarget(x, y);

  return 1;
}

int moveBoth(String input) {
  int loc1 = 0;
  int loc2 = 0;
  float arg1;
  float arg2;

  loc1 = input.indexOf(",");
  arg1 = input.substring(0, loc1).toFloat();

  loc2 = input.indexOf(",", loc1 + 1);
  arg2 = input.substring(loc1 + 1, loc2).toFloat();

  stepper1.setTarget(arg1);
  stepper2.setTarget(arg2);

  return 1;
}

int setMiddle(String input) {
  stepper1.setMiddle();
  stepper2.setMiddle();

  currentX = 26;
  currentY = 0;

  setTarget(26, 0);

  return 1;
}

int clean(String input) {
  targetX  = 26;
  targetY  = 12;
  cleaning = true;
  turnMotorOn();

  return 1;
}

void analyzeSituation() {
  if (currentX != targetX || currentY != targetY) {
    float diffX   = targetX - currentX;
    float diffY   = targetY - currentY;
    float maxDiff = max(abs(diffX), abs(diffY));

    moveTo(currentX + (diffX / maxDiff), currentY + (diffY / maxDiff));
  } else {
    if(cleaning) {
      nextCleanStep();
    }
  }
}

void nextCleanStep() {
  int steps[10][2] = {
    {26 , 12},
    {20 , 12},
    {20 , 16},
    {32 , 16},
    {32 , 20},
    {20 , 20},
    {20 , 24},
    {32 , 24},
    {32 , 12},
    {26 , 12}
  };

  for (int i = 0; i < 9; i++) {
    if (at(steps[i][0], steps[i][1])) {
      setTarget(steps[i+1][0], steps[i+1][1]);

      if (i == 8) {
        cleaning = false;
        turnMotorOff();
      }
    }
  }
}

bool at(int x, int y) {
  return (currentX == x && currentY == y);
}

void setTarget(int x, int y) {
  targetX = x;
  targetY = y;
}

void moveTo(float x, float y) {
  float length1 = sqrt(pow(x    + 4, 2) + pow(y + 10, 2));
  float length2 = sqrt(pow(52-x + 4, 2) + pow(y + 10, 2));

  currentX = x;
  currentY = y;

  stepper1.setTarget(length1);
  stepper2.setTarget(length2);
}

void turnMotorOn() {
  Serial.println("MOTOR ON");
  irSend(50);
}

void turnMotorOff() {
  Serial.println("MOTOR OFF");
  irSend(0);
}

// 100: test (ON then OFF)
// 50:  ON
// 0:   OFF
void irSend(int value) {
  irsend.sendSony(value, 12);
}

int irTest(String value) {
  char * valueChar = new char[value.length() + 1];
  strcpy(valueChar, value.c_str());
  int toSend = atof(valueChar);

  Serial.print("Sending: ");
  Serial.println(toSend);

  irsend.sendSony(toSend, 12);
  return 1;
}
