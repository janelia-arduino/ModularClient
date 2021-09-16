// ----------------------------------------------------------------------------
// ModularClient.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "../ModularClient.h"


using namespace modular_client;

ModularClient::ModularClient()
{
  initialize();
}

ModularClient::ModularClient(Stream & stream) :
json_stream_(stream)
{
  initialize();
}

void ModularClient::setStream(Stream  & stream)
{
  json_stream_.setStream(stream);
}

Stream & ModularClient::getStream()
{
  return json_stream_.getStream();
}

void ModularClient::removeStream()
{
  json_stream_.removeStream();
}

void ModularClient::setDebugStream(Stream  & stream)
{
  debug_json_stream_.setStream(stream);
}

Stream & ModularClient::getDebugStream()
{
  return debug_json_stream_.getStream();
}

void ModularClient::removeDebugStream()
{
  debug_json_stream_.removeStream();
}

void ModularClient::enable()
{
  enabled_ = true;
}

void ModularClient::disable()
{
  enabled_ = false;
}

bool ModularClient::enabled()
{
  return enabled_;
}

bool ModularClient::callWasSuccessful()
{
  return call_successful_;
}

ModularClient::address_t ModularClient::getAddress()
{
  return address_;
}

void ModularClient::removeAddress()
{
  address_.clear();
}

void ModularClient::setName(const ConstantString & name)
{
  name_ptr_ = &name;
}

bool ModularClient::compareName(const char * name_to_compare)
{
  char name_str[name_ptr_->length()+1];
  name_str[0] = '\0';
  name_ptr_->copy(name_str);
  return String(name_str).equalsIgnoreCase(name_to_compare);
}

bool ModularClient::compareName(const ConstantString & name_to_compare)
{
  return (&name_to_compare == name_ptr_);
}

const ConstantString & ModularClient::getName()
{
  return *name_ptr_;
}

void ModularClient::initialize()
{
  enabled_ = true;
  call_successful_ = false;
  setName(constants::empty_constant_string);
}

void ModularClient::endRequest()
{
  if (!enabled_)
  {
    return;
  }
  json_stream_.endArray();

  if (address_.size() > 0)
  {
    json_stream_.endArray();
  }

  json_stream_.writeNewline();

  if (debug_json_stream_.streamIsSet())
  {
    debug_json_stream_.endArray();

    if (address_.size() > 0)
    {
      debug_json_stream_.endArray();
    }

    debug_json_stream_.writeNewline();
  }
}

ArduinoJson::JsonVariant ModularClient::processResponse(JsonDocument & json_document)
{
  call_successful_ = false;
  if (!enabled_)
  {
    return json_document.to<ArduinoJson::JsonObject>();
  }

  DeserializationError error = deserializeJson(json_document,json_stream_.getStream());
  json_stream_.clear();

  if (error)
  {
    return json_document.to<ArduinoJson::JsonObject>();
  }
  ArduinoJson::JsonObject obj = json_document.as<ArduinoJson::JsonObject>();
  call_successful_ = (obj.containsKey("result") ? true : false);
  if (!call_successful_)
  {
    return obj;
  }
  return obj["result"];
}

void ModularClient::checkResponse()
{
  if (!enabled_)
  {
    call_successful_ = false;
    return;
  }
  call_successful_ = json_stream_.readJsonAndFind(constants::result_key_string);
}
