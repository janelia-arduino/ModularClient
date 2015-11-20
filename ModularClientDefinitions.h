// ----------------------------------------------------------------------------
// ModularClientDefinitions.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MODULAR_CLIENT_DEFINITIONS_H
#define MODULAR_CLIENT_DEFINITIONS_H


template<typename T>
void ModularClient::beginRequest(const T method)
{
  json_stream_.beginArray();
  json_stream_.add(method);
}

template<typename T>
void ModularClient::addParameter(const T parameter)
{
  json_stream_.add(parameter);
}

#endif
