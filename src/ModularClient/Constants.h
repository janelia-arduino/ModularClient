// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MODULAR_CLIENT_CONSTANTS_H
#define MODULAR_CLIENT_CONSTANTS_H
#include <ConstantVariable.h>


namespace modular_client
{
namespace constants
{
#if !defined(__AVR_ATmega2560__)
enum{ADDRESS_ID_COUNT_MAX=16};
#else
enum{ADDRESS_ID_COUNT_MAX=1};
#endif

extern ConstantString result_key_string;
extern ConstantString empty_constant_string;

extern ConstantString forward_to_address_function_name;
}
}
#endif
