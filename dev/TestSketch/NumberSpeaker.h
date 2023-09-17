#ifndef NumberSpeaker_h
#define NumberSpeaker_h

#include "Arduino.h"
#include "NumberSpeakerAudio.h"

class NumberSpeaker {
public:
  NumberSpeaker() {}

  void begin() {
    // Use timer 2 to output PWM on pin 11
    pinMode(11, OUTPUT);
    TCCR2A |= bit(COM2A1);
    TCCR2B = bit(CS20);
    p_OCR = &OCR2A;
  }

  void speak_int(uint32_t value) {
    if (value == 0) {
      speak_digit(0);
      return;
    }

    uint32_t divisor = 1000000000;
    uint8_t real_numbers_seen = 0;
    while (divisor > 0) {
      uint8_t digit = value / divisor;

      if (digit > 0) {
        real_numbers_seen = 1;
      }

      if (real_numbers_seen) {
        speak_digit(digit);
      }

      value = value - (digit * divisor);
      divisor /= 10;
    }
  }

  void speak_float(float value) {
    char buff[8];
    dtostrf(value, 4, 6, buff);
    for (int i = 0; i < sizeof(buff); i++) {
      if (buff[i] == 0)
        return;
      speak_char(buff[i]);
    }
  }

  void speak_string(String text) {
    for (int i = 0; i < text.length(); i++) {
      char c = text.charAt(i);
      speak_char(c);
    }
  }

  void speak_char(char c) {
    if (c >= 48 && c <= 57) {
      speak_digit(c - 48);
    } else if (c == 46) {
      speak_point();
    } else {
      speak_error();
    }
  }

private:
  uint8_t *p_OCR;  // pointer to the PWM register

  void play(uint8_t samples[], int length) {
    for (int i = 0; i < length; i++) {
      uint8_t value = pgm_read_byte(&samples[i]);
      *p_OCR = value;
      delayMicroseconds(200);  // 5 kHz
    }
  }

  void tone(int duration = 1000, int delay = 50) {
    const uint8_t sinewave[] = { 127, 166, 202, 230, 248, 255, 248, 230, 202, 166, 127, 88, 52, 24, 6, 0, 6, 24, 52, 88 };
    for (int i = 0; i < duration * 10; i++) {
      *p_OCR = sinewave[i % sizeof(sinewave)];
      delayMicroseconds(delay);
    }
  }

  void speak_error() {
    tone(500, 90);
    delay(7);
    tone(120, 50);
    delay(7);
    tone(120, 50);
    delay(7);
    tone(120, 50);
  }

  void speak_point() {
    play(AUDIO_SAMPLES_POINT, sizeof(AUDIO_SAMPLES_POINT));
  }

  void speak_digit(uint8_t digit) {
    switch (digit) {
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
        speak_error();
        break;
    }
  }
};

#endif