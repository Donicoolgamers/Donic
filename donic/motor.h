#ifndef motor_h
#define motor_h

#include "util.h"
#include <Servo.h>



class Motor : public Servo{
    private:
        int pin;
        unsigned long previousTime = 0;
        bool vibrating = false;
        Util *util;
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
        void burst(int,int);
        void vibrateOnDistance(int, bool);
};

void Motor::startStop(bool start = false)
{
    if (start)
        digitalWrite(pin, HIGH);
    else
        digitalWrite(pin, LOW);
}

void Motor::vibrate(int time)
{
    #ifdef VERBOSE
    Serial.print("MOTOR vibrate: time = ");
    Serial.println(time);
    #endif
    digitalWrite(pin, HIGH);
    vibrating = true;
    delay(time);
    digitalWrite(pin, LOW);
    vibrating = false;
}

void Motor::burst(int del, int bursts)
{
    #ifdef VERBOSE
    Serial.print("MOTOR burst: delay = ");
    Serial.print(del);
    Serial.print(" amt of bursts = ");
    Serial.println(burst);
    #endif
    for(int i = 0; i < bursts; i++)
    {
        digitalWrite(pin, HIGH);
        vibrating = true;
        delay(del);
        digitalWrite(pin, LOW);
        vibrating = false;
        delay(del);
    }
}
// use in loop. God may save us all
void Motor::vibrateOnDistance(int distance, bool metric = true)
{
    int delay;
    if (metric)
    {
        if (distance > 300)
            return;
        if (distance > 250)
        {
            delay = 10000;
        }
        else if (distance > 150)
        {
            delay = 5000;
        }
        else if (distance > 50)
        {
            delay = 1000;
        }
    }
    else
    {

    }

    if (util->delayHasPassed(previousTime, delay)) {
        if (vibrating)
        {
            digitalWrite(pin, LOW);
            vibrating = false;
        }
        else
        {
            digitalWrite(pin, HIGH);
            vibrating = true;
        }
    }
}

#endif