#include <Arduino.h>
#include <constants.h>
#include <ledMgr.h>

const int NUM_CLOCK_TICKS = 20;

bool startUpTest()
{
  static int clockTick = 0;
  static bool isOn = false;

  clockTick++;
  if (clockTick > NUM_CLOCK_TICKS)
  {
    return true;
  }

  if (clockTick % 5 == 0)
  {
    isOn = !isOn;
  }

  uint8_t val = isOn ? ON : OFF;

  digitalWrite(FORWARD_LED_OUT, val);
  digitalWrite(LAYOVER_LED_OUT, val);

  digitalWrite(SPEED_MIN_LED_OUT, val);
  digitalWrite(SPEED_20_LED_OUT, val);
  digitalWrite(SPEED_40_LED_OUT, val);
  digitalWrite(SPEED_80_LED_OUT, val);
  digitalWrite(SPEED_MAX_LED_OUT, val);

  return false;
}

void toggleClockTickIndicator()
{
  static int flashTick = 0;
  flashTick++;
  digitalWrite(CLOCK_LED_OUT, flashTick % CLOCKIE_ON_RATIO == 0 ? ON : OFF);
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
