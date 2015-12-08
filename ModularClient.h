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
  ArduinoJson::JsonVariant callServerMethod(const T method);
  template<typename T,
           typename A>
  ArduinoJson::JsonVariant callServerMethod(const T method,
                                            const A parameter0);
  template<typename T,
           typename A,
           typename B>
  ArduinoJson::JsonVariant callServerMethod(const T method,
                                            const A parameter0,
                                            const B parameter1);
  template<typename T,
           typename A,
           typename B,
           typename C>
  ArduinoJson::JsonVariant callServerMethod(const T method,
                                            const A parameter0,
                                            const B parameter1,
                                            const C parameter2);
  template<typename T,
           typename A,
           typename B,
           typename C,
           typename D>
  ArduinoJson::JsonVariant callServerMethod(const T method,
                                            const A parameter0,
                                            const B parameter1,
                                            const C parameter2,
                                            const D parameter3);
  template<typename T,
           typename A,
           typename B,
           typename C,
           typename D,
           typename E>
  ArduinoJson::JsonVariant callServerMethod(const T method,
                                            const A parameter0,
                                            const B parameter1,
                                            const C parameter2,
                                            const D parameter3,
                                            const E parameter4);
  template<typename T,
           typename A,
           typename B,
           typename C,
           typename D,
           typename E,
           typename F>
  ArduinoJson::JsonVariant callServerMethod(const T method,
                                            const A parameter0,
                                            const B parameter1,
                                            const C parameter2,
                                            const D parameter3,
                                            const E parameter4,
                                            const F parameter5);
  template<typename T,
           typename A,
           typename B,
           typename C,
           typename D,
           typename E,
           typename F,
           typename G>
  ArduinoJson::JsonVariant callServerMethod(const T method,
                                            const A parameter0,
                                            const B parameter1,
                                            const C parameter2,
                                            const D parameter3,
                                            const E parameter4,
                                            const F parameter5,
                                            const G parameter6);
  template<typename T,
           typename A,
           typename B,
           typename C,
           typename D,
           typename E,
           typename F,
           typename G,
           typename H>
  ArduinoJson::JsonVariant callServerMethod(const T method,
                                            const A parameter0,
                                            const B parameter1,
                                            const C parameter2,
                                            const D parameter3,
                                            const E parameter4,
                                            const F parameter5,
                                            const G parameter6,
                                            const H parameter7);
  bool callWasSuccessful();
  int getResponseByteCount();
private:
  template<typename T>
  void beginRequest(const T method);
  template<typename T>
  void addParameter(const T parameter);
  void endRequest();
  int readResponseIntoBuffer(char response_buffer[], unsigned int buffer_size);
  int pipeResponse(Stream &stream);
  int pipeResponse(JsonStream &json_stream);
  // ArduinoJson::JsonObject& sendRequestGetResponse(char response[STRING_LENGTH_RESPONSE], ArduinoJson::StaticJsonBuffer<JSON_BUFFER_SIZE>& buffer);
  ArduinoJson::JsonVariant processResponse();
  char response_[STRING_LENGTH_RESPONSE];
  bool call_successful_;
  int response_byte_count_;
  JsonStream json_stream_;
  unsigned int timeout_;
};
#include "ModularClientDefinitions.h"

#endif
