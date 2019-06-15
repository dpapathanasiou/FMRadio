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
const char *const callLetters[] PROGMEM = {
  "87.75 WNYZ",
  "88.1 WCWP",
  "88.3 WBGO Jazz 88",
  "88.7 WRHU",
  "88.9 WSIA",
  "89.1 WFDU",
  "89.1 WNYU",
  "89.5 WSOU",
  "89.9 WKCR",
  "90.3 WKRB",
  "90.3 WHCR",
  "90.3 WHPC",
  "90.7 WFUV",
  "91.1 WFMU",
  "91.5 WNYE Radio New York",
  "92.3 WBMP ALT 92.3 FM",
  "92.7 WQBU La Que Buena",
  "93.1 WPAT Amor 93.1",
  "93.5 WVIP",
  "93.9 WNYC",
  "94.7 WNSH Nash FM",
  "95.5 WPLJ",
  "96.3 WXNY X96.3 FM",
  "96.7 WKLV",
  "97.1 WQHT Hot 97",
  "97.9 WSKQ Mega 97.9",
  "98.3 WKJY K-Joy",
  "98.7 WEPN ESPN New York FM",
  "99.5 WBAI",
  "100.3 WHTZ Z-100",
  "100.7 WHUD",
  "101.1 WCBS",
  "101.9 WFAN",
  "102.7 WNEW Fresh 102.7",
  "103.1 WJUX W276AQ",
  "103.5 WKTU",
  "103.9 WNBM",
  "104.3 WAXQ Q104",
  "105.1 WWPR Power 105.1",
  "105.5 WDHA",
  "105.9 WQXR",
  "106.7 WLTW Lite FM",
  "107.1 WXPK The Peak",
  "107.5 WBLS"
};

int dial = 0; // index of stations (0-43)
int current = 0;

// OLED display
#define SCREEN_WIDTH  128 // in pixels
#define SCREEN_HEIGHT  64 
#define OLED_RESET      4 
#define OLED_ADDRESS 0x3C // usually, despite the circuit imprint (use the i2c_scanner to confirm)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
bool OLED = false;

// helper for injecting callLetters[] with the F() macro required by the display
#define FS(x) (__FlashStringHelper*) (x)

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

void updateDisplay(int dial) {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println(FS(callLetters[dial]));
  display.display();
  delay(100);

  // animation: scroll in various directions, pausing in-between
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}

void loop() {
  current = getStation();
  if (current != dial ) {
    dial = current;
    radio.setBandFrequency(RADIO_BAND_FM, stations[dial]);
    updateDisplay(dial);
  } 
  delay(1000);
}
