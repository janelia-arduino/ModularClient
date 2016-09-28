// StringController Client
#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonStream.h"
#include "Array.h"
#include "ConstantVariable.h"
#include "ModularClient.h"


const int BAUDRATE = 9600;
ModularClient dev(Serial2);
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
  const char* echo = dev.callServerMethod("echo","test",false);
  checkCall("echo");
  if (dev.callWasSuccessful())
  {
    Serial << "echo = " << echo << "\n\n";
  }
  delay(1000);

  long length = dev.callServerMethod("length","what is my length?");
  checkCall("length");
  if (dev.callWasSuccessful())
  {
    Serial << "length = " << length << "\n\n";
  }
  delay(1000);

  bool starts_with = dev.callServerMethod("startsWith","testing","te");
  checkCall("testing");
  if (dev.callWasSuccessful())
  {
    Serial << "starts_with = " << starts_with << "\n\n";
  }
  delay(1000);

  ArduinoJson::JsonArray& repeated_string = dev.callServerMethod("repeat","hello",4);
  checkCall("repeat");
  if (dev.callWasSuccessful())
  {
    Serial << "repeated_string = ";
    repeated_string.printTo(Serial);
    Serial << "\n\n";
  }
  delay(1000);

}
