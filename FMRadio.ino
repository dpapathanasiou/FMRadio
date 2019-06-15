#include <radio.h>
#include <TEA5767.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

TEA5767 radio;

int potPin = 2; // input pin for the potentiometer (station tuner)

// FM radio stations in NY: http://www.nyradioguide.com/freqlist.htm
uint16_t stations[] = {8775,8810,8830,8870,8890,8910,8910,8950,8990,9030,9030,9030,9070,9110,9150,9230,9270,9310,9350,9390,9470,9550,9630,9670,9710,9790,9830,9870,9950,10030,10070,10110,10190,10270,10310,10350,10390,10430,10510,10550,10590,10670,10710,10750};
int dial = 0; // index of stations (0-43)
int current = 0;

// OLED display
#define SCREEN_WIDTH  128 // in pixels
#define SCREEN_HEIGHT  64 
#define OLED_RESET      4 
#define OLED_ADDRESS 0x3C // usually, despite the circuit imprint (use the i2c_scanner to confirm)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
bool OLED = false;

void setup() {
  Serial.begin(9600);

  // initialize the radio
  radio.init();
  radio.debugEnable();
  radio.setMono(false);

  // initialize the display
  OLED = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  if(!OLED) { 
    Serial.println(F("OLED display setup failed"));
  } else {
    display.display();
    display.clearDisplay();
  }
}

int getStation() {
  // convert the value read from potentiometer (0-1023) 
  // into an index corresponding to the stations (0-43)
  return (43./1023.) * analogRead(potPin);
}

void loop() {
  current = getStation();
  if (current != dial ) {
    dial = current;
    radio.setBandFrequency(RADIO_BAND_FM, stations[dial]);
  } 
  delay(1000);
}
