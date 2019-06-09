#include <radio.h>
#include <TEA5767.h>

TEA5767 radio;

int potPin = 2; // input pin for the potentiometer (station tuner)

// FM radio stations in NY: http://www.nyradioguide.com/freqlist.htm
uint16_t stations[] = {8775,8810,8830,8870,8890,8910,8910,8950,8990,9030,9030,9030,9070,9110,9150,9230,9270,9310,9350,9390,9470,9550,9630,9670,9710,9790,9830,9870,9950,10030,10070,10110,10190,10270,10310,10350,10390,10430,10510,10550,10590,10670,10710,10750};
int dial = 0; // index of stations (0-43)

void setup() {
  Serial.begin(9600);
  Serial.println("starting");
  radio.init();
  radio.debugEnable();
  radio.setMono(false);
}

int getStation() {
  // convert the value read from potentiometer (0-1023) 
  // into an index corresponding to the stations (0-43)
  return (43./1023.) * analogRead(potPin);
}

void setStation() {
  dial = getStation();
  Serial.print("Station number: "); 
  Serial.print(dial);
  Serial.print(" which is station: ");
  Serial.println(stations[dial]);
  radio.setBandFrequency(RADIO_BAND_FM, stations[dial]);
}

void loop() {
  setStation();
  delay(1000);
}
