#include <Arduino.h>
#include <speedMgr.h>
#include <stationMgr.h>

void msgSendSpeedInfo()
{
  static String lastMsg = "";
  int speed = getSpeed();
  int prct = (speed * 100) / 255;
  String msg = "Power " + String(prct) + "% (" + String((speed)) + ") " + getDirection();
  if (msg == lastMsg)
  {
    return;
  }
  lastMsg = msg;
  Serial.println(msg);
}

void msgReversingDirection()
{
  Serial.println("Reversing direction");
}

void msgArrivedAtStation(String stationName)
{
  Serial.println("Arrived at station " + stationName);
}

void msgStart()
{
  Serial.println("Traveling");
}

void msgStopped()
{
  Serial.println("Stopped");
}
