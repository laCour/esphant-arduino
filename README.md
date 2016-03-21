# esphant-arduino

The goal of this library is to provide a simple interface for logging data to phant. This library will handle interaction with Wi-Fi via any ESP8266 module. Its purpose is to make it both easier for users to build phant compatible requests as well as execute those requests.

This library is based off of the [phant-arduino](https://github.com/sparkfun/phant-arduino) library from SparkFun. It uses the same license, GPL-3. The `ESPhant` class in this library is essentially a stripped down version of Phant which works alongside the `ESP8266` class.

As an example of stability/reliability, I have made a temperature logger using this library. You can see it in action here: [weather.lacour.me](http://weather.lacour.me/). The graph updates live, shortly after the logger [logs to data.sparkfun.com](https://data.sparkfun.com/temperatures) every 20 seconds or so. This logger uses an ESP-07 with an external antenna.

## Installation

**Linux & Mac:**
```bash
$ cd ~/Documents/Arduino/libraries
$ git clone https://github.com/lacour/esphant-arduino.git
```

**Windows:** :cry:

## Usage

Create a new instance of the `ESP8266` class, then pass pin integers for the `RX pin`, `TX pin`, and a `RESET pin` if used, respectively. If no parameters are passed, the hardware serial pins will be used. The `RESET pin` will be pulled low when the library feels it necessary to perform a hardware reset instead of a software reset, typically upon lock ups, in order to keep things working with minimal interaction.

```ino
ESP8266 esp8266(2, 3, 4);
```

To create a new instance of the request builder, pass the server's `hostname`, your `public key`, and your `private key` to the `ESPhant` constructor, respectively.

```ino
ESPhant esphant("data.sparkfun.com", "VGb2Y1jD4VIxjX3x196z", "9YBaDk6yeMtNErDNq4YM");
```

Before we can make the request, you should connect to your Wi-Fi network (do this in your `setup` method). To do so, use the `connect()` method provided by `ESP8266` and pass your network's SSID and password. This method returns a success boolean. If the library absolutely cannot, for whatever reason, achieve a connection this will be `false`.

```ino
boolean success = esp8266.connect("SSID", "password");
```

In order to add data to your ESPhant request you can make calls to `esphant.add(key, value)`. The library will convert any value data type to a string, so there is no need for conversion before sending data. For example, if you have a stream with fields titled `wind`, `temp`, and `raining`, your code would add data to the request like this:

```ino
esphant.add("wind", 12.0);
esphant.add("temp", 70.1);
esphant.add("raining", false);
```

Now we're ready to send the request. The `send` method accepts an instance of `ESPhant`, which is its only parameter, and it returns a success boolean. If the library either cannot achieve a connection with the phant service, or if some other issue is encountered, this will return `false`.

```ino
boolean success = esp8266.send(esphant);
```

## Example

```ino
#include <ESPhant.h>
#include <ESP8266.h>

#include <SoftwareSerial.h>

// ESP8266 Wi-Fi module
// RX, TX, RESET
ESP8266 esp8266(2, 3, 4);

// Arduino example stream
// http://data.sparkfun.com/streams/VGb2Y1jD4VIxjX3x196z
// hostname, public key, private key
ESPhant esphant("data.sparkfun.com", "VGb2Y1jD4VIxjX3x196z", "9YBaDk6yeMtNErDNq4YM");

void setup() {
  Serial.begin(115200);

  if (esp8266.connect("SSID", "password")) {
    Serial.println("Connected to network.");
  } else {
    Serial.println("Error connecting to network.");
    while(1);
  }
}

void loop() {
  esphant.add("wind", 12.0);
  esphant.add("temp", 70.1);
  esphant.add("raining", false);

  if (esp8266.send(esphant)) {
    Serial.println("Logged weather.");
  } else {
    Serial.println("Error logging weather.");
  }

  esphant.clear();
  delay(2000);
}
```
