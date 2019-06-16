# Arduino TEA5767 FM Radio

## About

This project provides code and wiring diagrams for building an FM radio in [Arduino](https://www.arduino.cc/) using the [TEA5767 FM Stereo Radio Module](https://amzn.to/2WUAYb7).

## Parts

* [Arduino Uno](https://amzn.to/2IlsEJt) or a [clone](https://amzn.to/2MOoApe)
* [TEA5767 FM Stereo Radio Module](https://amzn.to/2WUAYb7)
* [10K Potentiometer](https://amzn.to/2WtFVIq) for the station tuner
* [0.96" I2C 128x64 OLED LCD Display](https://amzn.to/2Ik1HpA)

### Speakers

It is possible to use a pair of [8 Ohm speakers](https://amzn.to/2IPS5C1) with an [LM386 audio amplifier](https://amzn.to/2Kmj4Z6), but a simpler and more robust option is to use a cheap usb speaker like [this one](https://amzn.to/2WJEwZy) or [this one](https://amzn.to/2XfpQWl), with a [usb audio adapter cable](https://amzn.to/2IJOUM1) (if not included with the speaker).

## Wiring

Both the TEA5767 and OLED connect to the same [I2C](https://en.wikipedia.org/wiki/I%C2%B2C) pins on the Arduino, but because their device addresses are different, they can use the [common I2C bus](https://www.arduino.cc/en/Reference/Wire) without conflict.

Use the [I2C scanner](https://playground.arduino.cc/Main/I2cScanner/) to check the addresses of actual hardware being used. Device conflicts cana be resolved, but it is a [more significant undertaking](https://create.arduino.cc/projecthub/chipmc/arduino-i2c-multi-master-approach-why-and-how-93f638).

Finally, note that these connections are based on the [Arduino Uno](https://amzn.to/2IlsEJt); the [Mega2560](https://amzn.to/2KTp8aY), [Leonardo](https://amzn.to/2WHgyy1), and [Due](https://amzn.to/2FacTmw) use [different pins for SDA and SCL](https://www.arduino.cc/en/Reference/Wire).

### TEA5767 to Arduino

* GND -> Arduino GND
* VCC -> Arduino 5V
* SDA -> Arduino Uno A4
* SCL -> Arduino Uno A5

### OLED to Arduino

* GND -> Arduino GND
* VCC -> Arduino 5V
* SDA -> Arduino Uno A4
* SCL -> Arduino Uno A5

### Potentiometer to Arduino

* Outer pin (either left or right) -> Arduino GND
* Other outer pin (opposite side)  -> Arduino 5V
* Middle pin -> Arduino A2 (this can be any available analog pin; its value is set by the `int potPin` variable in the code)

## Acknowledgements

* [Potentiometer Tutorial](https://www.arduino.cc/en/Tutorial/Potentiometer)
* [List of FM stations in NYC](http://www.nyradioguide.com/freqlist.htm) supplemented by [Radio-Locator.com](https://radio-locator.com/cgi-bin/locate?select=city&city=New+York&state=NY&band=FM&is_lic=Y&is_cp=Y&is_fl=Y&is_fx=Y&is_fb=Y&format=&dx=0&radius=&freq=&sort=freq)
* [Arduino Library for the TEA5767 FM radio receiver module](https://github.com/simonmonk/arduino_TEA5767)
* [Adafruit OLED Libraries](https://learn.adafruit.com/monochrome-oled-breakouts/arduino-library-and-examples)
