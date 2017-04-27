#include "Arduino.h"
#include "Streaming.h"
#include "Array.h"
#include "Vector.h"
#include "ConstantVariable.h"
#include "ArduinoJson.h"
#include "JsonStream.h"

#include "ModularClient.h"


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

  StaticJsonBuffer<80> json_buffer;
  double result = dev.callGetResult(json_buffer,"volume");
  if (dev.callWasSuccessful())
  {
    Serial << "volume: " << result << "\n\n";
  }
  else
  {
    Serial << "? not successful!\n\n";
  }
  delay(1000);

}
