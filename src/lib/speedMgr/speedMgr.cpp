#include <Arduino.h>
#include <constants.h>
#include <ledMgr.h>

const int NUM_SAMPLES = 5;

int trainSpeed;

int speedSamples[NUM_SAMPLES] = {0, 0, 0, 0, 0};

void sampleSpeed()
{
  static int sampleIndex = 0;
  speedSamples[sampleIndex] = analogRead(POTENTIOMETER_INPUT);
  sampleIndex++;
  if (sampleIndex >= NUM_SAMPLES)
  {
    sampleIndex = 0;
  }
}

int getAvgSpeed()
{
  static int lastSpeed = 0;
  int sum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++)
  {
    sum += speedSamples[i];
  }

  int speed = sum / NUM_SAMPLES;
  speed = map(speed, 0, 1023, 0, 255);
  if (speed >= lastSpeed - 2 && speed <= lastSpeed + 2)
  {
    return lastSpeed;
  }
  lastSpeed = speed;
  return speed;
}

/**
 * Get desired speed from the potentiometer, scale it, and set the
 * motor speed appropriately.
 * `map` adjustments to address disparity between analog read (10 bit)
 * and analog write (8 bit)
 */
void updateSpeed()
{
  int speed = getAvgSpeed();
  if (trainSpeed == speed)
  {
    return;
  }
  trainSpeed = speed;
  analogWrite(MOTOR_SPEED_OUT, trainSpeed);
  showSpeed(trainSpeed);
}

int getSpeed()
{
  return trainSpeed;
}
