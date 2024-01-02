#include <Arduino.h>
#include <speedMgr.h>
#include <stationMgr.h>

void msgSendSpeedInfo()
{
  static String lastMsg = "";
  int speed = getSpeed();
  int prct = (speed * 100) / 255;
  String msg = "Speed: " + String(prct) + "% (" + String((speed)) + ") " + getDirection();
  if (msg == lastMsg)
  {
    return;
  }
  lastMsg = msg;
  Serial.println(msg);
}
