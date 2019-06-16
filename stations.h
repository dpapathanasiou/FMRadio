#ifndef STATIONS_H_
#define STATIONS_H_

#include <avr/pgmspace.h>

// FM radio stations in NY:
// http://www.nyradioguide.com/freqlist.htm supplemented with
// https://radio-locator.com/cgi-bin/locate?select=city&city=New+York&state=NY&band=FM&is_lic=Y&is_cp=Y&is_fl=Y&is_fx=Y&is_fb=Y&format=&dx=0&radius=&freq=&sort=freq

float stations[] = {87.75, 88.10, 88.3, 88.7, 88.9, 89.1, 89.5, 89.9, 90.3, 90.7, 91.1, 91.5, 91.9, 92.3, 92.7, 93.1, 93.5, 93.9, 94.3, 94.7, 95.1, 95.5, 95.9, 96.3, 96.7, 97.1, 97.5, 97.9, 98.3, 98.7, 99.1, 99.5, 100.3, 100.7, 101.1, 101.5, 101.9, 102.3, 102.7, 103.1, 103.5, 103.9, 104.3, 104.7, 105.1, 105.9, 106.3, 106.7, 107.1, 107.5};

const char sta1[] PROGMEM = "87.75 WNYZ";
const char sta2[] PROGMEM = "88.1 WCWP";
const char sta3[] PROGMEM = "88.3 WBGO Jazz 88";
const char sta4[] PROGMEM = "88.7 WRHU";
const char sta5[] PROGMEM = "88.9 WSIA";
const char sta6[] PROGMEM = "89.1 WNYU";
const char sta7[] PROGMEM = "89.5 WSOU";
const char sta8[] PROGMEM = "89.9 WKCR";
const char sta9[] PROGMEM = "90.3 WHCR";
const char sta10[] PROGMEM = "90.7 WFUV";
const char sta11[] PROGMEM = "91.1 WFMU";
const char sta12[] PROGMEM = "91.5 WNYE Radio New York";
const char sta13[] PROGMEM = "91.9 WFMU";
const char sta14[] PROGMEM = "92.3 WBMP ALT FM";
const char sta15[] PROGMEM = "92.7 WQBU La Que Buena";
const char sta16[] PROGMEM = "93.1 WPAT Amor";
const char sta17[] PROGMEM = "93.5 WVIP";
const char sta18[] PROGMEM = "93.9 WNYC";
const char sta19[] PROGMEM = "94.3 WSBP";
const char sta20[] PROGMEM = "94.7 WNSH Nash FM";
const char sta21[] PROGMEM = "95.1 WRDR";
const char sta22[] PROGMEM = "95.5 WPLJ";
const char sta23[] PROGMEM = "95.9 WNJI";
const char sta24[] PROGMEM = "96.3 WXNY";
const char sta25[] PROGMEM = "96.7 WKLV";
const char sta26[] PROGMEM = "97.1 WQHT Hot 97";
const char sta27[] PROGMEM = "97.5 WXMC";
const char sta28[] PROGMEM = "97.9 WSKQ Mega";
const char sta29[] PROGMEM = "98.3 WKJY K-Joy";
const char sta30[] PROGMEM = "98.7 WEPN ESPN New York";
const char sta31[] PROGMEM = "99.1 WAWZ";
const char sta32[] PROGMEM = "99.5 WBAI";
const char sta33[] PROGMEM = "100.3 WHTZ Z-100";
const char sta34[] PROGMEM = "100.7 WHUD";
const char sta35[] PROGMEM = "101.1 WCBS";
const char sta36[] PROGMEM = "101.5 WVIP";
const char sta37[] PROGMEM = "101.9 WFAN";
const char sta38[] PROGMEM = "102.3 WBQE";
const char sta39[] PROGMEM = "102.7 WNEW Fresh";
const char sta40[] PROGMEM = "103.1 WRDR";
const char sta41[] PROGMEM = "103.5 WKTU";
const char sta42[] PROGMEM = "103.9 WNBM";
const char sta43[] PROGMEM = "104.3 WAXQ Q104";
const char sta44[] PROGMEM = "104.7 WWRV";
const char sta45[] PROGMEM = "105.1 WWPR Power";
const char sta46[] PROGMEM = "105.9 WQXR";
const char sta47[] PROGMEM = "106.3 WVIP";
const char sta48[] PROGMEM = "106.7 WLTW Lite FM";
const char sta49[] PROGMEM = "107.1 WKJY The Peak";
const char sta50[] PROGMEM = "107.5 WBLS";

const char *const callLetters[] PROGMEM = {sta1, sta2, sta3, sta4, sta5, sta6, sta7, sta8, sta9, sta10, sta11, sta12, sta13, sta14, sta15, sta16, sta17, sta18, sta19, sta20, sta21, sta22, sta23, sta24, sta25, sta26, sta27, sta28, sta29, sta30, sta31, sta32, sta33, sta34, sta35, sta36, sta37, sta38, sta39, sta40, sta41, sta42, sta43, sta44, sta45, sta46, sta47, sta48, sta49, sta50};

char stationBuffer[24]; // size is based on largest string in callLetters + 1

#endif // STATIONS_H_
