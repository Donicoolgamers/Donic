#ifndef motor_h
#define motor_h

#include "util.h"
#include <Servo.h>

class Motor : public Servo
{
private:
    int pin;
    unsigned long previousTime = 0;
    bool vibrating = false;
    Util *util;
    int _delay = 100;
    bool turned = true;
    int delays[5] = {100, 350, 450, 550, 650};

public:
    Motor(int motorPin, Util *Util)
    {
        pin = motorPin;
        util = Util;
    }
    void init()
    {
        this->attach(pin);
    }
    void startStop(bool);
    void vibrate(int);
    void burst(int, int);
    void vibrateOnDistance(int, bool, int);
};

void Motor::vibrate(int degrees)
{
    Serial.print("test");
#ifdef VERBOSE
    Serial.print("MOTOR vibrate: time = ");
    Serial.println(time);
#endif
    if (turned)
    {
        this->write(degrees);
    }
    else
    {
        this->write(0);
    }
    turned = !turned;
}

void Motor::burst(int del, int bursts)
{
#ifdef VERBOSE
    Serial.print("MOTOR burst: delay = ");
    Serial.print(del);
    Serial.print(" amt of bursts = ");
    Serial.println(bursts);
#endif
    for (int i = 0; i < bursts; i++)
    {
        this->write(50);
    }
}

void Motor::vibrateOnDistance(int currentDistance, bool metric = true, int limit = -1)
{
    if (limit == -1)
    {
        if (util->delayHasPassed(previousTime, _delay))
        {
            _delay = map(currentDistance, 0, 450, 100, 500);
            _delay = ceil(_delay / 100.0);
            _delay = delays[_delay];
            this->vibrate(20);
        }
    }
    else
    {
        if (util->delayHasPassed(previousTime, 300) && currentDistance < limit)
        {
            this->vibrate(20);
        }
    }
}
#endif