// ----------------------------------------------------------------------------
// Client.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _MODULAR_CLIENT_CLIENT_H_
#define _MODULAR_CLIENT_CLIENT_H_
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonSanitizer.h"
#include "Array.h"
#include "MemoryFree.h"
#include "ConstantVariable.h"
#include "GenericSerial.h"
#include "Parameter.h"
#include "Method.h"
#include "SavedVariable.h"
#include "Constants.h"
#include "JsonPrinter.h"


namespace ModularClient
{
class Client
{
public:
  Client(GenericSerialBase &serial);
  void addClientSerial(GenericSerialBase &serial);
  void setName(const ConstantString &name);
  void setModelNumber(const unsigned int model_number);
  void setSerialNumber(const unsigned int serial_number);
  void setFirmwareVersion(const unsigned char firmware_major,const unsigned char firmware_minor,const unsigned char firmware_patch);
  Method& createMethod(const ConstantString &method_name);
  Method& copyMethod(Method method,const ConstantString &method_name);
  Parameter& createParameter(const ConstantString &parameter_name);
  Parameter& copyParameter(Parameter parameter,const ConstantString &parameter_name);
  ArduinoJson::JsonVariant getParameterValue(const ConstantString &name);
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
  void resetDefaults();
  void startClient(const int baudrate);
  void handleRequest();
private:
  Array<GenericSerialBase*,constants::CLIENT_SERIAL_COUNT_MAX> client_serial_ptr_array_;
  unsigned char client_serial_index_;
  char request_[constants::STRING_LENGTH_REQUEST];
  ArduinoJson::JsonArray *request_json_array_ptr_;
  Array<Method,constants::METHOD_COUNT_MAX> method_array_;
  Array<Parameter,constants::PARAMETER_COUNT_MAX> parameter_array_;
  Array<SavedVariable,constants::SAVED_VARIABLE_COUNT_MAX> saved_variable_array_;
  const ConstantString *name_ptr_;
  unsigned int model_number_;
  unsigned char firmware_major_;
  unsigned char firmware_minor_;
  unsigned char firmware_patch_;
  int request_method_index_;
  int parameter_count_;
  JsonPrinter response_;
  bool error_;
  unsigned int eeprom_index_;
  const ConstantString *eeprom_init_name_ptr_;
  bool eeprom_uninitialized_;
  unsigned int eeprom_initialized_index_;

  void processRequestArray();
  int processMethodString(const char *method_string);
  int findMethodIndex(const char *method_name);
  int findMethodIndex(const ConstantString &method_name);
  int countJsonArrayElements(ArduinoJson::JsonArray &json_array);
  void executeMethod();
  void methodHelp(int method_index);
  void verboseMethodHelp(int method_index);
  int processParameterString(const char *parameter_string);
  int findParameterIndex(const char *parameter_name);
  int findParameterIndex(const ConstantString &parameter_name);
  void parameterHelp(Parameter &parameter);
  bool checkParameters();
  bool checkParameter(int parameter_index, ArduinoJson::JsonVariant &json_value);
  int findSavedVariableIndex(const ConstantString &saved_variable_name);
  unsigned int getSerialNumber();
  void initializeEeprom();
  void incrementClientSerial();

  // reserved methods
  void getClientInfoCallback();
  void getMethodIdsCallback();
  void getResponseCodesCallback();
  void getParametersCallback();
  void help();
  void verboseHelp();
};
}
#include "ClientDefinitions.h"

#endif
