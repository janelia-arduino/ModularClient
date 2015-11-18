// ----------------------------------------------------------------------------
// ModularClient.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "ModularClient.h"


ModularClient::ModularClient(GenericSerialBase &serial) :
  json_printer_(serial)
{
  client_serial_ptr_ = &serial;
  timeout_ = TIMEOUT_DEFAULT;
}

void ModularClient::endRequest()
{
  json_printer_.endArray();
  json_printer_.linefeed();
}

bool ModularClient::getResponse(char response_buffer[], unsigned int buffer_size)
{
  bool found_eol = false;
  unsigned int bytes_read = client_serial_ptr_->getStream().readBytesUntil(JsonPrinter::EOL,response_buffer,buffer_size-1);
  if ((bytes_read > 0) && (bytes_read < (buffer_size-1)))
  {
    found_eol = true;
  }
  else
  {
    // set response_buffer to empty string
    bytes_read = 0;
    // clear stream of remaining characters
    client_serial_ptr_->getStream().find(JsonPrinter::EOL);
  }
  response_buffer[bytes_read] = 0;
  return found_eol;
}

bool ModularClient::pipeResponse(GenericSerialBase &serial, unsigned int &bytes_piped)
{
  bool found_eol = false;
  int c;
  unsigned long start_millis = millis();
  bytes_piped = 0;
  while (!found_eol && ((millis() - start_millis) < timeout_))
  {
    c = client_serial_ptr_->getStream().read();
    if (c >= 0)
    {
      if ((char)c != JsonPrinter::EOL)
      {
        serial.getStream() << (char)c;
        bytes_piped++;
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
  unsigned int bytes_piped;
  return pipeResponse(serial,bytes_piped);
}
