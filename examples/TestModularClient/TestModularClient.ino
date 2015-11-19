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
GenericSerial generic_serial(Serial);
GenericSerial1to3 generic_serial2(Serial2);
ModularClient modular_client(generic_serial2);

void getLedPin()
{
  char response[ModularClient::STRING_LENGTH_RESPONSE];
  StaticJsonBuffer<ModularClient::JSON_BUFFER_SIZE> json_buffer;

  modular_client.beginRequest("getLedPin");
  modular_client.endRequest();
  bool found_eol = modular_client.getResponse(response,ModularClient::STRING_LENGTH_RESPONSE);
  Serial << "getLedPin found_eol = " << found_eol << "\n";
  Serial << "response: " << "\n" << response << "\n";
}

void help()
{
  char response[ModularClient::STRING_LENGTH_RESPONSE];
  StaticJsonBuffer<ModularClient::JSON_BUFFER_SIZE> json_buffer;

  modular_client.beginRequest("?");
  modular_client.endRequest();
  bool found_eol = modular_client.getResponse(response,ModularClient::STRING_LENGTH_RESPONSE);
  Serial << "help found_eol = " << found_eol << "\n";
  Serial << "response: " << "\n" << response << "\n";
}

void verboseHelp()
{
  char response[ModularClient::STRING_LENGTH_RESPONSE];
  StaticJsonBuffer<ModularClient::JSON_BUFFER_SIZE> json_buffer;

  modular_client.beginRequest("??");
  modular_client.endRequest();
  Serial << "verboseHelp: " << "\n";
  unsigned int chars_piped;
  bool found_eol = modular_client.pipeResponse(generic_serial,chars_piped);
  // bool found_eol = modular_client.getResponse(response,ModularClient::STRING_LENGTH_RESPONSE);
  Serial << "\n";
  Serial << "verboseHelp found_eol = " << found_eol << "\n";
  Serial << "verboseHelp chars_piped = " << chars_piped << "\n";
  // Serial << "response: " << "\n" << response << "\n";
}

void blinkLed()
{
  char response[ModularClient::STRING_LENGTH_RESPONSE];
  StaticJsonBuffer<ModularClient::JSON_BUFFER_SIZE> json_buffer;

  int test_delay = 500;

  modular_client.beginRequest("blinkLed");
  modular_client.addParameter(0.5);
  modular_client.addParameter(0.5);
  modular_client.addParameter(10);
  modular_client.endRequest();
  bool found_eol = modular_client.getResponse(response,ModularClient::STRING_LENGTH_RESPONSE);
  Serial << "blinkLed found_eol = " << found_eol << "\n";
  Serial << "response: " << "\n" << response << "\n";
}

void setup()
{
  generic_serial.begin(BAUDRATE);
  generic_serial2.begin(BAUDRATE);
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
