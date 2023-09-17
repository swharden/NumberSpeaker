#include <NumberSpeaker.h>

NumberSpeaker numberSpeaker = NumberSpeaker();

void setup() {
  numberSpeaker.begin();  // speaker on pin 11
}

void loop() {

  numberSpeaker.speak_int(1234567);
  delay(500);

  numberSpeaker.speak_float(123.4567);
  delay(500);

  numberSpeaker.speak_string("69.420.42");
  delay(500);

  numberSpeaker.speak_char('6');
  numberSpeaker.speak_char('.');
  numberSpeaker.speak_char('9');
  delay(500);

  for (;;) {}
}