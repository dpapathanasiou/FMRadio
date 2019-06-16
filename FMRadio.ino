#include <Wire.h>
#include <TEA5767Radio.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "stations.h"

TEA5767Radio radio = TEA5767Radio();

int potPin = 2; // input pin for the potentiometer (station tuner)

int availableStations = sizeof(stations) / sizeof(float);

int dial = 0; // index of available stations
int current = 0;

// OLED display
#define SCREEN_WIDTH  128 // in pixels
#define SCREEN_HEIGHT  64 
#define OLED_RESET     -1 
#define OLED_ADDRESS 0x3c // usually, despite the circuit imprint (use the i2c_scanner to confirm)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
bool displayAvailable = false;

void setup() {
  Serial.begin(9600);

  // initialize the radio
  Wire.begin();
  
  // initialize the display
  displayAvailable = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  if(!displayAvailable) { 
    Serial.println(F("OLED display setup failed"));
  } else {
    Serial.println(F("success"));
    display.display();
    display.clearDisplay();
  }
}

int getStation() {
  // convert the value read from potentiometer (0-1023) 
  // into an index corresponding to the stations
  return (availableStations/1023.) * analogRead(potPin);
}

void updateDisplay(int index) {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  // get the display label for this dial setting (index)
  strcpy_P(stationBuffer, (char*)pgm_read_word(&(callLetters[index])));
  Serial.println(stationBuffer);
  display.println(stationBuffer);
  display.display();

  // emphasize the update: invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(100);
  display.invertDisplay(false);
  delay(100);
}

void loop() {
  current = getStation();
  if (current != dial ) {
    dial = current;
    radio.setFrequency(stations[dial]);
    if (displayAvailable) {
      updateDisplay(dial);
    }
  } 
  delay(500);
}
