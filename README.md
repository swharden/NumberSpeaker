# NumberSpeaker

[![CI](https://github.com/swharden/NumberSpeaker/actions/workflows/arduino.yaml/badge.svg)](https://github.com/swharden/NumberSpeaker/actions/workflows/arduino.yaml)

**NumberSpeaker is an Arduino library for reading numbers using a speaker.** A human voice from WAV files is encoded into bytes which are stored in program memory and played back using PWM to drive a speaker.

⚠️ WARNING: This project is pre-alpha and not yet intended for public use

## Additional Resources

* [Speaking Numbers with a Microcontroller](https://swharden.com/blog/2023-08-19-speaking-microcontroller/) - A blog post describing the strategy used to encode audio files, store them in program memory, and play them back using a speaker.

* [Talkie](https://www.arduino.cc/reference/en/libraries/talkie/) is an official Arduino speech synthesis library. It is a software implementation of the [Texas Instruments speech synthesis architecture](https://en.wikipedia.org/wiki/Texas_Instruments_LPC_Speech_Chips) from the late 1970s. I found the voice to be poor quality for reading numbers, but it may be useful to users seeking more complex phrases or who are concerned about demands on program memory.