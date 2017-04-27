#include "Arduino.h"
#include "ArduinoJson.h"
#include "JsonStream.h"

#include "ModularClient.h"

#include "Streaming.h"


const long BAUDRATE = 115200;
HardwareSerial & serial = Serial1;
ModularClient dev(serial);

void setup()
{
  Serial.begin(BAUDRATE);
  serial.begin(BAUDRATE);

  dev.setDebugStream(Serial);
}

void checkCall(const char method[])
{
  if (dev.callWasSuccessful())
  {
    Serial << method << " success!" << "\n";
  }
  else
  {
    Serial << method << " error!" << "\n";
  }
  Serial << "\n";
}

void loop()
{
  dev.call("playTone","4000","ALL");
  checkCall("playTone");
  delay(1000);

  dev.call("playNoise","LEFT");
  checkCall("playNoise");
  delay(1000);

  dev.call("stop");
  checkCall("stop");
  delay(1000);

  dev.call("badMethod");
  checkCall("badMethod");
  delay(1000);
}
