/*
  Stepper.h - Library for controlling two LED strips with PWM.
  Created by Elias S. Fatsi, March 3, 2015.
  Released into the public domain.
*/

#ifndef Stepper_h
#define Stepper_h

#include "application.h"

class Stepper
{
  public:
    Stepper(
      int dirPin,
      int stepPin);

    void setMiddle();
    void setTarget(float newTarget);
    bool update();

  private:
    int _dirPin;
    int _stepPin;
    int _buttonPin;

    float _position;
    float _targetPosition;
    float _positionStep;
    float _buffer;

    void _moveTo(float newPosition);
    void _moveSteps(float steps);
};

#endif
