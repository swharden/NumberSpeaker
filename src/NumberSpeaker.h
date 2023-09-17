#ifndef NumberSpeaker_h
#define NumberSpeaker_h

#include "Arduino.h"

/*!
 * Class that manages speaking numbers using audio on a PWM output pin
 */
class NumberSpeaker {
public:
  NumberSpeaker();
  
  /*!
  * Setup pin 11 to use PWM for playing audio
  */
  void begin();
  
  /*!
  * Speak each digit of an integer
  */
  void speak_int(uint32_t value);
  
  /*!
  * Speak each of a floating point number including the decimal point
  */
  void speak_float(float value);
  
  /*!
  * Speak each character of a string (digits and period symbols only)
  */
  void speak_string(String text);
  
  /*!
  * Speak a single character (digits and period symbols only)
  */
  void speak_char(char c);

private:
  uint8_t *p_OCR;
  void play(uint8_t samples[], int length);
  void tone(int duration = 1000, int delay = 50);
  void speak_error();
  void speak_point();
  void speak_digit(uint8_t digit);
};

#endif