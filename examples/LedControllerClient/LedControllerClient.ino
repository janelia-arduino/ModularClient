// LedControllerClient
#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonStream.h"
#include "Array.h"
#include "ConstantVariable.h"
#include "ModularClient.h"


const int BAUDRATE = 9600;
ModularClient modular_client(Serial2);
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
  if (modular_client.callWasSuccessful())
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
  long led_pin = modular_client.callServerMethod("getLedPin");
  checkCall("getLedPin");
  if (modular_client.callWasSuccessful())
  {
    Serial << "led_pin = " << led_pin << "\n";
    Serial << "\n";
  }
  delay(1000);

  modular_client.callServerMethod("setLedOn");
  checkCall("setLedOn");
  delay(1000);

  modular_client.callServerMethod("setLedOff");
  checkCall("setLedOff");
  delay(1000);

  modular_client.callServerMethod("blinkLed",0.5,0.5,10);
  checkCall("blinkLed");
  delay(10000);

}
