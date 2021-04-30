#ifndef buzzer_h
#define buzzer_h

#include "pitches.h"

class Buzzer
{
private:
    int pin;
public:
    Buzzer(int PIN)
    {
        pin  = PIN;
    };
    void init()
    {
        pinMode(pin, OUTPUT);
    }
    void playNote(int, int);
    void playMelody(int);
    // Melodies, row 1 = tone, row 2 = time
  
};

void Buzzer::playNote(int frequency, int time = 1000)
{
    tone(pin, frequency);
    #ifdef VERBOSE
    Serial.print('Playing tone ');
    Serial.print(frequency);
    Serial.print(' for ');
    Serial.print(time);
    Serial.print(' ms.');
    #endif
    delay(time);
    noTone(pin);
}

void Buzzer::playMelody(int index)
{
    const int confirm[2][2] =
    {
        {NOTE_B5, NOTE_B4},
        {60, 40},
    };
}

#endif
