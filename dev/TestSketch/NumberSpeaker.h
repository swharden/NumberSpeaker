#ifndef NumberSpeaker_h
#define NumberSpeaker_h

#include "Arduino.h"
#include "NumberSpeakerAudio.h"

void play(uint8_t samples[], int length) {

  // Use timer 2 to generate an analog voltage using PWM on pin 11
  pinMode(11, OUTPUT);
  TCCR2A |= bit(COM2A1);
  TCCR2B = bit(CS20);

  // Shine the status LED while we are playing
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // Send each sample to the PWM and delay to achieve 5 kHz
  for (int i = 0; i < length; i++) {
    uint8_t value = pgm_read_byte(&samples[i]);
    OCR2A = value;
    delayMicroseconds(200); // adjust to customize speed
  }

  digitalWrite(LED_BUILTIN, LOW);
}

void play_point() {
  play(AUDIO_SAMPLES_POINT, sizeof(AUDIO_SAMPLES_POINT));
}

void play_digit(uint8_t digit) {
  switch (digit){
    case 0:
      play(AUDIO_SAMPLES_0, sizeof(AUDIO_SAMPLES_0));
      break;
    case 1:
      play(AUDIO_SAMPLES_1, sizeof(AUDIO_SAMPLES_1));
      break;
    case 2:
      play(AUDIO_SAMPLES_2, sizeof(AUDIO_SAMPLES_2));
      break;
    case 3:
      play(AUDIO_SAMPLES_3, sizeof(AUDIO_SAMPLES_3));
      break;
    case 4:
      play(AUDIO_SAMPLES_4, sizeof(AUDIO_SAMPLES_4));
      break;
    case 5:
      play(AUDIO_SAMPLES_5, sizeof(AUDIO_SAMPLES_5));
      break;
    case 6:
      play(AUDIO_SAMPLES_6, sizeof(AUDIO_SAMPLES_6));
      break;
    case 7:
      play(AUDIO_SAMPLES_7, sizeof(AUDIO_SAMPLES_7));
      break;
    case 8:
      play(AUDIO_SAMPLES_8, sizeof(AUDIO_SAMPLES_8));
      break;
    case 9:
      play(AUDIO_SAMPLES_9, sizeof(AUDIO_SAMPLES_9));
      break;
    default:
      break;
  }
}

void Speak(String text){
  for(int i =0; i < text.length(); i++ ) {
    char c = text.charAt(i);
    if (c >= 48 && c <= 57){
      play_digit(c - 48);
    } else if (c == 46) {
      play_point();
    } else {
      // error tone
    }
  }
}

void Speak(float value){

}

#endif