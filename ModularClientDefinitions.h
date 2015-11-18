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
  json_printer_.beginArray();
  json_printer_.add(method);
}

template<typename T>
void ModularClient::addParameter(const T parameter)
{
  json_printer_.add(parameter);
}

#endif
