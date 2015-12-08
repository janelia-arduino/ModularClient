// TestModularClient
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

// void getLedPin()
// {
//   char response[ModularClient::STRING_LENGTH_RESPONSE];
//   StaticJsonBuffer<ModularClient::JSON_BUFFER_SIZE> json_buffer;

//   modular_client.beginRequest("getLedPin");
//   modular_client.endRequest();
//   int bytes_read = modular_client.readResponseIntoBuffer(response,ModularClient::STRING_LENGTH_RESPONSE);
//   Serial << "getLedPin bytes_read = " << bytes_read << "\n";
//   Serial << "response: " << "\n" << response << "\n";
// }

// void help()
// {
//   char response[ModularClient::STRING_LENGTH_RESPONSE];
//   StaticJsonBuffer<ModularClient::JSON_BUFFER_SIZE> json_buffer;

//   modular_client.beginRequest("?");
//   modular_client.endRequest();
//   int bytes_read = modular_client.readResponseIntoBuffer(response,ModularClient::STRING_LENGTH_RESPONSE);
//   Serial << "help bytes_read = " << bytes_read << "\n";
//   Serial << "response: " << "\n" << response << "\n";
// }

// void verboseHelp()
// {
//   modular_client.beginRequest("??");
//   modular_client.endRequest();
//   Serial << "verboseHelp: " << "\n";
//   int chars_piped = modular_client.pipeResponse(Serial);
//   Serial << "verboseHelp chars_piped = " << chars_piped << "\n";
// }

// void blinkLed()
// {
//   char response[ModularClient::STRING_LENGTH_RESPONSE];
//   StaticJsonBuffer<ModularClient::JSON_BUFFER_SIZE> json_buffer;

//   int test_delay = 500;

//   modular_client.beginRequest("blinkLed");
//   modular_client.addParameter(0.5);
//   modular_client.addParameter(0.5);
//   modular_client.addParameter(10);
//   modular_client.endRequest();
//   int bytes_read = modular_client.readResponseIntoBuffer(response,ModularClient::STRING_LENGTH_RESPONSE);
//   Serial << "blinkLed bytes_read = " << bytes_read << "\n";
//   Serial << "response: " << "\n" << response << "\n";
// }

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

void setup()
{
  Serial.begin(BAUDRATE);
  Serial2.begin(BAUDRATE);
  pinMode(serial2_rx_pin,INPUT);
  digitalWrite(serial2_rx_pin,HIGH);
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
