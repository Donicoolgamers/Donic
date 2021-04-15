#ifndef joystick_h
#define joystick_h

class Joystick{
    private:
        int sw,vrx,vry;
        int xPos, yPos;
        boolean pressed;
    public:
    
        Joystick(int SW, int VRX, int VRY)
        {
            sw = SW;
            vrx = VRX;
            vry = VRY;
        };
        void init()
        {
            pinMode(vrx, INPUT);
            pinMode(vry, INPUT);
            pinMode(sw, INPUT_PULLUP);
        }
        void readValues();
        int getDirection();

        // getters
        int getX(){return xPos;};
        int getY(){return yPos;};
        bool getPressed(){return !pressed;};
};

void Joystick::readValues()
{
    xPos = map(analogRead(vrx), 0, 1023, -100, 100);
    yPos = map(analogRead(vry), 0, 1023, -100, 100);
    pressed = digitalRead(sw);

    #ifdef VERBOSE
    Serial.print("x: ");
    Serial.println(this->getX());
    Serial.print("y: ");
    Serial.println(this->getY());
    #endif
}
/*
* return values: 
* 0 : left
* 1: down
* 2: right
* 3: up
* 4: not clear
*/
int Joystick::getDirection()
{
    readValues();
    if(yPos >= 90)
    {
        return 0;
    }
    else if(xPos >= 90)
    {
        return 1;
    }
    else if(yPos <= -90)
    {
        return 2;
    }
    else if(xPos <= -80)
    {
        return 3;
    }
    else{
        return 4;
    }
}

#endif
