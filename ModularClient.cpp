// ----------------------------------------------------------------------------
// ModularClient.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "ModularClient.h"


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

void ModularClient::initialize()
{
  call_successful_ = false;
}

void ModularClient::endRequest()
{
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

void ModularClient::checkResponse()
{
  call_successful_ = json_stream_.readJsonAndFind(constants::result_key_string);
}

