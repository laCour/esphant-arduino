/**
 * ESP8266.cpp
 *
 * ESPhant Author: Jonathan la Cour <jon@lacour.me>
 *
 * Licensed under the GPL v3 license.
 *
 */

#include <Arduino.h>
#include <SoftwareSerial.h>

#include <avr/pgmspace.h>

#include "ESP8266.h"

const char responseOk[] PROGMEM = {"OK"};
const char responseReady[] PROGMEM = {"ready"};
const char responseSendOk[] PROGMEM = {"SEND OK"};

ESP8266::ESP8266(byte rxPin, byte txPin, byte resetPin, unsigned long baudRate) : SoftwareSerial(rxPin, txPin) {
  _resetEnabled = (resetPin != 0);
  _resetPin = resetPin;
  _baudRate = baudRate;

  if (_resetEnabled) {
    pinMode(_resetPin, OUTPUT);
    digitalWrite(_resetPin, HIGH);
  }
}

bool ESP8266::connect(String ssid, String password, byte attempts) {
  begin(_baudRate);
  delay(25L);

  if (!sendAndExpect(F("AT+CWMODE=1"), responseOk, 0, attempts)) return false;

  return sendAndExpect("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"", responseOk, 25, attempts);
}

bool ESP8266::send(ESPhant esphant, byte attempts) {
  while (attempts) {
    print(F("AT+CIPSTART=\"TCP\",\""));
    print(esphant.host());
    print(F("\","));
    println(esphant.port());
    expect(responseOk, 25);

    print(F("AT+CIPSEND="));
    println(esphant.request().length());
    expect(responseOk, 25);
    
    print(esphant.request());

    if (expect(responseSendOk)) return true;

    saneReset(--attempts);
  }

  return false;
}

bool ESP8266::expect(const char *expectation, byte successDelay) {
  byte i = 0;
  long startMillis = millis();

  do {
    char c = read();

    if (c >= 0) {
      if (c != pgm_read_byte_near(expectation + i)) i = 0;

      if (c == pgm_read_byte_near(expectation + i)) {
        if (++i >= strlen_P(expectation)) {
          delay(successDelay);
          return true;
        }
      }
    }
  } while (millis() - startMillis < 8000);

  return false;
}

bool ESP8266::sendAndExpect(String command, const char *expectation, byte successDelay, byte attempts) {
  while (attempts) {
    println(command);

    if (expect(expectation, successDelay)) {
      return true;
    }

    saneReset(--attempts);
  }

  return false;
}

void ESP8266::saneReset(byte i) {
  if (((int) round((i - 1 + i) / 0.6)) % 2 == 1) {
    if (i % 2 == 0 && i > 5) {
      sendAndExpect(F("AT+RST"), responseReady, 50L, 1);
    } else {
      reset();
    }
  }
}

void ESP8266::reset() {
  if (_resetEnabled) {
    digitalWrite(_resetPin, LOW);
    delay(50L);
    digitalWrite(_resetPin, HIGH);
    expect(responseReady, 150);
    char c;

    while (available() > 0) {
      c = read();
    }
  }
}