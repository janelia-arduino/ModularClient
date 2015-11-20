// ----------------------------------------------------------------------------
// ModularClient.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "ModularClient.h"


ModularClient::ModularClient(GenericSerialBase &serial) :
  json_stream_(serial)
{
  client_serial_ptr_ = &serial;
  timeout_ = TIMEOUT_DEFAULT;
}

void ModularClient::endRequest()
{
  json_stream_.endArray();
  json_stream_.linefeed();
}

bool ModularClient::getResponse(char response_buffer[], unsigned int buffer_size)
{
  bool found_eol = false;
  unsigned int bytes_read = client_serial_ptr_->getStream().readBytesUntil(JsonStream::EOL,response_buffer,buffer_size-1);
  if ((bytes_read > 0) && (bytes_read < (buffer_size-1)))
  {
    found_eol = true;
  }
  else
  {
    // set response_buffer to empty string
    bytes_read = 0;
    // clear stream of remaining characters
    client_serial_ptr_->getStream().find(JsonStream::EOL);
  }
  response_buffer[bytes_read] = 0;
  return found_eol;
}

bool ModularClient::pipeResponse(GenericSerialBase &serial, unsigned int &chars_piped)
{
  bool found_eol = false;
  int c;
  unsigned long start_millis = millis();
  chars_piped = 0;
  while (!found_eol && ((millis() - start_millis) < timeout_))
  {
    c = client_serial_ptr_->getStream().read();
    if (c >= 0)
    {
      if ((char)c != JsonStream::EOL)
      {
        serial.getStream() << (char)c;
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

bool ModularClient::pipeResponse(GenericSerialBase &serial)
{
  unsigned int chars_piped;
  return pipeResponse(serial,chars_piped);
}

bool ModularClient::pipeResponse(JsonStream &json_stream, unsigned int &chars_piped)
{
  bool found_eol = false;
  int c;
  unsigned long start_millis = millis();
  chars_piped = 0;
  while (!found_eol && ((millis() - start_millis) < timeout_))
  {
    c = client_serial_ptr_->getStream().read();
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
