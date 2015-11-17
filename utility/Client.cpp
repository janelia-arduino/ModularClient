// ----------------------------------------------------------------------------
// Client.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Client.h"


namespace ModularClient
{
Client::Client(GenericSerialBase &serial) :
  response_(serial)
{
  addClientSerial(serial);
  setName(constants::empty_constant_string);
  model_number_ = 0;
  firmware_major_ = 0;
  firmware_minor_ = 0;
  firmware_patch_ = 0;
  request_method_index_ = -1;
  parameter_count_ = 0;
  error_ = false;
  client_serial_index_ = 0;

  Method& get_client_info_method = createMethod(constants::get_client_info_method_name);
  get_client_info_method.attachReservedCallback(&Client::getClientInfoCallback);

  Method& get_method_ids_method = createMethod(constants::get_method_ids_method_name);
  get_method_ids_method.attachReservedCallback(&Client::getMethodIdsCallback);

  Method& get_response_codes_method = createMethod(constants::get_response_codes_method_name);
  get_response_codes_method.attachReservedCallback(&Client::getResponseCodesCallback);

  Method& get_parameters_method = createMethod(constants::get_parameters_method_name);
  get_parameters_method.attachReservedCallback(&Client::getParametersCallback);

  Method& help_method = createMethod(constants::help_method_name);
  help_method.attachReservedCallback(&Client::help);

  Method& verbose_help_method = createMethod(constants::verbose_help_method_name);
  verbose_help_method.attachReservedCallback(&Client::verboseHelp);

  eeprom_index_ = 0;
  eeprom_initialized_index_ = eeprom_index_;
  eeprom_init_name_ptr_ = &constants::eeprom_initialized_saved_variable_name;
  eeprom_uninitialized_ = true;
  saved_variable_array_.push_back(SavedVariable(*eeprom_init_name_ptr_,
                                                eeprom_index_,
                                                constants::eeprom_initialized_value));
  eeprom_index_ += sizeof(constants::eeprom_initialized_value);
  createSavedVariable(constants::serial_number_constant_string,constants::serial_number_default);
}

void Client::addClientSerial(GenericSerialBase &serial)
{
  bool serial_found = false;
  for (unsigned int i=0;i<client_serial_ptr_array_.size();++i)
  {
    if (client_serial_ptr_array_[i] == &serial)
    {
      serial_found = true;
    }
  }
  if (!serial_found)
  {
    client_serial_ptr_array_.push_back(&serial);
  }
}

void Client::setName(const ConstantString &name)
{
  name_ptr_ = &name;
}

void Client::setModelNumber(const unsigned int model_number)
{
  model_number_ = model_number;
}

void Client::setSerialNumber(const unsigned int serial_number)
{
  setSavedVariableValue(constants::serial_number_constant_string,serial_number);
}

void Client::setFirmwareVersion(const unsigned char firmware_major,const unsigned char firmware_minor,const unsigned char firmware_patch)
{
  firmware_major_ = firmware_major;
  firmware_minor_ = firmware_minor;
  firmware_patch_ = firmware_patch;
}

Method& Client::createMethod(const ConstantString &method_name)
{
  int method_index = findMethodIndex(method_name);
  if (method_index < 0)
  {
    method_array_.push_back(Method(method_name));
    return method_array_.back();
  }
  else
  {
    method_array_[method_index] = Method(method_name);
    return method_array_[method_index];
  }
}

Method& Client::copyMethod(Method method,const ConstantString &method_name)
{
  method_array_.push_back(method);
  method_array_.back().setName(method_name);
  return method_array_.back();
}

Parameter& Client::createParameter(const ConstantString &parameter_name)
{
  int parameter_index = findParameterIndex(parameter_name);
  if (parameter_index < 0)
  {
    parameter_array_.push_back(Parameter(parameter_name));
    return parameter_array_.back();
  }
  else
  {
    parameter_array_[parameter_index] = Parameter(parameter_name);
    return parameter_array_[parameter_index];
  }
}

Parameter& Client::copyParameter(Parameter parameter,const ConstantString &parameter_name)
{
  parameter_array_.push_back(parameter);
  parameter_array_.back().setName(parameter_name);
  return parameter_array_.back();
}

ArduinoJson::JsonVariant Client::getParameterValue(const ConstantString &name)
{
  int parameter_index = findParameterIndex(name);
  return (*request_json_array_ptr_)[parameter_index+1];
}

void Client::addNullToResponse()
{
  response_.addNull();
}

void Client::addResultKeyToResponse()
{
  response_.addKey(constants::result_constant_string);
}

void Client::startResponseObject()
{
  response_.startObject();
}

void Client::stopResponseObject()
{
  response_.stopObject();
}

void Client::startResponseArray()
{
  response_.startArray();
}

void Client::stopResponseArray()
{
  response_.stopArray();
}

void Client::resetDefaults()
{
  for (unsigned int i=0; i<saved_variable_array_.size(); ++i)
  {
    saved_variable_array_[i].setDefaultValue();
  }
}

void Client::startClient(const int baudrate)
{
  if (eeprom_uninitialized_)
  {
    initializeEeprom();
  }
  for (unsigned int i=0;i<client_serial_ptr_array_.size();++i)
  {
    client_serial_ptr_array_[i]->begin(baudrate);
  }
}

void Client::handleRequest()
{
  while (client_serial_ptr_array_[client_serial_index_]->getStream().available() > 0)
  {
    int request_length = client_serial_ptr_array_[client_serial_index_]->getStream().readBytesUntil(constants::eol,request_,constants::STRING_LENGTH_REQUEST);
    if (request_length == 0)
    {
      continue;
    }
    request_[request_length] = 0;
    JsonSanitizer sanitizer(constants::JSON_TOKEN_MAX);
    if (sanitizer.firstCharIsValidJson(request_))
    {
      response_.setCompactPrint();
    }
    else
    {
      response_.setPrettyPrint();
    }
    response_.startObject();
    error_ = false;
    sanitizer.sanitize(request_,constants::STRING_LENGTH_REQUEST);
    StaticJsonBuffer<constants::STRING_LENGTH_REQUEST> json_buffer;
    if (sanitizer.firstCharIsValidJsonObject(request_))
    {
      addToResponse(constants::status_constant_string,JsonPrinter::ERROR);
      addToResponse(constants::error_message_constant_string,constants::object_request_error_message);
      error_ = true;
    }
    else
    {
      request_json_array_ptr_ = &(json_buffer.parseArray(request_));
      if (request_json_array_ptr_->success())
      {
        processRequestArray();
      }
      else
      {
        addToResponse(constants::status_constant_string,JsonPrinter::ERROR);
        addToResponse(constants::error_message_constant_string,constants::array_parse_error_message);
        addToResponse(constants::received_request_constant_string,request_);
        error_ = true;
      }
      if (!error_)
      {
        addToResponse(constants::status_constant_string,JsonPrinter::SUCCESS);
      }
    }
    response_.stopObject();
    client_serial_ptr_array_[client_serial_index_]->getStream() << endl;
  }
  incrementClientSerial();
}

void Client::processRequestArray()
{
  const char* method_string = (*request_json_array_ptr_)[0];
  request_method_index_ = processMethodString(method_string);
  if (!(request_method_index_ < 0))
  {
    int array_elements_count = countJsonArrayElements((*request_json_array_ptr_));
    int parameter_count = array_elements_count - 1;
    if ((parameter_count == 1) && (strcmp((*request_json_array_ptr_)[1],"?") == 0))
    {
      addKeyToResponse(constants::method_info_constant_string);
      methodHelp(request_method_index_);
    }
    else if ((parameter_count == 1) && (strcmp((*request_json_array_ptr_)[1],"??") == 0))
    {
      addKeyToResponse(constants::method_info_constant_string);
      verboseMethodHelp(request_method_index_);
    }
    else if ((parameter_count == 2) &&
             ((strcmp((*request_json_array_ptr_)[2],"?") == 0) ||
              (strcmp((*request_json_array_ptr_)[2],"??") == 0)))
    {
      int parameter_index = processParameterString((*request_json_array_ptr_)[1]);
      Parameter& parameter = *(method_array_[request_method_index_].parameter_ptr_array_[parameter_index]);
      addKeyToResponse(constants::parameter_info_constant_string);
      parameterHelp(parameter);
    }
    else if (parameter_count != method_array_[request_method_index_].parameter_count_)
    {
      addToResponse(constants::status_constant_string,JsonPrinter::ERROR);
      char incorrect_parameter_number[constants::incorrect_parameter_number_constant_string.length()+1];
      constants::incorrect_parameter_number_constant_string.copy(incorrect_parameter_number);
      char error_str[constants::STRING_LENGTH_ERROR];
      error_str[0] = 0;
      strcat(error_str,incorrect_parameter_number);
      char parameter_count_str[constants::STRING_LENGTH_PARAMETER_COUNT];
      dtostrf(parameter_count,0,0,parameter_count_str);
      strcat(error_str,parameter_count_str);
      strcat(error_str," given. ");
      dtostrf(method_array_[request_method_index_].parameter_count_,0,0,parameter_count_str);
      strcat(error_str,parameter_count_str);
      strcat(error_str," needed.");
      addToResponse(constants::error_message_constant_string,error_str);
      error_ = true;
    }
    else
    {
      bool parameters_ok = checkParameters();
      if (parameters_ok)
      {
        executeMethod();
      }
    }
  }
}

int Client::processMethodString(const char *method_string)
{
  int method_index = -1;
  int method_id = atoi(method_string);
  if (strcmp(method_string,"0") == 0)
  {
    method_index = 0;
    addToResponse(constants::method_id_constant_string,0);
  }
  else if (method_id > 0)
  {
    method_index = method_id;
    addToResponse(constants::method_id_constant_string,method_id);
  }
  else
  {
    method_index = findMethodIndex(method_string);
    addToResponse(constants::method_constant_string,method_string);
  }
  if ((method_index < 0) || (method_index >= (int)method_array_.size()))
  {
    addToResponse(constants::status_constant_string,JsonPrinter::ERROR);
    addToResponse(constants::error_message_constant_string,constants::unknown_method_constant_string);
    error_ = true;
    method_index = -1;
  }
  return method_index;
}

int Client::findMethodIndex(const char *method_name)
{
  int method_index = -1;
  for (unsigned int i=0; i<method_array_.size(); ++i)
  {
    if (method_array_[i].compareName(method_name))
    {
      method_index = i;
      break;
    }
  }
  return method_index;
}

int Client::findMethodIndex(const ConstantString &method_name)
{
  int method_index = -1;
  for (unsigned int i=0; i<method_array_.size(); ++i)
  {
    if (method_array_[i].compareName(method_name))
    {
      method_index = i;
      break;
    }
  }
  return method_index;
}

int Client::countJsonArrayElements(ArduinoJson::JsonArray &json_array)
{
  int elements_count = 0;
  for (ArduinoJson::JsonArray::iterator it=json_array.begin();
       it!=json_array.end();
       ++it)
  {
    elements_count++;
  }
  return elements_count;
}

void Client::executeMethod()
{
  if (method_array_[request_method_index_].isReserved())
  {
    method_array_[request_method_index_].reservedCallback(this);
  }
  else
  {
    method_array_[request_method_index_].callback();
  }
}

void Client::methodHelp(int method_index)
{
  startResponseObject();
  const ConstantString* method_name_ptr = method_array_[method_index].getNamePointer();
  addToResponse(constants::name_constant_string,method_name_ptr);

  addKeyToResponse(constants::parameters_constant_string);
  response_.startArray();
  Array<Parameter*,constants::METHOD_PARAMETER_COUNT_MAX>& parameter_ptr_array = method_array_[method_index].parameter_ptr_array_;
  const ConstantString* parameter_name_ptr;
  char parameter_name_char_array[constants::STRING_LENGTH_PARAMETER_NAME];
  for (unsigned int i=0; i<parameter_ptr_array.size(); ++i)
  {
    parameter_name_ptr = parameter_ptr_array[i]->getNamePointer();
    parameter_name_ptr->copy(parameter_name_char_array);
    addToResponse(parameter_name_char_array);
  }
  response_.stopArray();
  addToResponse(constants::result_type_constant_string,method_array_[method_index].getReturnType());
  stopResponseObject();
}

void Client::verboseMethodHelp(int method_index)
{
  startResponseObject();
  const ConstantString* method_name_ptr = method_array_[method_index].getNamePointer();
  addToResponse(constants::name_constant_string,method_name_ptr);

  addKeyToResponse(constants::parameters_constant_string);
  response_.startArray();
  Array<Parameter*,constants::METHOD_PARAMETER_COUNT_MAX>& parameter_ptr_array = method_array_[method_index].parameter_ptr_array_;
  for (unsigned int i=0; i<parameter_ptr_array.size(); ++i)
  {
    parameterHelp(*(parameter_ptr_array[i]));
  }
  response_.stopArray();
  addToResponse(constants::result_type_constant_string,method_array_[method_index].getReturnType());
  stopResponseObject();
}

int Client::processParameterString(const char *parameter_string)
{
  int parameter_index = -1;
  int parameter_id = atoi(parameter_string);
  if (strcmp(parameter_string,"0") == 0)
  {
    parameter_index = 0;
  }
  else if (parameter_id > 0)
  {
    parameter_index = parameter_id;
  }
  else
  {
    parameter_index = findParameterIndex(parameter_string);
  }
  Array<Parameter*,constants::METHOD_PARAMETER_COUNT_MAX>& parameter_ptr_array = method_array_[request_method_index_].parameter_ptr_array_;
  if ((parameter_index < 0) || (parameter_index >= (int)parameter_ptr_array.size()))
  {
    addToResponse(constants::status_constant_string,JsonPrinter::ERROR);
    addToResponse(constants::error_message_constant_string,constants::unknown_parameter_constant_string);
    error_ = true;
    parameter_index = -1;
  }
  return parameter_index;
}

int Client::findParameterIndex(const char *parameter_name)
{
  int parameter_index = -1;
  if (request_method_index_ >= 0)
  {
    Array<Parameter*,constants::METHOD_PARAMETER_COUNT_MAX>& parameter_ptr_array = method_array_[request_method_index_].parameter_ptr_array_;
    for (unsigned int i=0; i<parameter_ptr_array.size(); ++i)
    {
      if (parameter_ptr_array[i]->compareName(parameter_name))
      {
        parameter_index = i;
        break;
      }
    }
  }
  return parameter_index;
}

int Client::findParameterIndex(const ConstantString &parameter_name)
{
  int parameter_index = -1;
  if (request_method_index_ >= 0)
  {
    Array<Parameter*,constants::METHOD_PARAMETER_COUNT_MAX>& parameter_ptr_array = method_array_[request_method_index_].parameter_ptr_array_;
    for (unsigned int i=0; i<parameter_ptr_array.size(); ++i)
    {
      if (parameter_ptr_array[i]->compareName(parameter_name))
      {
        parameter_index = i;
        break;
      }
    }
  }
  return parameter_index;
}

void Client::parameterHelp(Parameter &parameter)
{
  startResponseObject();
  const ConstantString* parameter_name_ptr = parameter.getNamePointer();
  addToResponse(constants::name_constant_string,parameter_name_ptr);

  char parameter_units[constants::STRING_LENGTH_PARAMETER_UNITS];
  parameter_units[0] = 0;
  const ConstantString* parameter_units_ptr = parameter.getUnitsPointer();
  parameter_units_ptr->copy(parameter_units);
  if (strcmp(parameter_units,"") != 0)
  {
    addToResponse(constants::units_constant_string,parameter_units);
  }
  JsonPrinter::JsonTypes type = parameter.getType();
  switch (type)
  {
    case JsonPrinter::LONG_TYPE:
      {
        addToResponse(constants::type_constant_string,JsonPrinter::LONG_TYPE);
        if (parameter.rangeIsSet())
        {
          long min = parameter.getMin().l;
          long max = parameter.getMax().l;
          addToResponse(constants::min_constant_string,min);
          addToResponse(constants::max_constant_string,max);
        }
        break;
      }
    case JsonPrinter::DOUBLE_TYPE:
      {
        addToResponse(constants::type_constant_string,JsonPrinter::DOUBLE_TYPE);
        if (parameter.rangeIsSet())
        {
          double min = parameter.getMin().d;
          double max = parameter.getMax().d;
          addToResponse(constants::min_constant_string,min);
          addToResponse(constants::max_constant_string,max);
        }
        break;
      }
    case JsonPrinter::BOOL_TYPE:
      {
        addToResponse(constants::type_constant_string,JsonPrinter::BOOL_TYPE);
        break;
      }
    case JsonPrinter::STRING_TYPE:
      {
        addToResponse(constants::type_constant_string,JsonPrinter::STRING_TYPE);
        break;
      }
    case JsonPrinter::OBJECT_TYPE:
      {
        addToResponse(constants::type_constant_string,JsonPrinter::OBJECT_TYPE);
        break;
      }
    case JsonPrinter::ARRAY_TYPE:
      {
        addToResponse(constants::type_constant_string,JsonPrinter::ARRAY_TYPE);
        JsonPrinter::JsonTypes array_element_type = parameter.getArrayElementType();
        switch (array_element_type)
        {
          case JsonPrinter::LONG_TYPE:
            {
              addToResponse(constants::array_element_type_constant_string,JsonPrinter::LONG_TYPE);
              if (parameter.rangeIsSet())
              {
                long min = parameter.getMin().l;
                long max = parameter.getMax().l;
                addToResponse(constants::min_constant_string,min);
                addToResponse(constants::max_constant_string,max);
              }
              break;
            }
          case JsonPrinter::DOUBLE_TYPE:
            {
              addToResponse(constants::array_element_type_constant_string,JsonPrinter::DOUBLE_TYPE);
              if (parameter.rangeIsSet())
              {
                double min = parameter.getMin().d;
                double max = parameter.getMax().d;
                addToResponse(constants::min_constant_string,min);
                addToResponse(constants::max_constant_string,max);
              }
              break;
            }
          case JsonPrinter::BOOL_TYPE:
            {
              addToResponse(constants::array_element_type_constant_string,JsonPrinter::BOOL_TYPE);
              break;
            }
          case JsonPrinter::STRING_TYPE:
            {
              addToResponse(constants::array_element_type_constant_string,JsonPrinter::STRING_TYPE);
              break;
            }
          case JsonPrinter::OBJECT_TYPE:
            {
              addToResponse(constants::array_element_type_constant_string,JsonPrinter::OBJECT_TYPE);
              break;
            }
          case JsonPrinter::ARRAY_TYPE:
            {
              addToResponse(constants::array_element_type_constant_string,JsonPrinter::ARRAY_TYPE);
              break;
            }
        }
        break;
      }
  }
  stopResponseObject();
}

bool Client::checkParameters()
{
  int parameter_index = 0;
  for (ArduinoJson::JsonArray::iterator it=request_json_array_ptr_->begin();
       it!=request_json_array_ptr_->end();
       ++it)
  {
    if (it!=request_json_array_ptr_->begin())
    {
      if (checkParameter(parameter_index,*it))
      {
        parameter_index++;
      }
      else
      {
        return false;
      }
    }
  }
  parameter_count_ = parameter_index;
  return true;
}

bool Client::checkParameter(int parameter_index, ArduinoJson::JsonVariant &json_value)
{
  bool out_of_range = false;
  bool object_parse_unsuccessful = false;
  bool array_parse_unsuccessful = false;
  Parameter& parameter = *(method_array_[request_method_index_].parameter_ptr_array_[parameter_index]);
  JsonPrinter::JsonTypes type = parameter.getType();
  char min_str[JsonPrinter::STRING_LENGTH_DOUBLE];
  min_str[0] = 0;
  char max_str[JsonPrinter::STRING_LENGTH_DOUBLE];
  max_str[0] = 0;
  switch (type)
  {
    case JsonPrinter::LONG_TYPE:
      {
        if (parameter.rangeIsSet())
        {
          long value = (long)json_value;
          long min = parameter.getMin().l;
          long max = parameter.getMax().l;
          if ((value < min) || (value > max))
          {
            out_of_range = true;
            dtostrf(min,0,0,min_str);
            dtostrf(max,0,0,max_str);
          }
        }
        break;
      }
    case JsonPrinter::DOUBLE_TYPE:
      {
        if (parameter.rangeIsSet())
        {
          double value = (double)json_value;
          double min = parameter.getMin().d;
          double max = parameter.getMax().d;
          if ((value < min) || (value > max))
          {
            out_of_range = true;
            dtostrf(min,0,JsonPrinter::DOUBLE_DIGITS,min_str);
            dtostrf(max,0,JsonPrinter::DOUBLE_DIGITS,max_str);
          }
        }
        break;
      }
    case JsonPrinter::BOOL_TYPE:
      break;
    case JsonPrinter::STRING_TYPE:
      break;
    case JsonPrinter::OBJECT_TYPE:
      {
        ArduinoJson::JsonObject& json_object = json_value;
        if (!json_object.success())
        {
          object_parse_unsuccessful = true;
        }
        break;
      }
    case JsonPrinter::ARRAY_TYPE:
      {
        ArduinoJson::JsonArray& json_array = json_value;
        if (!json_array.success())
        {
          array_parse_unsuccessful = true;
        }
        else
        {
          JsonPrinter::JsonTypes array_element_type = parameter.getArrayElementType();
          switch (array_element_type)
          {
            case JsonPrinter::LONG_TYPE:
              {
                if (parameter.rangeIsSet())
                {
                  long value;
                  long min = parameter.getMin().l;
                  long max = parameter.getMax().l;
                  for (ArduinoJson::JsonArray::iterator it=json_array.begin();
                       it!=json_array.end();
                       ++it)
                  {
                    value = (long)*it;
                    if ((value < min) || (value > max))
                    {
                      out_of_range = true;
                      dtostrf(min,0,0,min_str);
                      dtostrf(max,0,0,max_str);
                      break;
                    }
                  }
                }
                break;
              }
            case JsonPrinter::DOUBLE_TYPE:
              {
                if (parameter.rangeIsSet())
                {
                  double value;
                  double min = parameter.getMin().d;
                  double max = parameter.getMax().d;
                  for (ArduinoJson::JsonArray::iterator it=json_array.begin();
                       it!=json_array.end();
                       ++it)
                  {
                    value = (double)*it;
                    if ((value < min) || (value > max))
                    {
                      out_of_range = true;
                      dtostrf(min,0,JsonPrinter::DOUBLE_DIGITS,min_str);
                      dtostrf(max,0,JsonPrinter::DOUBLE_DIGITS,max_str);
                      break;
                    }
                  }
                }
                break;
              }
            case JsonPrinter::BOOL_TYPE:
              {
                break;
              }
            case JsonPrinter::STRING_TYPE:
              {
                break;
              }
            case JsonPrinter::OBJECT_TYPE:
              {
                break;
              }
            case JsonPrinter::ARRAY_TYPE:
              {
                break;
              }
          }
        }
        break;
      }
  }
  if (out_of_range)
  {
    addToResponse(constants::status_constant_string,JsonPrinter::ERROR);
    char error_str[constants::STRING_LENGTH_ERROR];
    error_str[0] = 0;
    if (type != JsonPrinter::ARRAY_TYPE)
    {
      constants::parameter_error_preamble_message.copy(error_str);
    }
    else
    {
      constants::array_parameter_error_preamble_message.copy(error_str);
    }
    strcat(error_str,min_str);
    strcat(error_str," <= ");
    char parameter_name[constants::STRING_LENGTH_PARAMETER_NAME];
    parameter_name[0] = 0;
    const ConstantString* parameter_name_ptr = parameter.getNamePointer();
    parameter_name_ptr->copy(parameter_name);
    strcat(error_str,parameter_name);
    if (type == JsonPrinter::ARRAY_TYPE)
    {
      strcat(error_str," element");
    }
    strcat(error_str," <= ");
    strcat(error_str,max_str);
    addToResponse(constants::error_message_constant_string,error_str);
    error_ = true;
  }
  else if (object_parse_unsuccessful)
  {
    addToResponse(constants::status_constant_string,JsonPrinter::ERROR);
    char parameter_name[constants::STRING_LENGTH_PARAMETER_NAME];
    parameter_name[0] = 0;
    const ConstantString* parameter_name_ptr = parameter.getNamePointer();
    parameter_name_ptr->copy(parameter_name);
    char error_str[constants::STRING_LENGTH_ERROR];
    error_str[0] = 0;
    strcat(error_str,parameter_name);
    char invalid_json_object[constants::invalid_json_object_constant_string.length()+1];
    constants::invalid_json_object_constant_string.copy(invalid_json_object);
    strcat(error_str,invalid_json_object);
    addToResponse(constants::error_message_constant_string,error_str);
    error_ = true;
  }
  else if (array_parse_unsuccessful)
  {
    addToResponse(constants::status_constant_string,JsonPrinter::ERROR);
    char parameter_name[constants::STRING_LENGTH_PARAMETER_NAME];
    parameter_name[0] = 0;
    const ConstantString* parameter_name_ptr = parameter.getNamePointer();
    parameter_name_ptr->copy(parameter_name);
    char error_str[constants::STRING_LENGTH_ERROR];
    error_str[0] = 0;
    strcat(error_str,parameter_name);
    char invalid_json_array[constants::invalid_json_array_constant_string.length()+1];
    constants::invalid_json_array_constant_string.copy(invalid_json_array);
    strcat(error_str,invalid_json_array);
    addToResponse(constants::error_message_constant_string,error_str);
    error_ = true;
  }
  bool parameter_ok = (!out_of_range) && (!object_parse_unsuccessful) && (!array_parse_unsuccessful);
  return parameter_ok;
}

int Client::findSavedVariableIndex(const ConstantString &saved_variable_name)
{
  int saved_variable_index = -1;
  for (unsigned int i=0; i<saved_variable_array_.size(); ++i)
  {
    if (saved_variable_array_[i].compareName(saved_variable_name))
    {
      saved_variable_index = i;
      break;
    }
  }
  return saved_variable_index;
}

unsigned int Client::getSerialNumber()
{
  unsigned int serial_number;
  getSavedVariableValue(constants::serial_number_constant_string,serial_number);
  return serial_number;
}

void Client::initializeEeprom()
{
  saved_variable_array_[eeprom_initialized_index_].setValue(constants::eeprom_initialized_value);
  eeprom_uninitialized_ = false;
}

void Client::incrementClientSerial()
{
  client_serial_index_ = (client_serial_index_ + 1) % client_serial_ptr_array_.size();
  response_.setSerial(*client_serial_ptr_array_[client_serial_index_]);
}

void Client::getClientInfoCallback()
{
  addToResponse(constants::name_constant_string,name_ptr_);
  addToResponse(constants::model_number_constant_string,model_number_);
  addToResponse(constants::serial_number_constant_string,getSerialNumber());
  addKeyToResponse(constants::firmware_version_constant_string);
  startResponseObject();
  addToResponse(constants::major_constant_string,firmware_major_);
  addToResponse(constants::minor_constant_string,firmware_minor_);
  addToResponse(constants::patch_constant_string,firmware_patch_);
  stopResponseObject();
}

void Client::getMethodIdsCallback()
{
  const ConstantString* method_name_ptr;
  for (unsigned int method_index=0; method_index<method_array_.size(); ++method_index)
  {
    if (!method_array_[method_index].isReserved())
    {
      method_name_ptr = method_array_[method_index].getNamePointer();
      addToResponse(method_name_ptr,method_index);
    }
  }
}

void Client::getResponseCodesCallback()
{
  addToResponse(constants::response_success_constant_string,JsonPrinter::SUCCESS);
  addToResponse(constants::response_error_constant_string,JsonPrinter::ERROR);
}

void Client::getParametersCallback()
{
  addKeyToResponse(constants::parameters_constant_string);
  response_.startArray();
  for (unsigned int parameter_index=0; parameter_index<parameter_array_.size(); ++parameter_index)
  {
    parameterHelp(parameter_array_[parameter_index]);
  }
  response_.stopArray();
}

void Client::help()
{
  addKeyToResponse(constants::client_info_constant_string);
  startResponseObject();
  getClientInfoCallback();
  stopResponseObject();

  addKeyToResponse(constants::methods_constant_string);
  startResponseArray();
  const ConstantString* method_name_ptr;
  for (unsigned int method_index=0; method_index<method_array_.size(); ++method_index)
  {
    if (!method_array_[method_index].isReserved())
    {
      method_name_ptr = method_array_[method_index].getNamePointer();
      addToResponse(method_name_ptr);
    }
  }
  stopResponseArray();
}

void Client::verboseHelp()
{
  addKeyToResponse(constants::client_info_constant_string);
  startResponseObject();
  getClientInfoCallback();
  stopResponseObject();

  addKeyToResponse(constants::methods_constant_string);
  startResponseArray();
  for (unsigned int method_index=0; method_index<method_array_.size(); ++method_index)
  {
    if (!method_array_[method_index].isReserved())
    {
      verboseMethodHelp(method_index);
    }
  }
  stopResponseArray();
}
}
