#include <Arduino.h>
#include <constants.h>
#include <ledMgr.h>

/** Returns true for first 5 seconds of startup. Flashes LEDs to verify working. */
bool isLEDTestDone()
{
  static bool isDone = false;
  if (isDone)
  {
    return true;
  }

  unsigned long elapsedTime = millis();
  bool isOn = false;

  if (elapsedTime >= 4000)
  {
    isDone = true;
    isOn = false;
  }
  else
  {
    isOn = (elapsedTime / 333) % 2 != 0;
  }

  uint8_t val = isOn ? ON : OFF;
  if (digitalRead(CLOCK_LED_OUT) == val)
  {
    return false;
  }

  digitalWrite(CLOCK_LED_OUT, val);

  digitalWrite(FORWARD_LED_OUT, val);
  digitalWrite(LAYOVER_LED_OUT, val);

  digitalWrite(SPEED_MIN_LED_OUT, val);
  digitalWrite(SPEED_20_LED_OUT, val);
  digitalWrite(SPEED_40_LED_OUT, val);
  digitalWrite(SPEED_80_LED_OUT, val);
  digitalWrite(SPEED_MAX_LED_OUT, val);

  return false;
}

void updateClockIndicator()
{
  static int tick = 0;
  digitalWrite(CLOCK_LED_OUT, tick % CLOCKIE_ON_RATIO == 0 ? ON : OFF);
  tick++;
}

void showSpeed(int speed)
{
  const int speedPrct = map(speed, 0, 255, 0, 100);

  digitalWrite(SPEED_MIN_LED_OUT, OFF);
  digitalWrite(SPEED_20_LED_OUT, OFF);
  digitalWrite(SPEED_40_LED_OUT, OFF);
  digitalWrite(SPEED_80_LED_OUT, OFF);
  digitalWrite(SPEED_MAX_LED_OUT, OFF);

  if (speedPrct < 20)
  {
    digitalWrite(SPEED_MIN_LED_OUT, ON);
  }
  else if (speedPrct < 40)
  {
    digitalWrite(SPEED_20_LED_OUT, ON);
  }
  else if (speedPrct < 60)
  {
    digitalWrite(SPEED_40_LED_OUT, ON);
  }
  else if (speedPrct < 80)
  {
    digitalWrite(SPEED_80_LED_OUT, ON);
  }
  else
  {
    digitalWrite(SPEED_MAX_LED_OUT, ON);
  }
}

void showDirection(int direction)
{
  digitalWrite(FORWARD_LED_OUT, direction == FORWARD ? ON : OFF);
}

void showLayover(bool isStopped)
{
  digitalWrite(LAYOVER_LED_OUT, isStopped ? ON : OFF);
}
