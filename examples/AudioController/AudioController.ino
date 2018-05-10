#include <Arduino.h>
#include <Streaming.h>
#include <ArduinoJson.h>
#include <ModularClient.h>


const long BAUD = 2000000;
HardwareSerial & serial = Serial1;
ModularClient dev(serial);

void setup()
{
  Serial.begin(BAUD);
  serial.begin(BAUD);
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
  double volume = dev.callGetResult(json_buffer,"volume");
  if (dev.callWasSuccessful())
  {
    Serial << "volume: " << volume << "\n\n";
  }
  else
  {
    Serial << "? not successful!\n\n";
  }
  delay(1000);

  StaticJsonBuffer<256> json_buffer2;
  JsonObject & device_id = dev.callGetResult(json_buffer2,"getDeviceId");
  const char * device_name = device_id["name"];
  if (dev.callWasSuccessful())
  {
    Serial << "device_name: " << device_name << "\n\n";
  }
  else
  {
    Serial << "? not successful!\n\n";
  }
  delay(1000);

}
