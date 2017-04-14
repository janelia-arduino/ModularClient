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

void ModularClient::setDebugStream(Stream  & stream)
{
  debug_json_stream_.setStream(stream);
}

void ModularClient::removeDebugStream()
{
  debug_json_stream_.removeStream();
}

void ModularClient::initialize()
{
  call_successful_ = false;
  response_byte_count_ = 0;
}

int ModularClient::readResponseIntoBuffer(char response_buffer[], unsigned int buffer_size)
{
  return json_stream_.readJsonIntoBuffer(response_buffer,buffer_size);
}

int ModularClient::pipeResponse(Stream & stream)
{
  JsonStream json_stream(stream);
  return pipeResponse(json_stream);
}

int ModularClient::pipeResponse(JsonStream & json_stream)
{
  bool found_eol = false;
  char c;
  unsigned long start_millis = millis();
  int chars_piped = 0;
  while (!found_eol && ((millis() - start_millis) < constants::TIMEOUT_DEFAULT))
  {
    c = json_stream_.readChar();
    if (c >= 0)
    {
      json_stream.writeChar(c);
      chars_piped++;
      if (c == JsonStream::EOL)
      {
        found_eol = true;
      }
    }
  }
  if (found_eol)
  {
    return chars_piped;
  }
  else
  {
    return -1;
  }
}

void ModularClient::endRequest()
{
  json_stream_.endArray();
  json_stream_.writeNewline();
  if (debug_json_stream_.streamIsSet())
  {
    debug_json_stream_.endArray();
    debug_json_stream_.writeNewline();
  }
}

ArduinoJson::JsonVariant ModularClient::processResponse()
{
  response_byte_count_ = readResponseIntoBuffer(response_,constants::STRING_LENGTH_RESPONSE);
  Serial << "response_byte_count: " << response_byte_count_ << "\n";
  if (debug_json_stream_.streamIsSet())
  {
    debug_json_stream_.writeJson(response_);
    debug_json_stream_.writeNewline();
  }
  StaticJsonBuffer<constants::JSON_BUFFER_SIZE> json_buffer;
  ArduinoJson::JsonObject & root = json_buffer.parseObject(response_);
  call_successful_  = (root.containsKey("result") ? true : false);
  return root["result"];
}

bool ModularClient::callWasSuccessful()
{
  return call_successful_;
}

int ModularClient::getResponseByteCount()
{
  return response_byte_count_;
}
