/**
 * ESPhant.h
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

#ifndef ESPhant_h
#define ESPhant_h

#include <Arduino.h>

class ESPhant {
 public:
  ESPhant(String host, String publicKey, String privateKey, unsigned short port = 80);

  void add(String field, String data);
  void add(String field, char data);
  void add(String field, int data);
  void add(String field, byte data);
  void add(String field, long data);
  void add(String field, unsigned int data);
  void add(String field, unsigned long data);
  void add(String field, float data);
  void add(String field, double data);

  void add(const __FlashStringHelper *field, String data);
  void add(const __FlashStringHelper *field, char data);
  void add(const __FlashStringHelper *field, int data);
  void add(const __FlashStringHelper *field, byte data);
  void add(const __FlashStringHelper *field, long data);
  void add(const __FlashStringHelper *field, unsigned int data);
  void add(const __FlashStringHelper *field, unsigned long data);
  void add(const __FlashStringHelper *field, float data);
  void add(const __FlashStringHelper *field, double data);

  void clear();

  String host();
  String request();

  unsigned short port();

 private:
  String _pub;
  String _prv;
  String _host;
  String _params;

  unsigned short _port;

  void addFlashString(const __FlashStringHelper *string, String &dest);
};

#endif
