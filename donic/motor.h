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
        int _delay = 100;
<<<<<<< HEAD
        int delays[5] = {100, 200, 300, 400, 500};
=======
        bool turned = true;
        //int delays[] = {100, 200, 300, 400, 500};
>>>>>>> b27069a4f3c3fa729d41fa9077a4e5f4382b955c
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
        void vibrateOnDistance(int, bool, int);
};



<<<<<<< HEAD
void Motor::vibrate(int amount)
=======
void Motor::vibrate(int degrees)
>>>>>>> b27069a4f3c3fa729d41fa9077a4e5f4382b955c
{
    Serial.print("test");
    #ifdef VERBOSE
    Serial.print("MOTOR vibrate: time = ");
    Serial.println(time);
    #endif
    if(turned)
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
    for(int i = 0; i < bursts; i++)
    {
        this->write(50);
        
    }
}

void Motor::vibrateOnDistance(int currentDistance, bool metric = true, int limit = -1)
{
  if(limit == -1)
    {
        digitalWrite(pin, LOW);
        if (util->delayHasPassed(previousTime, _delay)) {
            vibrating = !vibrating;
            digitalWrite(pin, HIGH);
            
            if (metric)
            {
                // if (distance > 300 || distance < 15)
                //     return;

                _delay = map(currentDistance, 0, 450, 100, 500);
                //delay = delays[ceil(distance/100.0)];
            }
            else
            {

            }
        }
    }
    else
    {
        digitalWrite(pin, LOW);
        if (currentDistance < limit)
        {
            if (util->delayHasPassed(previousTime, _delay)) {
                vibrating = !vibrating;
                digitalWrite(pin, HIGH);
                _delay = 1000;
            }
        }
    }

}
#endif