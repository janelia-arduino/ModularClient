#include <Arduino.h>
#include <Streaming.h>
#include <ArduinoJson.h>
#include <ModularClient.h>
#include <ConstantVariable.h>


const long BAUD = 2000000;
HardwareSerial & serial = Serial1;
ModularClient dev(serial);
CONSTANT_STRING(device_name_string,"audio_controller");

void setup()
{
  Serial.begin(BAUD);
  serial.begin(BAUD);

  dev.setName(device_name_string);
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

  StaticJsonDocument<80> json_document;
  double volume = dev.callGetResult(json_document,"volume");
  if (dev.callWasSuccessful())
  {
    Serial << "volume: " << volume << "\n\n";
  }
  else
  {
    Serial << "? not successful!\n\n";
  }
  delay(1000);

  StaticJsonDocument<256> json_document2;
  JsonObject device_id = dev.callGetResult(json_document2,"getDeviceId");
  const char * device_name = device_id["name"];
  if (dev.callWasSuccessful())
  {
    Serial << "device_name: " << device_name << "\n";
    if (dev.compareName(device_name))
    {
      Serial << "names match!\n\n";
    }
    else
    {
      Serial << "names do not match!\n\n";
    }
  }
  else
  {
    Serial << "? not successful!\n\n";
  }
  delay(1000);

}
