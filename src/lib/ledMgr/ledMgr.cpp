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

  digitalWrite(DIRECTION_LED_OUT, val);
  digitalWrite(LAYOVER_LED_OUT, val);

  digitalWrite(SPEED_MIN_LED_OUT, val);
  digitalWrite(SPEED_20_LED_OUT, val);
  digitalWrite(SPEED_40_LED_OUT, val);
  digitalWrite(SPEED_80_LED_OUT, val);
  digitalWrite(SPEED_MAX_LED_OUT, val);

  return false;
}

void updateClockLED()
{
  static int tick = 0;
  digitalWrite(CLOCK_LED_OUT, tick % CLOCKIE_ON_RATIO == 0 ? ON : OFF);
  tick++;
}

void updateSpeedLEDs(int speed)
{
  const int speedPrct = map(speed, 0, 255, 0, 100);

  if (speedPrct < 20)
  {
    digitalWrite(SPEED_MIN_LED_OUT, ON);
    digitalWrite(SPEED_20_LED_OUT, OFF);
    digitalWrite(SPEED_40_LED_OUT, OFF);
    digitalWrite(SPEED_80_LED_OUT, OFF);
    digitalWrite(SPEED_MAX_LED_OUT, OFF);
  }
  else
  {
    digitalWrite(SPEED_MIN_LED_OUT, OFF);
    digitalWrite(SPEED_20_LED_OUT, ON);
    digitalWrite(SPEED_40_LED_OUT, speedPrct > 40 ? ON : OFF);
    digitalWrite(SPEED_80_LED_OUT, speedPrct > 60 ? ON : OFF);
    digitalWrite(SPEED_MAX_LED_OUT, speedPrct > 80 ? ON : OFF);
  }
}

void updateDirectionLED(int direction)
{
  digitalWrite(DIRECTION_LED_OUT, direction == FORWARD ? ON : OFF);
}

void updateLayoverLED(bool isStopped)
{
  digitalWrite(LAYOVER_LED_OUT, isStopped ? ON : OFF);
}
