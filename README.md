# esphant-arduino

The goal of this library is to provide a simple interface for logging data to phant. This library will handle interaction with Wi-Fi via any ESP8266 module. Its purpose is to make it both easier for users to build phant compatible requests as well as execute those requests.

This library is based off of the [phant-arduino](https://github.com/sparkfun/phant-arduino) library from SparkFun. It uses the same license, GPL-3. The `ESPhant` class in this library is essentially a stripped down version of Phant which works alongside with the `ESP8266` class.

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

## Notes

### Basic Setup

![Diagram](http://i.imgur.com/Olwr97d.png)

The ESP8266 module is not 5v tolerant. You must use 3v3 power source along with a logic level converter for converting the Arduino's 5v logic to 3v3, or else you risk bricking the module.

### ESP8266

This library was made using the [ESP-01](http://www.esp8266.com/wiki/doku.php?id=esp8266-module-family#esp-01), [ESP-07](http://www.esp8266.com/wiki/doku.php?id=esp8266-module-family#esp-07), and [ESP-12](http://www.esp8266.com/wiki/doku.php?id=esp8266-module-family#esp-12) modules. I used v1.0.1-b2 of the ESP8266 SDK, you can find this release on the [Espressif Forum](http://bbs.espressif.com/viewforum.php?f=5) along with newer versions (most should work). The files you need to flash are within the SDK zip package, within the `bin` directory. Be sure to read the text file in the same directory for instructions on what to flash where.

For flashing, I recommend using [esptool](https://github.com/themadinventor/esptool) and [SparkFun's 3.3v FTDI Breakout](https://www.sparkfun.com/products/9873). An FTDI Breakout is completely optional, you can flash the modules via an Arduino as well. SparkFun's 5v FTDI Breakout will also work if you use it with a [Logic Level Converter](https://www.sparkfun.com/products/12009) (though you can also convert it to 3v3 by using the solder jumper on the back and cutting the default trace).

![Diagram](http://i.imgur.com/wWA5S9R.png)

### Components


**ESP8266 ESP-01:**
* US: [Adafruit @ $6.95](http://www.adafruit.com/products/2282) — [SparkFun @ $6.95](https://www.sparkfun.com/products/13252) — [Hack A Day @ $6.97](http://store.hackaday.com/products/wifi-serial-module-esp8266) — [Amazon @ $7.99](http://www.amazon.com/Diymall-Esp8266-Serial-Wireless-Transceiver/dp/B00O34AGSU)
* China: [AliExpress @ >$2.50](http://www.aliexpress.com/wholesale?catId=0&SearchText=ESP8266+ESP-01) — [Elecrow @ $3.24](http://www.elecrow.com/serial-wifi-transceiver-module-esp8266-p-1136.html)
* Note: Most places seem to only sell the ESP-01 model, but you can certainly use different models. Namely, I would recommend the ESP-07 or ESP-12. The ESP-07 offers both an on-board ceramic antenna and an antenna socket, while the ESP-12 only offers an on-board antenna similar to the ESP-01. Both the ESP-07 and ESP-12 are shielded. The ESP-12 is FCC approved... sort-of. While I couldn't find any with clear FCC ID markings on them, I did find the actual ID, `2ADUIESP-12`. You can find [more information here](http://www.esp8266.com/wiki/doku.php?id=esp8266-module-family).

**Logic Level Converter:**
* US: [SparkFun @ $2.95](https://www.sparkfun.com/products/12009) — [Adafruit @ $3.50](http://www.adafruit.com/products/1875) — [Adafruit @ $3.95](http://www.adafruit.com/products/757)
* China: [AliExpress @ >$1.00](http://www.aliexpress.com/wholesale?catId=0&SearchText=logic+level+converter+ttl)

**FTDI Breakout (supporting 3v3):**
* US: [SparkFun @ $14.95](https://www.sparkfun.com/products/9873)
* China: [AliExpress @ >$2.20](http://www.aliexpress.com/wholesale?catId=0&SearchText=FTDI+3.3V+TTL)
