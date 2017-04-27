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
  dev.call("setLedOn");
  checkCall("setLedOn");
  delay(1000);

  dev.call("setLedOff");
  checkCall("setLedOff");
  delay(1000);

  long led_pin = dev.call("getLedPin");
  checkCall("getLedPin");
  if (dev.callWasSuccessful())
  {
    Serial << "led_pin = " << led_pin << "\n\n";
  }
  delay(1000);

  dev.call("badMethod",true,0.5,false);
  checkCall("badMethod");
  delay(1000);

  dev.call("blinkLed",0.5,0.5,10);
  checkCall("blinkLed");
  delay(10000);

}
