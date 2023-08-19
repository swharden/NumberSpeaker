#include "NumberSpeaker.h"

void setup() {
}

void loop() {
  for (;;) {
    String s = String("123.45678");
    Speak(s);
  }
}