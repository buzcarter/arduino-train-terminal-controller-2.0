#include <Arduino.h>
#include <constants.h>
#include <ledMgr.h>
#include <speedMgr.h>
#include <stationMgr.h>
#include <TaskScheduler.h>

void setup()
{
  Serial.begin(9600);
  pinMode(MOTOR_FORWARD_OUT, OUTPUT);
  pinMode(MOTOR_REVERSE_OUT, OUTPUT);
  pinMode(MOTOR_SPEED_OUT, OUTPUT);

  pinMode(CLOCK_LED_OUT, OUTPUT);

  pinMode(FORWARD_LED_OUT, OUTPUT);
  pinMode(LAYOVER_LED_OUT, OUTPUT);

  pinMode(SPEED_MIN_LED_OUT, OUTPUT);
  pinMode(SPEED_20_LED_OUT, OUTPUT);
  pinMode(SPEED_40_LED_OUT, OUTPUT);
  pinMode(SPEED_80_LED_OUT, OUTPUT);
  pinMode(SPEED_MAX_LED_OUT, OUTPUT);
}

void clockie() {
  static int clockTick = 0;
  static bool isOn = false;
  clockTick++;
  if (clockTick % 12 == 0) {
    isOn = !isOn;
  }
  digitalWrite(CLOCK_LED_OUT, isOn ? HIGH : LOW);

}

void loop()
{
  clockie();

  static bool isOn = false;
  isOn = !isOn;
  int value = isOn ? LOW : HIGH;


  digitalWrite(FORWARD_LED_OUT, value);
  digitalWrite(LAYOVER_LED_OUT, value);

  digitalWrite(SPEED_MIN_LED_OUT, ON);
  digitalWrite(SPEED_20_LED_OUT, ON);
  digitalWrite(SPEED_40_LED_OUT, ON);
  digitalWrite(SPEED_80_LED_OUT, ON);
  digitalWrite(SPEED_MAX_LED_OUT, ON);

  delay(100);
}
