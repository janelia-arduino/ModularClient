// ----------------------------------------------------------------------------
// ModularClient.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "ModularClient.h"


ModularClient::ModularClient(Stream &stream) :
  json_stream_(stream)
{
  timeout_ = TIMEOUT_DEFAULT;
  call_successful_ = false;
  response_byte_count_ = 0;
}

int ModularClient::readResponseIntoBuffer(char response_buffer[], unsigned int buffer_size)
{
  return json_stream_.readJsonIntoBuffer(response_buffer,buffer_size);
}

int ModularClient::pipeResponse(Stream &stream)
{
  JsonStream json_stream(stream);
  return pipeResponse(json_stream);
}

int ModularClient::pipeResponse(JsonStream &json_stream)
{
  bool found_eol = false;
  char c;
  unsigned long start_millis = millis();
  int chars_piped = 0;
  while (!found_eol && ((millis() - start_millis) < timeout_))
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
}

ArduinoJson::JsonVariant ModularClient::processResponse()
{
  response_byte_count_ = readResponseIntoBuffer(response_,STRING_LENGTH_RESPONSE);
  StaticJsonBuffer<JSON_BUFFER_SIZE> json_buffer;
  ArduinoJson::JsonObject& root = json_buffer.parseObject(response_);
  call_successful_ = root["status"];
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
