// ----------------------------------------------------------------------------
// ModularClientDefinitions.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MODULAR_DEVICE_DEFINITIONS_H
#define MODULAR_DEVICE_DEFINITIONS_H


template<typename T>
void ModularClient::beginRequest(const T method)
{
  json_stream_.beginArray();
  json_stream_.write(method);
  if (debug_json_stream_.streamIsSet())
  {
    debug_json_stream_.beginArray();
    debug_json_stream_.write(method);
  }
}

template<typename T>
void ModularClient::addParameter(const T parameter)
{
  json_stream_.write(parameter);
  if (debug_json_stream_.streamIsSet())
  {
    debug_json_stream_.write(parameter);
  }
}

template<typename T>
ArduinoJson::JsonVariant ModularClient::callServerMethod(const T method)
{
  beginRequest(method);
  endRequest();
  return processResponse();
}

template<typename T,
         typename A>
ArduinoJson::JsonVariant ModularClient::callServerMethod(const T method,
                                                         const A parameter0)
{
  beginRequest(method);
  addParameter(parameter0);
  endRequest();
  return processResponse();
}

template<typename T,
         typename A,
         typename B>
ArduinoJson::JsonVariant ModularClient::callServerMethod(const T method,
                                                         const A parameter0,
                                                         const B parameter1)
{
  beginRequest(method);
  addParameter(parameter0);
  addParameter(parameter1);
  endRequest();
  return processResponse();
}

template<typename T,
         typename A,
         typename B,
         typename C>
ArduinoJson::JsonVariant ModularClient::callServerMethod(const T method,
                                                         const A parameter0,
                                                         const B parameter1,
                                                         const C parameter2)
{
  beginRequest(method);
  addParameter(parameter0);
  addParameter(parameter1);
  addParameter(parameter2);
  endRequest();
  return processResponse();
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D>
ArduinoJson::JsonVariant ModularClient::callServerMethod(const T method,
                                                         const A parameter0,
                                                         const B parameter1,
                                                         const C parameter2,
                                                         const D parameter3)
{
  beginRequest(method);
  addParameter(parameter0);
  addParameter(parameter1);
  addParameter(parameter2);
  addParameter(parameter3);
  endRequest();
  return processResponse();
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E>
ArduinoJson::JsonVariant ModularClient::callServerMethod(const T method,
                                                         const A parameter0,
                                                         const B parameter1,
                                                         const C parameter2,
                                                         const D parameter3,
                                                         const E parameter4)
{
  beginRequest(method);
  addParameter(parameter0);
  addParameter(parameter1);
  addParameter(parameter2);
  addParameter(parameter3);
  addParameter(parameter4);
  endRequest();
  return processResponse();
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E,
         typename F>
ArduinoJson::JsonVariant ModularClient::callServerMethod(const T method,
                                                         const A parameter0,
                                                         const B parameter1,
                                                         const C parameter2,
                                                         const D parameter3,
                                                         const E parameter4,
                                                         const F parameter5)
{
  beginRequest(method);
  addParameter(parameter0);
  addParameter(parameter1);
  addParameter(parameter2);
  addParameter(parameter3);
  addParameter(parameter4);
  addParameter(parameter5);
  endRequest();
  return processResponse();
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E,
         typename F,
         typename G>
ArduinoJson::JsonVariant ModularClient::callServerMethod(const T method,
                                                         const A parameter0,
                                                         const B parameter1,
                                                         const C parameter2,
                                                         const D parameter3,
                                                         const E parameter4,
                                                         const F parameter5,
                                                         const G parameter6)
{
  beginRequest(method);
  addParameter(parameter0);
  addParameter(parameter1);
  addParameter(parameter2);
  addParameter(parameter3);
  addParameter(parameter4);
  addParameter(parameter5);
  addParameter(parameter6);
  endRequest();
  return processResponse();
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E,
         typename F,
         typename G,
         typename H>
ArduinoJson::JsonVariant ModularClient::callServerMethod(const T method,
                                                         const A parameter0,
                                                         const B parameter1,
                                                         const C parameter2,
                                                         const D parameter3,
                                                         const E parameter4,
                                                         const F parameter5,
                                                         const G parameter6,
                                                         const H parameter7)
{
  beginRequest(method);
  addParameter(parameter0);
  addParameter(parameter1);
  addParameter(parameter2);
  addParameter(parameter3);
  addParameter(parameter4);
  addParameter(parameter5);
  addParameter(parameter6);
  addParameter(parameter7);
  endRequest();
  return processResponse();
}
#endif