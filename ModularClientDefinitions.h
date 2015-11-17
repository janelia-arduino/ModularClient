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
void ModularClient::startRequest(const T method)
{
  request_.startArray();
  request_.add(method);
}

template<typename T>
void ModularClient::addParameter(const T parameter)
{
  request_.add(parameter);
}

#endif
