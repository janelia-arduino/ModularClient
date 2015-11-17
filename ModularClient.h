// ----------------------------------------------------------------------------
// ModularClient.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MODULAR_CLIENT_H
#define MODULAR_CLIENT_H
#include "utility/Client.h"


namespace ModularClient
{
class Method;
void getMemoryFreeCallback();
void resetDefaultsCallback();
void setSerialNumberCallback();

class ModularClient
{
public:
  ModularClient(GenericSerialBase &serial);
  void addClientSerial(GenericSerialBase &serial);
  void setName(const ConstantString &client_name);
  void setModelNumber(const unsigned int model_number);
  void setFirmwareVersion(const unsigned char firmware_major,const unsigned char firmware_minor,const unsigned char firmware_patch);
  Method& createMethod(const ConstantString &method_name);
  Method& copyMethod(Method &method,const ConstantString &method_name);
  Parameter& createParameter(const ConstantString &parameter_name);
  Parameter& copyParameter(Parameter &parameter,const ConstantString &parameter_name);
  ArduinoJson::JsonVariant getParameterValue(const ConstantString &parameter_name);
  template<typename T>
  SavedVariable& createSavedVariable(const ConstantString &saved_variable_name,
                                     const T &default_value);
  template<typename T>
  SavedVariable& createSavedVariable(const ConstantString &saved_variable_name,
                                     const T default_value[],
                                     const unsigned int array_length);
  template<typename T>
  void setSavedVariableValue(const ConstantString &saved_variable_name,
                             const T &value);
  template<typename T>
  void setSavedVariableValue(const ConstantString &saved_variable_name,
                             const T value[],
                             const unsigned int array_index);
  template<typename T>
  void getSavedVariableValue(const ConstantString &saved_variable_name,
                             T &value);
  template<typename T>
  void getSavedVariableValue(const ConstantString &saved_variable_name,
                             T value[],
                             const unsigned int array_index);
  template<typename K>
  void addKeyToResponse(K key);
  template<typename T>
  void addToResponse(T value);
  template<typename K, typename T>
  void addToResponse(K key, T value);
  void addNullToResponse();
  template<typename K>
  void addNullToResponse(K key);
  template<typename T>
  void sendErrorResponse(T error);
  void addResultKeyToResponse();
  template<typename T>
  void addResultToResponse(T value);
  void startResponseObject();
  void stopResponseObject();
  void startResponseArray();
  void stopResponseArray();
  void startClient(const int baudrate);
  void handleClientRequests();
  void resetDefaults();
  void setSerialNumber(const unsigned int serial_number);
private:
  Client client_;
};
}
#include "ModularClientDefinitions.h"

#endif
