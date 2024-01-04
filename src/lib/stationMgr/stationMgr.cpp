#include <Arduino.h>
#include <constants.h>
#include <ledMgr.h>
#include <msgMgr.h>

int trainDirection = FORWARD;
unsigned long delayExpiry = 0;

void setDirection(int direction)
{
  if (trainDirection == direction)
  {
    return;
  }
  trainDirection = direction;
  updateDirectionLED(direction);
  msgReversingDirection();
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

String getStationName(uint8_t pin)
{
  switch (pin)
  {
  case TERMINUS_1_INPUT:
    return "Terminus 1";
  case TERMINUS_2_INPUT:
    return "Terminus 2";
  case MID_STATION_1_INPUT:
    return "Middle Station 1";
  default:
    return "Unknown";
  }
}

/**
 * Check if the train has *arrived* at a station by reading the IR proximity
 * sensor (corresponding to `pin`) and comparing it to the threshold.
 * After returning `true` for a given station this will not return `true` again
 * until after the train has visited a different station.
 */
bool isAtStation(uint8_t pin)
{
  static uint8_t lastStation;

  const bool isAtStation = analogRead(pin) < SENSOR_THRESHOLD;
  if (isAtStation && lastStation == pin)
  {
    return false;
  }
  if (isAtStation)
  {
    lastStation = pin;
    msgArrivedAtStation(getStationName(pin) + " (pin " + String(pin) + ")");
  }
  return isAtStation;
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
  updateLayoverLED(true);
  msgStopped();

  digitalWrite(MOTOR_FORWARD_OUT, OFF);
  digitalWrite(MOTOR_REVERSE_OUT, OFF);
}

void startTrain()
{
  setDelay(0);
  updateLayoverLED(false);
  msgStart();
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
  static bool hasFired = false;
  if (hasDelay())
  {
    hasFired = false;
    return false;
  }

  if (hasFired)
  {
    return true;
  }

  hasFired = true;
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
