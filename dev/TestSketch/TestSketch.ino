#include "NumberSpeaker.h"

NumberSpeaker numberSpeaker = NumberSpeaker();

void setup() {
  numberSpeaker.begin();
}

void loop() {
  for (;;) {

    numberSpeaker.speak("28.432");
    delay(1000);
    
    numberSpeaker.speak("14.253");
    delay(1000);
    
    numberSpeaker.speak("7.040");
    delay(1000);

    for (int i = 0; i < 10; i++) {
      numberSpeaker.speak(i);
    }
    delay(1000);

  }
}