#include <Arduino.h>
#include <constants.h>
#include <ledMgr.h>

int trainSpeed;

/**
 * Get desired speed from the potentiometer, scale it, and set the
 * motor speed appropriately.
 * `map` adjustments to address disparity between analog read (10 bit)
 * and analog write (8 bit)
 */
void updateSpeed()
{
  int potValue = analogRead(POTENTIOMETER_INPUT);
  trainSpeed = map(potValue, 0, 1023, 0, 255);
  analogWrite(MOTOR_SPEED_OUT, trainSpeed);
  showSpeed(trainSpeed);
}

int getSpeed()
{
  return trainSpeed;
}
