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
  client_stream_ptr_ = &stream;
  timeout_ = TIMEOUT_DEFAULT;
}

void ModularClient::endRequest()
{
  json_stream_.endArray();
  json_stream_.writeNewline();
}

int ModularClient::readResponseIntoBuffer(char response_buffer[], unsigned int buffer_size)
{
  return json_stream_.readJsonIntoBuffer(response_buffer,buffer_size);
}

bool ModularClient::pipeResponse(Stream &stream, unsigned int &chars_piped)
{
  bool found_eol = false;
  int c;
  unsigned long start_millis = millis();
  chars_piped = 0;
  while (!found_eol && ((millis() - start_millis) < timeout_))
  {
    c = client_stream_ptr_->read();
    if (c >= 0)
    {
      if ((char)c != JsonStream::EOL)
      {
        stream << (char)c;
        chars_piped++;
      }
      else
      {
        found_eol = true;
      }
    }
  }
  return found_eol;
}

bool ModularClient::pipeResponse(Stream &stream)
{
  unsigned int chars_piped;
  return pipeResponse(stream,chars_piped);
}

bool ModularClient::pipeResponse(JsonStream &json_stream, unsigned int &chars_piped)
{
  bool found_eol = false;
  int c;
  unsigned long start_millis = millis();
  chars_piped = 0;
  while (!found_eol && ((millis() - start_millis) < timeout_))
  {
    c = client_stream_ptr_->read();
    if (c >= 0)
    {
      if ((char)c != JsonStream::EOL)
      {
        json_stream.writeChar(c);
        chars_piped++;
      }
      else
      {
        found_eol = true;
      }
    }
  }
  return found_eol;
}

bool ModularClient::pipeResponse(JsonStream &json_stream)
{
  unsigned int chars_piped;
  return pipeResponse(json_stream,chars_piped);
}
