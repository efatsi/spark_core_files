#include "math.h"

const int sampleWindow = 1000; // one second

long timerStart;
int  sample;
int  signalMax;
int  signalMin;

int  readings[60];
int  peakToPeak    = 0;
int  iteration     = 0;
int  mean          = 0;
int  variance      = 0;
bool hasEnoughData = false;

void setup()
{
  Serial.begin(9600);
  Spark.variable("mean",     &mean, INT);
  Spark.variable("variance", &variance, INT);

  resetVariables();
}

void loop()
{
  makeSampleReading();

  if (millis() - timerStart > sampleWindow) {
    peakToPeak = signalMax - signalMin;
    readings[iteration] = peakToPeak * 100 / 4096;

    iteration += 1;

    if (iteration == 60) {
      hasEnoughData = true;
      iteration     = 0;
    }
    if (hasEnoughData) {
      calculateMean();
      calculateVariance();
    }

    resetVariables();
  }
}

void makeSampleReading() {
  sample = analogRead(A0);

  if (sample > signalMax) signalMax = min(sample, 4096);
  if (sample < signalMin) signalMin = sample;
}

void resetVariables() {
  signalMax  = 0;
  signalMin  = 4096;
  timerStart = millis();
}

void calculateMean() {
  int sum = 0;

  for (int i = 0; i < 60; i++) {
    sum += readings[i];
  }

  mean = sum / 60;
}

void calculateVariance() {
  int varianceSum = 0;

  for (int i = 0; i < 60; i++) {
    varianceSum += pow(readings[i] - mean, 2);
  }

  variance = varianceSum / 60;
}
