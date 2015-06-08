/*
  LightControl.h - Library for controlling two LED strips with PWM.
  Created by Elias S. Fatsi, August 30, 2014.
  Released into the public domain.
*/

#include "LightControl.h"

LightControl::LightControl(
  int littleRedPin,
  int littleGreenPin,
  int littleBluePin,
  int largeRedPin,
  int largeGreenPin,
  int largeBluePin)
{
  _littleRedPin   = littleRedPin;
  _littleGreenPin = littleGreenPin;
  _littleBluePin  = littleBluePin;
  _largeRedPin    = largeRedPin;
  _largeGreenPin  = largeGreenPin;
  _largeBluePin   = largeBluePin;

  _min            = 0;
  _littleMax      = 40;
  _largeMax       = 200;

  _fadeSpeed = 15;

  _littlePartyTracker = rand() % 1000;
  _largePartyTracker  = rand() % 1000;

  pinMode(littleRedPin,   OUTPUT);
  pinMode(littleGreenPin, OUTPUT);
  pinMode(littleBluePin,  OUTPUT);

  pinMode(largeRedPin,   OUTPUT);
  pinMode(largeGreenPin, OUTPUT);
  pinMode(largeBluePin,  OUTPUT);
}


void LightControl::initialize()
{
  analogWrite(_littleRedPin,   OUTPUT);
  analogWrite(_littleGreenPin, OUTPUT);
  analogWrite(_littleBluePin,  OUTPUT);

  analogWrite(_largeRedPin,   OUTPUT);
  analogWrite(_largeGreenPin, OUTPUT);
  analogWrite(_largeBluePin,  OUTPUT);
}

void LightControl::display(String light, String command)
{
  int min = _min;
  int redPin;
  int greenPin;
  int bluePin;
  int max;

  if (light == "little") {
    redPin   = _littleRedPin;
    greenPin = _littleGreenPin;
    bluePin  = _littleBluePin;
    max      = _littleMax;
  }
  else {
    redPin   = _largeRedPin;
    greenPin = _largeGreenPin;
    bluePin  = _largeBluePin;
    max      = _largeMax;
  }

  if (command == "r") {
    analogWrite(redPin,   max);
    analogWrite(greenPin, min);
    analogWrite(bluePin,  min);
  }
  else if (command == "g") {
    analogWrite(redPin,   min);
    analogWrite(greenPin, max);
    analogWrite(bluePin,  min);
  }
  else if (command == "b") {
    analogWrite(redPin,   min);
    analogWrite(greenPin, min);
    analogWrite(bluePin,  max);
  }
  else if (command == "rg") {
    analogWrite(redPin,   max);
    analogWrite(greenPin, max);
    analogWrite(bluePin,  min);
  }
  else if (command == "rb") {
    analogWrite(redPin,   max);
    analogWrite(greenPin, min);
    analogWrite(bluePin,  max);
  }
  else if (command == "bg") {
    analogWrite(redPin,   min);
    analogWrite(greenPin, max);
    analogWrite(bluePin,  max);
  }
  else if (command == "rgb") {
    analogWrite(redPin,   max);
    analogWrite(greenPin, max);
    analogWrite(bluePin,  max);
  }
  else if (command == "off") {
    analogWrite(redPin,   min);
    analogWrite(greenPin, min);
    analogWrite(bluePin,  min);
  }
  else if (command == "rainbow") {
    int i;

    // start with just red
    analogWrite(redPin, max);
    analogWrite(bluePin, min);
    analogWrite(greenPin, min);

    // red to red/blue
    for (i = min; i < max; i++) {
      analogWrite(bluePin, i);
      delay(_fadeSpeed);
    }
    // red/blue to blue
    for (i = max; i > min; i--) {
      analogWrite(redPin, i);
      delay(_fadeSpeed);
    }
    // blue to blue/green
    for (i = min; i < max; i++) {
      analogWrite(greenPin, i);
      delay(_fadeSpeed);
    }
    // blue/green to green
    for (i = max; i > min; i--) {
      analogWrite(bluePin, i);
      delay(_fadeSpeed);
    }
    // green to green/red
    for (i = min; i < max; i++) {
      analogWrite(redPin, i);
      delay(_fadeSpeed);
    }
    // green/red to red
    for (i = max; i > min; i--) {
      analogWrite(greenPin, i);
      delay(_fadeSpeed);
    }
  }
}

void LightControl::dualRainbows() {
  int i;

  // start with just red
  analogWrite(_littleRedPin, _littleMax);
  analogWrite(_littleGreenPin, _min);
  analogWrite(_littleBluePin, _min);

  analogWrite(_largeRedPin, _largeMax);
  analogWrite(_largeGreenPin, _min);
  analogWrite(_largeBluePin, _min);

  // red to red/blue
  for (i = 0; i < 100; i++) {
    analogWrite(_littleBluePin, i * _littleMax / 100);
    analogWrite(_largeBluePin, i * _largeMax / 100);
    delay(_fadeSpeed);
  }
  // red/blue to blue
  for (i = 100; i > 0; i--) {
    analogWrite(_littleRedPin, i * _littleMax / 100);
    analogWrite(_largeRedPin, i * _largeMax / 100);
    delay(_fadeSpeed);
  }
  // blue to blue/green
  for (i = 0; i < 100; i++) {
    analogWrite(_littleGreenPin, i * _littleMax / 100);
    analogWrite(_largeGreenPin, i * _largeMax / 100);
    delay(_fadeSpeed);
  }
  // blue/green to green
  for (i = 100; i > 0; i--) {
    analogWrite(_littleBluePin, i * _littleMax / 100);
    analogWrite(_largeBluePin, i * _largeMax / 100);
    delay(_fadeSpeed);
  }
  // green to green/red
  for (i = 0; i < 100; i++) {
    analogWrite(_littleRedPin, i * _littleMax / 100);
    analogWrite(_largeRedPin, i * _largeMax / 100);
    delay(_fadeSpeed);
  }
  // green/red to red
  for (i = 100; i > 0; i--) {
    analogWrite(_littleGreenPin, i * _littleMax / 100);
    analogWrite(_largeGreenPin, i * _largeMax / 100);
    delay(_fadeSpeed);
  }
}

void LightControl::party() {
  _littlePartyTracker = (_littlePartyTracker + (rand() % 4)) % 1000;
  _largePartyTracker  = (_largePartyTracker  + (rand() % 7)) % 1000;

  int littleValues[3];
  int largeValues[3];

  _setValues(littleValues, _littlePartyTracker);
  _setValues(largeValues, _largePartyTracker);

  analogWrite(_littleRedPin,   littleValues[0] * _littleMax / 1000);
  analogWrite(_littleGreenPin, littleValues[1] * _littleMax / 1000);
  analogWrite(_littleBluePin,  littleValues[2] * _littleMax / 1000);

  analogWrite(_largeRedPin,   largeValues[0] * _largeMax / 1000);
  analogWrite(_largeGreenPin, largeValues[1] * _largeMax / 1000);
  analogWrite(_largeBluePin,  largeValues[2] * _largeMax / 1000);

  delay(_fadeSpeed);
}

void LightControl::_setValues(int rgbValues[], int partyValue) {
  // invalid input
  if (partyValue < 0 || partyValue > 1000) {
    rgbValues[0] = 0;
    rgbValues[1] = 0;
    rgbValues[2] = 0;
  }

  // red on, green up
  else if (partyValue < 170) {
    rgbValues[0] = 1000;
    rgbValues[1] = partyValue * 1000 / 170;
    rgbValues[2] = 0;
  }
  // green on, red down
  else if (partyValue < 330) {
    rgbValues[0] = 1000 - ((partyValue - 170) * 1000 / 160);
    rgbValues[1] = 1000;
    rgbValues[2] = 0;
  }
  // green on, blue up
  else if (partyValue < 500) {
    rgbValues[0] = 0;
    rgbValues[1] = 1000;
    rgbValues[2] = (partyValue - 330) * 1000 / 170;
  }
  // blue on, greem down
  else if (partyValue < 670) {
    rgbValues[0] = 0;
    rgbValues[1] = 1000 - ((partyValue - 500) * 1000 / 170);
    rgbValues[2] = 1000;
  }
  // blue on, red up
  else if (partyValue < 830) {
    rgbValues[0] = (partyValue - 670) * 1000 / 160;
    rgbValues[1] = 0;
    rgbValues[2] = 1000;
  }
  // red on, blue down
  else if (partyValue < 1000) {
    rgbValues[0] = 1000;
    rgbValues[1] = 0;
    rgbValues[2] = 1000 - ((partyValue - 830) * 1000 / 170);
  }
}
