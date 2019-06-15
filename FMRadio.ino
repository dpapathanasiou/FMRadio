#include <radio.h>
#include <TEA5767.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>

TEA5767 radio;

int potPin = 2; // input pin for the potentiometer (station tuner)

// FM radio stations in NY: http://www.nyradioguide.com/freqlist.htm
uint16_t stations[] = {8775,8810,8830,8870,8890,8910,8910,8950,8990,9030,9030,9030,9070,9110,9150,9230,9270,9310,9350,9390,9470,9550,9630,9670,9710,9790,9830,9870,9950,10030,10070,10110,10190,10270,10310,10350,10390,10430,10510,10550,10590,10670,10710,10750};
int dial = 0; // index of stations (0-43)
int current = 0;

const char sta1[] PROGMEM = "87.75 WNYZ";
const char sta2[] PROGMEM = "88.1 WCWP";
const char sta3[] PROGMEM = "88.3 WBGO Jazz 88";
const char sta4[] PROGMEM = "88.7 WRHU";
const char sta5[] PROGMEM = "88.9 WSIA";
const char sta6[] PROGMEM = "89.1 WFDU";
const char sta7[] PROGMEM = "89.1 WNYU";
const char sta8[] PROGMEM = "89.5 WSOU";
const char sta9[] PROGMEM = "89.9 WKCR";
const char sta10[] PROGMEM = "90.3 WKRB";
const char sta11[] PROGMEM = "90.3 WHCR";
const char sta12[] PROGMEM = "90.3 WHPC";
const char sta13[] PROGMEM = "90.7 WFUV";
const char sta14[] PROGMEM = "91.1 WFMU";
const char sta15[] PROGMEM = "91.5 WNYE Radio New York";
const char sta16[] PROGMEM = "92.3 WBMP ALT 92.3 FM";
const char sta17[] PROGMEM = "92.7 WQBU La Que Buena";
const char sta18[] PROGMEM = "93.1 WPAT Amor 93.1";
const char sta19[] PROGMEM = "93.5 WVIP";
const char sta20[] PROGMEM = "93.9 WNYC";
const char sta21[] PROGMEM = "94.7 WNSH Nash FM";
const char sta22[] PROGMEM = "95.5 WPLJ";
const char sta23[] PROGMEM = "96.3 WXNY X96.3 FM";
const char sta24[] PROGMEM = "96.7 WKLV";
const char sta25[] PROGMEM = "97.1 WQHT Hot 97";
const char sta26[] PROGMEM = "97.9 WSKQ Mega 97.9";
const char sta27[] PROGMEM = "98.3 WKJY K-Joy";
const char sta28[] PROGMEM = "98.7 WEPN ESPN New York FM";
const char sta29[] PROGMEM = "99.5 WBAI";
const char sta30[] PROGMEM = "100.3 WHTZ Z-100";
const char sta31[] PROGMEM = "100.7 WHUD";
const char sta32[] PROGMEM = "101.1 WCBS";
const char sta33[] PROGMEM = "101.9 WFAN";
const char sta34[] PROGMEM = "102.7 WNEW Fresh 102.7";
const char sta35[] PROGMEM = "103.1 WJUX W276AQ";
const char sta36[] PROGMEM = "103.5 WKTU";
const char sta37[] PROGMEM = "103.9 WNBM";
const char sta38[] PROGMEM = "104.3 WAXQ Q104";
const char sta39[] PROGMEM = "105.1 WWPR Power 105.1";
const char sta40[] PROGMEM = "105.5 WDHA";
const char sta41[] PROGMEM = "105.9 WQXR";
const char sta42[] PROGMEM = "106.7 WLTW Lite FM";
const char sta43[] PROGMEM = "107.1 WXPK The Peak";
const char sta44[] PROGMEM = "107.5 WBLS";
const char *const callLetters[] PROGMEM = {sta1, sta2, sta3, sta4, sta5, sta6, sta7, sta8, sta9, sta10, sta11, sta12, sta13, sta14, sta15, sta16, sta17, sta18, sta19, sta20, sta21, sta22, sta23, sta24, sta25, sta26, sta27, sta28, sta29, sta30, sta31, sta32, sta33, sta34, sta35, sta36, sta37, sta38, sta39, sta40, sta41, sta42, sta43, sta44};
char stationBuffer[26]; // size is based on largest string in callLetters

// OLED display
#define SCREEN_WIDTH  128 // in pixels
#define SCREEN_HEIGHT  64 
#define OLED_RESET     -1 
#define OLED_ADDRESS 0x3c // usually, despite the circuit imprint (use the i2c_scanner to confirm)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
bool displayAvailable = false;

// helper for injecting callLetters[] with the F() macro required by the display
#define FS(x) (__FlashStringHelper*) (x)

void setup() {
  Serial.begin(9600);

  // initialize the radio
  radio.init();
  radio.debugEnable();
  radio.setMono(false);
  
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
  // into an index corresponding to the stations (0-43)
  return (43./1023.) * analogRead(potPin);
}

void updateDisplay(int dial) {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  strcpy_P(stationBuffer, (char*)pgm_read_word(&(callLetters[dial])));
  display.println(stationBuffer);
  display.display();

  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(100);
  display.invertDisplay(false);
  delay(100);
}

void loop() {
  current = getStation();
  if (current != dial ) {
    dial = current;
    Serial.println(dial);
    //radio.setBandFrequency(RADIO_BAND_FM, stations[dial]);
    if (displayAvailable) {
      updateDisplay(dial);
    }
  } 
  delay(1000);
}
