#include <Arduino.h>
#include <constants.h>
#include <ledMgr.h>

int trainDirection;

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

void startTrain(int direction)
{
  trainDirection = direction;

  showLayover(false);
  showDirection(direction);

  digitalWrite(MOTOR_FORWARD_OUT, direction == FORWARD ? ON : OFF);
  digitalWrite(MOTOR_REVERSE_OUT, direction == REVERSE ? ON : OFF);
}

void stopAndGo(int direction)
{
  stopTrain();
  delay(5000); // ideally wouldn't block, but this is a simple example
  startTrain(direction);
}

void reverseDirection()
{
  stopAndGo(trainDirection == FORWARD ? REVERSE : FORWARD);
}

void pauseAndResume()
{
  stopAndGo(trainDirection);
}

String getDirection()
{
  return (trainDirection == FORWARD) ? "forward" : "reverse";
}
