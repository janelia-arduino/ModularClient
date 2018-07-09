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
  call_successful_ = false;
  if (!enabled_)
  {
    return;
  }

  if (address_.size() > 0)
  {
    json_stream_.beginArray();
    json_stream_.write(modular_client::constants::forward_to_address_function_name);
    json_stream_.write(address_);
  }

  json_stream_.beginArray();
  json_stream_.write(method);

  if (debug_json_stream_.streamIsSet())
  {
    if (address_.size() > 0)
    {
      debug_json_stream_.beginArray();
      debug_json_stream_.write(modular_client::constants::forward_to_address_function_name);
      debug_json_stream_.write(address_);
    }

    debug_json_stream_.beginArray();
    debug_json_stream_.write(method);
  }
}

template<typename T>
void ModularClient::addParameter(const T parameter)
{
  if (!enabled_)
  {
    return;
  }
  json_stream_.write(parameter);
  if (debug_json_stream_.streamIsSet())
  {
    debug_json_stream_.write(parameter);
  }
}

template<typename T>
void ModularClient::call(const T method)
{
  beginRequest(method);
  endRequest();
  checkResponse();
}

template<typename T,
         typename A>
void ModularClient::call(const T method,
                         const A parameter0)
{
  beginRequest(method);
  addParameter(parameter0);
  endRequest();
  checkResponse();
}

template<typename T,
         typename A,
         typename B>
void ModularClient::call(const T method,
                         const A parameter0,
                         const B parameter1)
{
  beginRequest(method);
  addParameter(parameter0);
  addParameter(parameter1);
  endRequest();
  checkResponse();
}

template<typename T,
         typename A,
         typename B,
         typename C>
void ModularClient::call(const T method,
                         const A parameter0,
                         const B parameter1,
                         const C parameter2)
{
  beginRequest(method);
  addParameter(parameter0);
  addParameter(parameter1);
  addParameter(parameter2);
  endRequest();
  checkResponse();
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D>
void ModularClient::call(const T method,
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
  checkResponse();
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E>
void ModularClient::call(const T method,
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
  checkResponse();
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E,
         typename F>
void ModularClient::call(const T method,
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
  checkResponse();
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E,
         typename F,
         typename G>
void ModularClient::call(const T method,
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
  checkResponse();
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
void ModularClient::call(const T method,
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
  checkResponse();
}

template<typename T>
void ModularClient::callUntilSuccessful(const T method)
{
  do
  {
    beginRequest(method);
    endRequest();
    checkResponse();
    if (!enabled_)
    {
      break;
    }
  }
  while (!callWasSuccessful());
}

template<typename T,
         typename A>
void ModularClient::callUntilSuccessful(const T method,
                                        const A parameter0)
{
  do
  {
    beginRequest(method);
    addParameter(parameter0);
    endRequest();
    checkResponse();
    if (!enabled_)
    {
      break;
    }
  }
  while (!callWasSuccessful());
}

template<typename T,
         typename A,
         typename B>
void ModularClient::callUntilSuccessful(const T method,
                                        const A parameter0,
                                        const B parameter1)
{
  do
  {
    beginRequest(method);
    addParameter(parameter0);
    addParameter(parameter1);
    endRequest();
    checkResponse();
    if (!enabled_)
    {
      break;
    }
  }
  while (!callWasSuccessful());
}

template<typename T,
         typename A,
         typename B,
         typename C>
void ModularClient::callUntilSuccessful(const T method,
                                        const A parameter0,
                                        const B parameter1,
                                        const C parameter2)
{
  do
  {
    beginRequest(method);
    addParameter(parameter0);
    addParameter(parameter1);
    addParameter(parameter2);
    endRequest();
    checkResponse();
    if (!enabled_)
    {
      break;
    }
  }
  while (!callWasSuccessful());
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D>
void ModularClient::callUntilSuccessful(const T method,
                                        const A parameter0,
                                        const B parameter1,
                                        const C parameter2,
                                        const D parameter3)
{
  do
  {
    beginRequest(method);
    addParameter(parameter0);
    addParameter(parameter1);
    addParameter(parameter2);
    addParameter(parameter3);
    endRequest();
    checkResponse();
    if (!enabled_)
    {
      break;
    }
  }
  while (!callWasSuccessful());
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E>
void ModularClient::callUntilSuccessful(const T method,
                                        const A parameter0,
                                        const B parameter1,
                                        const C parameter2,
                                        const D parameter3,
                                        const E parameter4)
{
  do
  {
    beginRequest(method);
    addParameter(parameter0);
    addParameter(parameter1);
    addParameter(parameter2);
    addParameter(parameter3);
    addParameter(parameter4);
    endRequest();
    checkResponse();
    if (!enabled_)
    {
      break;
    }
  }
  while (!callWasSuccessful());
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E,
         typename F>
void ModularClient::callUntilSuccessful(const T method,
                                        const A parameter0,
                                        const B parameter1,
                                        const C parameter2,
                                        const D parameter3,
                                        const E parameter4,
                                        const F parameter5)
{
  do
  {
    beginRequest(method);
    addParameter(parameter0);
    addParameter(parameter1);
    addParameter(parameter2);
    addParameter(parameter3);
    addParameter(parameter4);
    addParameter(parameter5);
    endRequest();
    checkResponse();
    if (!enabled_)
    {
      break;
    }
  }
  while (!callWasSuccessful());
}

template<typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E,
         typename F,
         typename G>
void ModularClient::callUntilSuccessful(const T method,
                                        const A parameter0,
                                        const B parameter1,
                                        const C parameter2,
                                        const D parameter3,
                                        const E parameter4,
                                        const F parameter5,
                                        const G parameter6)
{
  do
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
    checkResponse();
    if (!enabled_)
    {
      break;
    }
  }
  while (!callWasSuccessful());
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
void ModularClient::callUntilSuccessful(const T method,
                                        const A parameter0,
                                        const B parameter1,
                                        const C parameter2,
                                        const D parameter3,
                                        const E parameter4,
                                        const F parameter5,
                                        const G parameter6,
                                        const H parameter7)
{
  do
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
    checkResponse();
    if (!enabled_)
    {
      break;
    }
  }
  while (!callWasSuccessful());
}

template<size_t N,
         typename T>
ArduinoJson::JsonVariant ModularClient::callGetResult(StaticJsonBuffer<N> & json_buffer,
                                                      const T method)
{
  beginRequest(method);
  endRequest();
  return processResponse(json_buffer);
}

template<size_t N,
         typename T,
         typename A>
ArduinoJson::JsonVariant ModularClient::callGetResult(StaticJsonBuffer<N> & json_buffer,
                                                      const T method,
                                                      const A parameter0)
{
  beginRequest(method);
  addParameter(parameter0);
  endRequest();
  return processResponse(json_buffer);
}

template<size_t N,
         typename T,
         typename A,
         typename B>
ArduinoJson::JsonVariant ModularClient::callGetResult(StaticJsonBuffer<N> & json_buffer,
                                                      const T method,
                                                      const A parameter0,
                                                      const B parameter1)
{
  beginRequest(method);
  addParameter(parameter0);
  addParameter(parameter1);
  endRequest();
  return processResponse(json_buffer);
}

template<size_t N,
         typename T,
         typename A,
         typename B,
         typename C>
ArduinoJson::JsonVariant ModularClient::callGetResult(StaticJsonBuffer<N> & json_buffer,
                                                      const T method,
                                                      const A parameter0,
                                                      const B parameter1,
                                                      const C parameter2)
{
  beginRequest(method);
  addParameter(parameter0);
  addParameter(parameter1);
  addParameter(parameter2);
  endRequest();
  return processResponse(json_buffer);
}

template<size_t N,
         typename T,
         typename A,
         typename B,
         typename C,
         typename D>
ArduinoJson::JsonVariant ModularClient::callGetResult(StaticJsonBuffer<N> & json_buffer,
                                                      const T method,
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
  return processResponse(json_buffer);
}

template<size_t N,
         typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E>
ArduinoJson::JsonVariant ModularClient::callGetResult(StaticJsonBuffer<N> & json_buffer,
                                                      const T method,
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
  return processResponse(json_buffer);
}

template<size_t N,
         typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E,
         typename F>
ArduinoJson::JsonVariant ModularClient::callGetResult(StaticJsonBuffer<N> & json_buffer,
                                                      const T method,
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
  return processResponse(json_buffer);
}

template<size_t N,
         typename T,
         typename A,
         typename B,
         typename C,
         typename D,
         typename E,
         typename F,
         typename G>
ArduinoJson::JsonVariant ModularClient::callGetResult(StaticJsonBuffer<N> & json_buffer,
                                                      const T method,
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
  return processResponse(json_buffer);
}

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
ArduinoJson::JsonVariant ModularClient::callGetResult(StaticJsonBuffer<N> & json_buffer,
                                                      const T method,
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
  return processResponse(json_buffer);
}

template<typename T>
void ModularClient::setAddress(T & address_array)
{
  if (address_array.size() <= address_.max_size())
  {
    removeAddress();
    for (size_t index=0; index<address_array.size(); ++index)
    {
      address_.push_back(address_array[index]);
    }
  }
}

template<typename T, size_t N>
void ModularClient::setAddress(const T (&address_array)[N])
{
  if (N <= address_.max_size())
  {
    removeAddress();
    address_.fill(address_array);
  }
}

template<size_t N>
ArduinoJson::JsonVariant ModularClient::processResponse(StaticJsonBuffer<N> & json_buffer)
{
  call_successful_ = false;
  if (!enabled_)
  {
    ArduinoJson::JsonObject& root = json_buffer.createObject();
    return root;
  }

  JsonObject& root = json_buffer.parseObject(json_stream_.getStream());
  json_stream_.clear();

  if (root.success())
  {
    call_successful_ = (root.containsKey("result") ? true : false);
  }
  if (!call_successful_)
  {
    return root;
  }
  return root["result"];
}

#endif
