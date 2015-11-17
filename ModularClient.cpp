// ----------------------------------------------------------------------------
// ModularClient.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "ModularClient.h"


ModularClient::ModularClient(GenericSerialBase &serial) :
  request_(serial)
{
  client_serial_ptr_ = &serial;
}

size_t ModularClient::sendRequestGetResponse(char response[], size_t response_size)
{
  request_.stopArray();
  request_.linefeed();
  size_t bytes_read = client_serial_ptr_->getStream().readBytesUntil(JsonPrinter::EOL,response,response_size);
  response[bytes_read] = 0;
  return bytes_read;
}
