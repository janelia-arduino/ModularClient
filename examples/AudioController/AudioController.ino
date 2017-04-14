#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonStream.h"
#include "Array.h"
#include "ConstantVariable.h"
#include "ModularClient.h"


const long BAUDRATE = 115200;
ModularClient dev(Serial3);
const size_t serial3_rx_pin = 7;

void setup()
{
  Serial.begin(BAUDRATE);
  Serial3.begin(BAUDRATE);
  pinMode(serial3_rx_pin,INPUT_PULLUP);

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
  dev.callServerMethod("playTone","4000","ALL");
  checkCall("playTone");
  delay(1000);

  dev.callServerMethod("playNoise","LEFT");
  checkCall("playNoise");
  delay(1000);

  dev.callServerMethod("stop");
  checkCall("stop");
  delay(1000);
}
