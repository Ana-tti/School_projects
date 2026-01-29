#include "SpedenSpelit.h"
#include "buttons.h"

// Painikkeiden pinnit
volatile const int _btns[4] = { 2, 3, 4, 5 };
// Booleaniset liput ovatko painikkeet painettu
volatile bool _btnIsPressed[4] = {false, false, false, false};
volatile int buttonPressed = -1; // -1 toimii merkkausarvona, että mikään nappi ei ole aktiivinen aluksi
// Keskeytykselle kynnysaika
volatile const long interruptTreshold = 300;
unsigned long interruptTime = 0;

void initButtonsAndButtonInterrupts() {
  for (int i = 0; i < 4; i++) {
    pinMode(_btns[i], INPUT_PULLUP);
  }
  // Otetaan käyttöön Port D (digitalipinnit 2-7)
  PCICR = B00000100;
  // Määritetään mitkä yksittäiset pinnit otetaan käyttöön
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT21);

  interrupts();
}

ISR(PCINT2_vect) {
  unsigned long debounceTimer = millis();

  // Tarkistetaan onko häiriövaimennuksen (debounce) aika ylittynyt
  if (debounceTimer - interruptTime > interruptTreshold) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(_btns[i]) == LOW && !_btnIsPressed[i]) {
        Serial.print("Button ");
        Serial.print(_btns[i]);
        Serial.println(" pressed");

        // Painike liputetaan painetuksi
        _btnIsPressed[i] = true;
        // Päivitetään häiriövaimennuksen aikaleima
        interruptTime = debounceTimer;
        // Talennetaan painetun painikkeen indeksi
        buttonPressed = i;
        // Ilmaistaan pelitilan tarkistus
        timeToCheckGameStatus = true;
      } 
      // Mikäli painike ei ole enää painetussa tilassa
      else if (digitalRead(_btns[i]) == HIGH) {
        // Nollataan painalluksen tila
        _btnIsPressed[i] = false;
      }
    }
  }
}