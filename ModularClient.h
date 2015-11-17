// ----------------------------------------------------------------------------
// ModularClient.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MODULAR_CLIENT_H
#define MODULAR_CLIENT_H
// #include "utility/Client.h"
#include "ArduinoJson.h"
#include "JsonPrinter.h"
#include "GenericSerial.h"


class ModularClient
{
public:
  static const unsigned int STRING_LENGTH_RESPONSE=257;
  static const unsigned int JSON_BUFFER_SIZE=200;

  ModularClient(GenericSerialBase &serial);
  template<typename T>
  void startRequest(const T method);
  template<typename T>
  void addParameter(const T parameter);
  size_t sendRequestGetResponse(char response[], size_t response_size);
  // ArduinoJson::JsonObject& sendRequestGetResponse(char response[STRING_LENGTH_RESPONSE], ArduinoJson::StaticJsonBuffer<JSON_BUFFER_SIZE>& buffer);
private:
  GenericSerialBase* client_serial_ptr_;
  JsonPrinter request_;
};
#include "ModularClientDefinitions.h"

#endif
