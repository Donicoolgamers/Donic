#ifndef joystick_h
#define joystick_h

class Joystick{
    private:
        int sw,vrx,vry;
        int xPos, yPos, pressed;
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

        // getters
        int getX(){return xPos;};
        int getY(){return yPos;};
        int getPressed(){return pressed;};
};

void Joystick::readValues()
{
    xPos = analogRead(vrx);
    yPos = analogRead(vry);
    pressed = digitalRead(sw);
    
}

#endif
