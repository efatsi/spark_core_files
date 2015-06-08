/*
  LightControl.h - Library for controlling two LED strips with PWM.
  Created by Elias S. Fatsi, August 30, 2014.
  Released into the public domain.
*/

#ifndef LightControl_h
#define LightControl_h

#include "application.h"

class LightControl
{
  public:
    LightControl(
      int littleRedPin,
      int littleGreenPin,
      int littleBluePin,
      int largeRedPin,
      int largeGreenPin,
      int largeBluePin);

    void initialize();
    void display(String light, String command);
    void dualRainbows();
    void party();
  private:
    int _littleRedPin;
    int _littleGreenPin;
    int _littleBluePin;
    int _largeRedPin;
    int _largeGreenPin;
    int _largeBluePin;

    int _min;
    int _littleMax;
    int _largeMax;

    int _fadeSpeed;

    int _littlePartyTracker;
    int _largePartyTracker;

    void _setValues(int rgbValues[], int partyValue);
};

#endif
