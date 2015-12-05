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
#include "JsonStream.h"


class ModularClient
{
public:
  static const unsigned int STRING_LENGTH_RESPONSE=257;
  static const unsigned int JSON_BUFFER_SIZE=200;
  static const unsigned int TIMEOUT_DEFAULT=1000;

  ModularClient(Stream &stream);
  template<typename T>
  void beginRequest(const T method);
  template<typename T>
  void addParameter(const T parameter);
  void endRequest();
  int readResponseIntoBuffer(char response_buffer[], unsigned int buffer_size);
  int pipeResponse(Stream &stream);
  int pipeResponse(JsonStream &json_stream);
  // ArduinoJson::JsonObject& sendRequestGetResponse(char response[STRING_LENGTH_RESPONSE], ArduinoJson::StaticJsonBuffer<JSON_BUFFER_SIZE>& buffer);
private:
  JsonStream json_stream_;
  unsigned int timeout_;
};
#include "ModularClientDefinitions.h"

#endif
