#include <Arduino.h>
#include <constants.h>
#include <ledMgr.h>

int trainDirection;
unsigned long delayExpiry = 0;

void setDirection(int direction)
{
  trainDirection = direction;
  showDirection(direction);
}

String getDirection()
{
  return (trainDirection == FORWARD) ? "forward" : "reverse";
}

bool hasDelay()
{
  if (millis() >= delayExpiry)
  {
    delayExpiry = 0;
  }
  return delayExpiry > 0;
}

void setDelay(int length)
{
  delayExpiry = millis() + length;
}

/**
 * Check if the train is at a station by reading the IR proximity sensor
 * (corresponding to `pin`) and comparing it to the threshold.
 */
bool isAtStation(uint8_t pin)
{
  return analogRead(pin) < SENSOR_THRESHOLD;
}

bool isAtTerminus()
{
  return isAtStation(TERMINUS_1_INPUT) || isAtStation(TERMINUS_2_INPUT);
}

/**
 * Makes adding additional stations easier, just OR ('||') them together
 */
bool isAtMiddleStation()
{
  return isAtStation(MID_STATION_1_INPUT);
}

void stopTrain()
{
  showLayover(true);

  digitalWrite(MOTOR_FORWARD_OUT, OFF);
  digitalWrite(MOTOR_REVERSE_OUT, OFF);
}

void startTrain()
{
  setDelay(0);
  showLayover(false);

  digitalWrite(MOTOR_FORWARD_OUT, trainDirection == FORWARD ? ON : OFF);
  digitalWrite(MOTOR_REVERSE_OUT, trainDirection == REVERSE ? ON : OFF);
}

void scheduleTrainStart(int length)
{
  setDelay(length);
  // in theory at a later time we'd have a stack of actions, slowDown, speedUp, etc.
}

bool pendingActionsResolved()
{
  if (hasDelay())
  {
    return false;
  }

  startTrain();
  return true;
}

void reverseDirection()
{
  stopTrain();
  setDirection(trainDirection == FORWARD ? REVERSE : FORWARD);
  scheduleTrainStart(3000);
}

void pauseAndResume()
{
  stopTrain();
  scheduleTrainStart(6000);
}
