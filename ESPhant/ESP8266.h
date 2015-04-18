/**
 * ESP8266.h
 *
 * ESPhant Author: Jonathan la Cour <jon@lacour.me>
 *
 * Licensed under the GPL v3 license.
 *
 */

#ifndef ESP8266_h
#define ESP8266_h

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "ESPhant.h"

class ESP8266 : public SoftwareSerial {
 public:
  ESP8266(byte rxPin, byte txPin, byte resetPin = 0, unsigned long baudRate = 115200);

  bool connect(String ssid, String password, byte attempts = 10);
  bool send(ESPhant esphant, byte attempts = 5);

 private:
  String _password;
  String _ssid;

  unsigned long _baudRate;
  unsigned short _resetEnabled;
  unsigned short _resetPin;

  bool expect(const char *expectation, byte successDelay = 0);
  bool sendAndExpect(String command, const char *expectation, byte successDelay = 0, byte attempts = 10);

  void saneReset(byte i);
  void reset();
};

#endif
