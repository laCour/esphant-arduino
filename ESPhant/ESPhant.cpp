/**
 * ESPhant.cpp
 *
 *             .-.._
 *       __  /`     '.
 *    .-'  `/   (   a \
 *   /      (    \,_   \
 *  /|       '---` |\ =|
 * ` \    /__.-/  /  | |
 *    |  / / \ \  \   \_\  jgs
 *    |__|_|  |_|__\
 *    never   forget.
 *
 * Phant Author: Todd Treece <todd@sparkfun.com>
 * ESPhant Author: Jonathan la Cour <jon@lacour.me>
 *
 * Copyright (c) 2014 SparkFun Electronics.
 * Licensed under the GPL v3 license.
 *
 */

#include <Arduino.h>
#include <avr/pgmspace.h>

#include "ESPhant.h"

ESPhant::ESPhant(String host, String publicKey, String privateKey, unsigned short port) {
  _host = host;
  _port = port;
  _pub = publicKey;
  _prv = privateKey;
  _params = "";
}

void ESPhant::add(String field, String data) {
  _params += "&" + field + "=" + data;
}

void ESPhant::add(const __FlashStringHelper *field, String data) {
  _params += "&";
  addFlashString(field, _params);
  _params += "=" + data;
}


void ESPhant::add(String field, char data) {
  _params += "&" + field + "=" + String(data);
}

void ESPhant::add(const __FlashStringHelper *field, char data) {
  _params += "&";
  addFlashString(field, _params);
  _params += "=" + String(data);
}


void ESPhant::add(String field, int data) {
  _params += "&" + field + "=" + String(data);
}

void ESPhant::add(const __FlashStringHelper *field, int data) {
  _params += "&";
  addFlashString(field, _params);
  _params += '=' + String(data);
}


void ESPhant::add(String field, byte data) {
  _params += "&" + field + "=" + String(data);
}

void ESPhant::add(const __FlashStringHelper *field, byte data) {
  _params += "&";
  addFlashString(field, _params);
  _params += "=" + String(data);
}


void ESPhant::add(String field, long data) {
  _params += "&" + field + "=" + String(data);
}

void ESPhant::add(const __FlashStringHelper *field,  long data) {
  _params += "&";
  addFlashString(field, _params);
  _params += "=" + String(data);
}

void ESPhant::add(String field, unsigned int data) {
  _params += "&" + field + "=" + String(data);
}

void ESPhant::add(const __FlashStringHelper *field,  unsigned int data) {
  _params += "&";
  addFlashString(field, _params);
  _params += "=" + String(data);
}


void ESPhant::add(String field, unsigned long data) {
  _params += "&" + field + "=" + String(data);
}

void ESPhant::add(const __FlashStringHelper *field,  unsigned long data) {
  _params += "&";
  addFlashString(field, _params);
  _params += "=" + String(data);
}


void ESPhant::add(String field, double data) {
  char tmp[30];
  dtostrf(data, 1, 4, tmp);
  _params += "&" + field + "=" + String(tmp);
}

void ESPhant::add(const __FlashStringHelper *field,  double data) {
  char tmp[30];
  dtostrf(data, 1, 4, tmp);
  _params += "&";
  addFlashString(field, _params);
  _params += "=" + String(tmp);
}

void ESPhant::add(String field, float data) {
  char tmp[30];
  dtostrf(data, 1, 4, tmp);
  _params += "&" + field + "=" + String(tmp);
}

void ESPhant::add(const __FlashStringHelper *field,  float data) {
  char tmp[30];
  dtostrf(data, 1, 4, tmp);
  _params += "&";
  addFlashString(field, _params);
  _params += "=" + String(tmp);
}

String ESPhant::host() {
  return _host;
}

unsigned short ESPhant::port() {
  return _port;
}

String ESPhant::request() {
  String params = _params.substring(1);
  return "GET /input/" + _pub + "?private_key=" + _prv + "&" + params + "\r\n";
}

void ESPhant::clear() {
  _params = "";
}

void ESPhant::addFlashString(const __FlashStringHelper *string, String &dest) {
  PGM_P p = reinterpret_cast<PGM_P>(string);
  size_t n = 0;

  while (1) {
    unsigned char c = pgm_read_byte(p++);

    if (c == 0) break;

    dest += static_cast<char>(c);
  }
}