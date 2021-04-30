#ifndef motor_h
#define motor_h

#include "util.h"

class Motor {
    private:
        int pin;
        unsigned long previousTime = 0;
        bool vibrating = false;
        Util *util;
        int _delay = 100;
        //int delays[] = {100, 200, 300, 400, 500};
    public:
        Motor(int motorPin, Util *Util)
        {
            pin = motorPin;
            util = Util;
        }
        void init()
        {
            pinMode(pin, OUTPUT);
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
    Serial.println(bursts);
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
void Motor::vibrateOnDistance(int distance, bool metric = true)
{
    if (util->delayHasPassed(previousTime, _delay)) {
        vibrating = !vibrating;
        digitalWrite(pin, vibrating);

        if (metric)
        {
            // if (distance > 300 || distance < 15)
            //     return;

            _delay = map(distance, 0, 450, 100, 500);
            //delay = delays[ceil(distance/100.0)];
        }
        else
        {

        }
    }

}

#endif