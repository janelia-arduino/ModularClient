// TestModularClient
#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonPrinter.h"
#include "Array.h"
#include "ConstantVariable.h"
#include "GenericSerial.h"
#include "ModularClient.h"


const int BAUDRATE = 9600;
GenericSerial1to3 generic_serial(Serial2);
ModularClient modular_client(generic_serial);

void getLedPin()
{
  char response[ModularClient::STRING_LENGTH_RESPONSE];
  StaticJsonBuffer<ModularClient::JSON_BUFFER_SIZE> json_buffer;

  modular_client.startRequest("getLedPin");
  // ArduinoJson::JsonObject& response_object = modular_client.sendRequestGetResponse(response,json_buffer);
  size_t response_length = modular_client.sendRequestGetResponse(response,ModularClient::STRING_LENGTH_RESPONSE);
  Serial << "getLedPin response_length = " << response_length << "\n";
  Serial << "response: " << "\n" << response << "\n";
  // if (!response_object.success())
  // {
  //   Serial << "parseObject() failed" << "\n";
  // }
  // else
  // {
  //   response_object.printTo(Serial);
  //   Serial << "\n";
  // }
}

void help()
{
  char response[ModularClient::STRING_LENGTH_RESPONSE];
  StaticJsonBuffer<ModularClient::JSON_BUFFER_SIZE> json_buffer;

  modular_client.startRequest("?");
  // ArduinoJson::JsonObject& response_object = modular_client.sendRequestGetResponse(response,json_buffer);
  size_t response_length = modular_client.sendRequestGetResponse(response,ModularClient::STRING_LENGTH_RESPONSE);
  Serial << "help response_length = " << response_length << "\n";
  Serial << "response: " << "\n" << response << "\n";
  // if (!response_object.success())
  // {
  //   Serial << "parseObject() failed" << "\n";
  // }
  // else
  // {
  //   response_object.printTo(Serial);
  //   Serial << "\n";
  // }
}

void verboseHelp()
{
  char response[ModularClient::STRING_LENGTH_RESPONSE];
  StaticJsonBuffer<ModularClient::JSON_BUFFER_SIZE> json_buffer;

  modular_client.startRequest("??");
  // ArduinoJson::JsonObject& response_object = modular_client.sendRequestGetResponse(response,json_buffer);
  size_t response_length = modular_client.sendRequestGetResponse(response,ModularClient::STRING_LENGTH_RESPONSE);
  Serial << "verboseHelp response_length = " << response_length << "\n";
  Serial << "response: " << "\n" << response << "\n";
  // if (!response_object.success())
  // {
  //   Serial << "parseObject() failed" << "\n";
  // }
  // else
  // {
  //   response_object.printTo(Serial);
  //   Serial << "\n";
  // }
}

void blinkLed()
{
  char response[ModularClient::STRING_LENGTH_RESPONSE];
  StaticJsonBuffer<ModularClient::JSON_BUFFER_SIZE> json_buffer;

  int test_delay = 500;

  modular_client.startRequest("blinkLed");
  modular_client.addParameter(0.5);
  modular_client.addParameter(0.5);
  modular_client.addParameter(10);
  // ArduinoJson::JsonObject& response_object = modular_client.sendRequestGetResponse(response,json_buffer);
  size_t response_length = modular_client.sendRequestGetResponse(response,ModularClient::STRING_LENGTH_RESPONSE);
  Serial << "blinkLed response_length = " << response_length << "\n";
  Serial << "response: " << "\n" << response << "\n";

  // if (!response_object.success())
  // {
  //   Serial << "parseObject() failed" << "\n";
  // }
  // else
  // {
  //   response_object.printTo(Serial);
  //   Serial << "\n";
  // }
}

void setup()
{
  Serial.begin(BAUDRATE);
  generic_serial.begin(BAUDRATE);
}

void loop()
{
  getLedPin();
  delay(1000);

  blinkLed();
  delay(10000);

  help();
  delay(1000);

  verboseHelp();
  delay(1000);
}
