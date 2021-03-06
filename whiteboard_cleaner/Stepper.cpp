/*
  Stepper.h - Library for controlling Whiteboard Cleaning stepper motors.
  Created by Elias S. Fatsi, March 3, 2015.
  Released into the public domain.
*/

#include "Stepper.h"

Stepper::Stepper(
  int dirPin,
  int stepPin)
{
  _dirPin  = dirPin;
  _stepPin = stepPin;

  _position       = 0;
  _targetPosition = 0;
  _positionStep   = 0.01;
  _buffer         = 0.005;

  pinMode(_dirPin,  OUTPUT);
  pinMode(_stepPin, OUTPUT);
}

void Stepper::setMiddle() {
  _position = 31.5;
  _targetPosition = 31.5;
}

void Stepper::setTarget(float newTarget) {
  _targetPosition = newTarget;
}

bool Stepper::update() {
  if (_targetPosition > (_position + _buffer)) {
    _moveTo(_position + _positionStep);
    return true;
  } else if (_targetPosition < (_position - _buffer)) {
    _moveTo(_position - _positionStep);
    return true;
  } else {
    return false;
  }
}

void Stepper::_moveTo(float newPosition)
{
  if(newPosition > _position) {
    digitalWrite(_dirPin, HIGH);
    _moveSteps((newPosition - _position) * 1600);
  } else {
    digitalWrite(_dirPin, LOW);
    _moveSteps((_position - newPosition) * 1600);
  }

  _position = newPosition;
}

void Stepper::_moveSteps(float steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(_stepPin, LOW);
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(100);
  }
}
