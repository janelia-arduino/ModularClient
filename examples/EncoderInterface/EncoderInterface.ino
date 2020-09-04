#include <Arduino.h>
#include <Streaming.h>
#include <ArduinoJson.h>
#include <ModularClient.h>
#include <Watchdog.h>


const long BAUD = 2000000;
enum{ENCODER_POSITIONS_JSON_DOCUMENT_SIZE=256};
const size_t INDEX = 0;
const unsigned long POLL_PERIOD = 50;
const unsigned long PRINT_PERIOD = 500;
const size_t SERIAL_TIMEOUT = 500;
HardwareSerial & serial = Serial1;
ModularClient dev(serial);
ModularClient * encoder_interface_simple_ptr_;
unsigned long time;
unsigned long poll_time_previous;
unsigned long print_time_previous;
Watchdog watchdog;


void setup()
{
  Serial.setTimeout(SERIAL_TIMEOUT);
  Serial.begin(BAUD);

  serial.setTimeout(SERIAL_TIMEOUT);
  serial.begin(BAUD);

  encoder_interface_simple_ptr_ = &dev;

  poll_time_previous = millis();
  print_time_previous = millis();

  watchdog.enable(Watchdog::TIMEOUT_2S);
}

void loop()
{
  time = millis();
  if ((time - poll_time_previous) < POLL_PERIOD)
  {
    return;
  }
  poll_time_previous = time;
  watchdog.reset();

  StaticJsonDocument<ENCODER_POSITIONS_JSON_DOCUMENT_SIZE> json_document;
  JsonArray position_array = encoder_interface_simple_ptr_->callGetResult(json_document,"getPositions");

  if ((time - print_time_previous) < PRINT_PERIOD)
  {
    return;
  }
  print_time_previous = time;
  long position;
  if (encoder_interface_simple_ptr_->callWasSuccessful())
  {
    position = position_array[INDEX];
    Serial << "position = " << position << "\n";
  }
  else
  {
    Serial << "call failed!\n";
  }
}
