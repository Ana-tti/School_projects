#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>

  //Ulkoinen muuttuja, jota käytetään pelitilan tarkistamiseen.
extern volatile bool timeToCheckGameStatus;

  // Funktioiden esittelyt
void setupLeds(void);
void setLed(byte ledNumber);
void clearAllLeds(void);
void setAllLeds(void);
void show1(void);   // Näyttää binäärisen laskurin LEDeillä.
void show2(int);    // Näyttää valoanimaation melodian tahtiin.
#endif
