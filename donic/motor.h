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
        //int delays[] = {100, 200, 300, 400, 500};
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



void Motor::vibrate(int time)
{
    #ifdef VERBOSE
    Serial.print("MOTOR vibrate: time = ");
    Serial.println(time);
    #endif
    this->write(50);
    
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
void Motor::vibrateOnDistance(int distance, bool metric = true)
{
    digitalWrite(pin, LOW);
    if (util->delayHasPassed(previousTime, _delay)) {
        Serial.print("hello");
        vibrating = !vibrating;
        digitalWrite(pin, HIGH);
        

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