// ----------------------------------------------------------------------------
// ModularClient.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MODULAR_DEVICE_H
#define MODULAR_DEVICE_H
#include "Arduino.h"
#include "ArduinoJson.h"
#include "JsonStream.h"

#include "utility/Constants.h"


class ModularClient
{
public:
  ModularClient();
  ModularClient(Stream & stream);
  void setStream(Stream & stream);
  void setDebugStream(Stream & stream);
  void removeDebugStream();
  // template<typename T>
  // ArduinoJson::JsonVariant callServerMethod(const T method);
  // template<typename T,
  //          typename A>
  // ArduinoJson::JsonVariant callServerMethod(const T method,
  //                                           const A parameter0);
  // template<typename T,
  //          typename A,
  //          typename B>
  // ArduinoJson::JsonVariant callServerMethod(const T method,
  //                                           const A parameter0,
  //                                           const B parameter1);
  // template<typename T,
  //          typename A,
  //          typename B,
  //          typename C>
  // ArduinoJson::JsonVariant callServerMethod(const T method,
  //                                           const A parameter0,
  //                                           const B parameter1,
  //                                           const C parameter2);
  // template<typename T,
  //          typename A,
  //          typename B,
  //          typename C,
  //          typename D>
  // ArduinoJson::JsonVariant callServerMethod(const T method,
  //                                           const A parameter0,
  //                                           const B parameter1,
  //                                           const C parameter2,
  //                                           const D parameter3);
  // template<typename T,
  //          typename A,
  //          typename B,
  //          typename C,
  //          typename D,
  //          typename E>
  // ArduinoJson::JsonVariant callServerMethod(const T method,
  //                                           const A parameter0,
  //                                           const B parameter1,
  //                                           const C parameter2,
  //                                           const D parameter3,
  //                                           const E parameter4);
  // template<typename T,
  //          typename A,
  //          typename B,
  //          typename C,
  //          typename D,
  //          typename E,
  //          typename F>
  // ArduinoJson::JsonVariant callServerMethod(const T method,
  //                                           const A parameter0,
  //                                           const B parameter1,
  //                                           const C parameter2,
  //                                           const D parameter3,
  //                                           const E parameter4,
  //                                           const F parameter5);
  // template<typename T,
  //          typename A,
  //          typename B,
  //          typename C,
  //          typename D,
  //          typename E,
  //          typename F,
  //          typename G>
  // ArduinoJson::JsonVariant callServerMethod(const T method,
  //                                           const A parameter0,
  //                                           const B parameter1,
  //                                           const C parameter2,
  //                                           const D parameter3,
  //                                           const E parameter4,
  //                                           const F parameter5,
  //                                           const G parameter6);
  // template<typename T,
  //          typename A,
  //          typename B,
  //          typename C,
  //          typename D,
  //          typename E,
  //          typename F,
  //          typename G,
  //          typename H>
  // ArduinoJson::JsonVariant callServerMethod(const T method,
  //                                           const A parameter0,
  //                                           const B parameter1,
  //                                           const C parameter2,
  //                                           const D parameter3,
  //                                           const E parameter4,
  //                                           const F parameter5,
  //                                           const G parameter6,
  //                                           const H parameter7);
  template<typename T>
  void call(const T method);
  template<typename T,
           typename A>
  void call(const T method,
            const A parameter0);
  template<typename T,
           typename A,
           typename B>
  void call(const T method,
            const A parameter0,
            const B parameter1);
  template<typename T,
           typename A,
           typename B,
           typename C>
  void call(const T method,
            const A parameter0,
            const B parameter1,
            const C parameter2);
  template<typename T,
           typename A,
           typename B,
           typename C,
           typename D>
  void call(const T method,
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
  void call(const T method,
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
  void call(const T method,
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
  void call(const T method,
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
  void call(const T method,
            const A parameter0,
            const B parameter1,
            const C parameter2,
            const D parameter3,
            const E parameter4,
            const F parameter5,
            const G parameter6,
            const H parameter7);
  bool callWasSuccessful();

  // ArduinoJson::JsonVariant sendJsonRequest(ArduinoJson::JsonArray & request_array);

  // int getResponseByteCount();

private:
  bool call_successful_;
  JsonStream json_stream_;
  JsonStream debug_json_stream_;

  void initialize();
  template<typename T>
  void beginRequest(const T method);
  template<typename T>
  void addParameter(const T parameter);
  void endRequest();
  // int readResponseIntoBuffer(char response_buffer[], unsigned int buffer_size);
  // int pipeResponse(Stream & stream);
  // int pipeResponse(JsonStream & json_stream);
  // ArduinoJson::JsonObject & sendRequestGetResponse(char response[STRING_LENGTH_RESPONSE], ArduinoJson::StaticJsonBuffer<JSON_BUFFER_SIZE> & buffer);
  ArduinoJson::JsonVariant processResponse();
  void checkResponse();
};
#include "ModularClientDefinitions.h"

#endif
