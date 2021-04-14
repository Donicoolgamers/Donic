#ifndef motor_h
#define motor_h

class Motor{
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
    digitalWrite(pin, HIGH);
    delay(time);
    digitalWrite(pin, LOW);
}
void Motor::burst(int del, int bursts)
{
    for(int i = 0; i < bursts; i++)
    {
        digitalWrite(pin, HIGH);
        delay(del);
        digitalWrite(pin, LOW);
        delay(del);
    }
}

#endif