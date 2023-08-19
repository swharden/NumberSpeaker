#include "NumberSpeaker.h"

NumberSpeaker numberSpeaker = NumberSpeaker();

void setup() {
  numberSpeaker.begin();
}

void loop() {
  for (;;) {
    for (int i = 0; i < 10; i++) {
      numberSpeaker.speak(i);
      delay(500);
    }
  }
}