// LedController Client
#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonStream.h"
#include "Array.h"
#include "ConstantVariable.h"
#include "ModularDevice.h"


const int BAUDRATE = 9600;
ModularDevice dev(Serial2);
const unsigned char serial2_rx_pin = 17;

void setup()
{
  Serial.begin(BAUDRATE);
  Serial2.begin(BAUDRATE);
  pinMode(serial2_rx_pin,INPUT);
  digitalWrite(serial2_rx_pin,HIGH);
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
  dev.callServerMethod("setLedOn");
  checkCall("setLedOn");
  delay(1000);

  dev.callServerMethod("setLedOff");
  checkCall("setLedOff");
  delay(1000);

  long led_pin = dev.callServerMethod("getLedPin");
  checkCall("getLedPin");
  if (dev.callWasSuccessful())
  {
    Serial << "led_pin = " << led_pin << "\n\n";
  }
  delay(1000);

  dev.callServerMethod("badMethod",true,0.5,false);
  checkCall("badMethod");
  delay(1000);

  dev.callServerMethod("blinkLed",0.5,0.5,10);
  checkCall("blinkLed");
  delay(10000);

}
