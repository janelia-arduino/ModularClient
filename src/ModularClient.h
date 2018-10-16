// ----------------------------------------------------------------------------
// ModularClient.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef MODULAR_DEVICE_H
#define MODULAR_DEVICE_H
#include <Arduino.h>
#include <Streaming.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <ArduinoJson.h>
#include <JsonStream.h>

#include "ModularClient/Constants.h"


class ModularClient
{
public:
  ModularClient();
  ModularClient(Stream & stream);

  void setStream(Stream & stream);
  Stream & getStream();
  void removeStream();
  void setDebugStream(Stream & stream);
  Stream & getDebugStream();
  void removeDebugStream();

  void enable();
  void disable();
  bool enabled();

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

  template<typename T>
  void callUntilSuccessful(const T method);
  template<typename T,
    typename A>
  void callUntilSuccessful(const T method,
    const A parameter0);
  template<typename T,
    typename A,
    typename B>
  void callUntilSuccessful(const T method,
    const A parameter0,
    const B parameter1);
  template<typename T,
    typename A,
    typename B,
    typename C>
  void callUntilSuccessful(const T method,
    const A parameter0,
    const B parameter1,
    const C parameter2);
  template<typename T,
    typename A,
    typename B,
    typename C,
    typename D>
  void callUntilSuccessful(const T method,
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
  void callUntilSuccessful(const T method,
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
  void callUntilSuccessful(const T method,
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
  void callUntilSuccessful(const T method,
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
  void callUntilSuccessful(const T method,
    const A parameter0,
    const B parameter1,
    const C parameter2,
    const D parameter3,
    const E parameter4,
    const F parameter5,
    const G parameter6,
    const H parameter7);

  template<size_t N,
    typename T>
  ArduinoJson::JsonVariant callGetResult(StaticJsonBuffer<N> & json_buffer,
    const T method);
  template<size_t N,
    typename T,
    typename A>
  ArduinoJson::JsonVariant callGetResult(StaticJsonBuffer<N> & json_buffer,
    const T method,
    const A parameter0);
  template<size_t N,
    typename T,
    typename A,
    typename B>
  ArduinoJson::JsonVariant callGetResult(StaticJsonBuffer<N> & json_buffer,
    const T method,
    const A parameter0,
    const B parameter1);
  template<size_t N,
    typename T,
    typename A,
    typename B,
    typename C>
  ArduinoJson::JsonVariant callGetResult(StaticJsonBuffer<N> & json_buffer,
    const T method,
    const A parameter0,
    const B parameter1,
    const C parameter2);
  template<size_t N,
    typename T,
    typename A,
    typename B,
    typename C,
    typename D>
  ArduinoJson::JsonVariant callGetResult(StaticJsonBuffer<N> & json_buffer,
    const T method,
    const A parameter0,
    const B parameter1,
    const C parameter2,
    const D parameter3);
  template<size_t N,
    typename T,
    typename A,
    typename B,
    typename C,
    typename D,
    typename E>
  ArduinoJson::JsonVariant callGetResult(StaticJsonBuffer<N> & json_buffer,
    const T method,
    const A parameter0,
    const B parameter1,
    const C parameter2,
    const D parameter3,
    const E parameter4);
  template<size_t N,
    typename T,
    typename A,
    typename B,
    typename C,
    typename D,
    typename E,
    typename F>
  ArduinoJson::JsonVariant callGetResult(StaticJsonBuffer<N> & json_buffer,
    const T method,
    const A parameter0,
    const B parameter1,
    const C parameter2,
    const D parameter3,
    const E parameter4,
    const F parameter5);
  template<size_t N,
    typename T,
    typename A,
    typename B,
    typename C,
    typename D,
    typename E,
    typename F,
    typename G>
  ArduinoJson::JsonVariant callGetResult(StaticJsonBuffer<N> & json_buffer,
    const T method,
    const A parameter0,
    const B parameter1,
    const C parameter2,
    const D parameter3,
    const E parameter4,
    const F parameter5,
    const G parameter6);
  template<size_t N,
    typename T,
    typename A,
    typename B,
    typename C,
    typename D,
    typename E,
    typename F,
    typename G,
    typename H>
  ArduinoJson::JsonVariant callGetResult(StaticJsonBuffer<N> & json_buffer,
    const T method,
    const A parameter0,
    const B parameter1,
    const C parameter2,
    const D parameter3,
    const E parameter4,
    const F parameter5,
    const G parameter6,
    const H parameter7);

  bool callWasSuccessful();

  template<typename T>
  void setAddress(T & address_array);
  template <typename T, size_t N>
  void setAddress(const T (&address_array)[N]);
  typedef Array<size_t,modular_client::constants::ADDRESS_ID_COUNT_MAX> address_t;
  address_t getAddress();
  void removeAddress();

  // ArduinoJson::JsonVariant sendJsonRequest(ArduinoJson::JsonArray & request_array);

  void setName(const ConstantString & name);
  bool compareName(const char * name_to_compare);
  bool compareName(const ConstantString & name_to_compare);
  const ConstantString & getName();

private:
  JsonStream json_stream_;
  JsonStream debug_json_stream_;
  Array<size_t,modular_client::constants::ADDRESS_ID_COUNT_MAX> address_;
  bool enabled_;
  bool call_successful_;
  const ConstantString * name_ptr_;

  void initialize();
  template<typename T>
  void beginRequest(const T method);
  template<typename T>
  void addParameter(const T parameter);
  void endRequest();
  // ArduinoJson::JsonObject & sendRequestGetResponse(char response[STRING_LENGTH_RESPONSE], ArduinoJson::StaticJsonBuffer<JSON_BUFFER_SIZE> & buffer);
  template<size_t N>
  ArduinoJson::JsonVariant processResponse(StaticJsonBuffer<N> & json_buffer);
  void checkResponse();
};
#include "ModularClient/ModularClientDefinitions.h"

#endif
