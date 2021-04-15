#ifndef motor_h
#define motor_h

class Motor {
    private:
        int pin;
    public:
        Motor(int motorPin)
        {
            pin = motorPin;
        }
        void init()
        {
            pinMode(pin, OUTPUT);
        }
        void vibrate(int);
        void burst(int,int);
};
void Motor::vibrate(int time)
{
    #ifdef VERBOSE
    Serial.print("MOTOR vibrate: time = ");
    Serial.println(time);
    #endif
    digitalWrite(pin, HIGH);
    delay(time);
    digitalWrite(pin, LOW);
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
        delay(del);
        digitalWrite(pin, LOW);
        delay(del);
    }
}

#endif