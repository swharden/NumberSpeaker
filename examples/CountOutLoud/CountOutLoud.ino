#include <NumberSpeaker.h>

NumberSpeaker numberSpeaker = NumberSpeaker();

void setup() {
  numberSpeaker.begin();  // speaker on pin 11
}

void loop() {
  unsigned int count = 0;
  for (;;) {
    numberSpeaker.speak_int(count++);
    delay(500);
  }
}