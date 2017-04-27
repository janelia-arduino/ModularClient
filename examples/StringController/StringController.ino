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
  const char* echo = dev.call("echo","test",false);
  checkCall("echo");
  if (dev.callWasSuccessful())
  {
    Serial << "echo = " << echo << "\n\n";
  }
  delay(1000);

  long length = dev.call("length","what is my length?");
  checkCall("length");
  if (dev.callWasSuccessful())
  {
    Serial << "length = " << length << "\n\n";
  }
  delay(1000);

  bool starts_with = dev.call("startsWith","testing","te");
  checkCall("testing");
  if (dev.callWasSuccessful())
  {
    Serial << "starts_with = " << starts_with << "\n\n";
  }
  delay(1000);

  ArduinoJson::JsonArray& repeated_string = dev.call("repeat","hello",4);
  checkCall("repeat");
  if (dev.callWasSuccessful())
  {
    Serial << "repeated_string = ";
    repeated_string.printTo(Serial);
    Serial << "\n\n";
  }
  delay(1000);

}
