// ----------------------------------------------------------------------------
// ModularDevice.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "ModularDevice.h"


ModularDevice::ModularDevice(Stream &stream) :
  json_stream_(stream),
  debug_json_stream_(Serial)
{
  timeout_ = TIMEOUT_DEFAULT;
  call_successful_ = false;
  response_byte_count_ = 0;
}

int ModularDevice::readResponseIntoBuffer(char response_buffer[], unsigned int buffer_size)
{
  return json_stream_.readJsonIntoBuffer(response_buffer,buffer_size);
}

int ModularDevice::pipeResponse(Stream &stream)
{
  JsonStream json_stream(stream);
  return pipeResponse(json_stream);
}

int ModularDevice::pipeResponse(JsonStream &json_stream)
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

void ModularDevice::endRequest()
{
  json_stream_.endArray();
  json_stream_.writeNewline();
  debug_json_stream_.endArray();
  debug_json_stream_.writeNewline();
}

ArduinoJson::JsonVariant ModularDevice::processResponse()
{
  response_byte_count_ = readResponseIntoBuffer(response_,STRING_LENGTH_RESPONSE);
  Serial << "response_byte_count: " << response_byte_count_ << "\n";
  debug_json_stream_.writeJson(response_);
  debug_json_stream_.writeNewline();
  StaticJsonBuffer<JSON_BUFFER_SIZE> json_buffer;
  ArduinoJson::JsonObject& root = json_buffer.parseObject(response_);
  call_successful_  = (root.containsKey("error") ? false : true);
  return root["result"];
}

bool ModularDevice::callWasSuccessful()
{
  return call_successful_;
}

int ModularDevice::getResponseByteCount()
{
  return response_byte_count_;
}
