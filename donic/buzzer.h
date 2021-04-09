#ifndef buzzer_h
#define buzzer_h

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
    void playSound(int, int);
};

void Buzzer::playSound(int frequency, int time = 1000)
{
    tone(pin, frequency);
    delay(time);
    noTone(pin);
}

#endif
