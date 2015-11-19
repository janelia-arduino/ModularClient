// ----------------------------------------------------------------------------
// ModularClient.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MODULAR_CLIENT_H
#define MODULAR_CLIENT_H
#include "Arduino.h"
#include "ArduinoJson.h"
#include "JsonPrinter.h"
#include "GenericSerial.h"


class ModularClient
{
public:
  static const unsigned int STRING_LENGTH_RESPONSE=257;
  static const unsigned int JSON_BUFFER_SIZE=200;
  static const unsigned int TIMEOUT_DEFAULT=1000;

  ModularClient(GenericSerialBase &serial);
  template<typename T>
  void beginRequest(const T method);
  template<typename T>
  void addParameter(const T parameter);
  void endRequest();
  bool getResponse(char response_buffer[], unsigned int buffer_size);
  bool pipeResponse(GenericSerialBase &serial, unsigned int &chars_piped);
  bool pipeResponse(GenericSerialBase &serial);
  bool pipeResponse(JsonPrinter &json_printer, unsigned int &chars_piped);
  bool pipeResponse(JsonPrinter &json_printer);
  // ArduinoJson::JsonObject& sendRequestGetResponse(char response[STRING_LENGTH_RESPONSE], ArduinoJson::StaticJsonBuffer<JSON_BUFFER_SIZE>& buffer);
private:
  GenericSerialBase* client_serial_ptr_;
  JsonPrinter json_printer_;
  unsigned int timeout_;
};
#include "ModularClientDefinitions.h"

#endif
