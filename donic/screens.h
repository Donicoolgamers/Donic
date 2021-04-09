#ifndef screens_h
#define screens_h

#include "LiquidCrystal_I2C.h"
#include "chars.h"
#include "joystick.h"

#define JOYX A0
#define JOYY A1
#define JOYSW 2

Joystick joystick(JOYSW, JOYX, JOYY);

class Screen
{
private:
    LiquidCrystal_I2C *lcd;
    int mode = 0;

public:
    Screen(LiquidCrystal_I2C *LCD)
    {
        lcd = LCD;
    };
    void init()
    {
        lcd->init();
        lcd->clear();
        lcd->backlight();
    }
    int getMode() { return mode; };
    void drawWelcome();
    void drawLoadingbar(int progress, int start = 0, int end = 100);
    void drawDistance(int distance);
    void drawStartMenu();
};

void Screen::drawWelcome()
{
    lcd->print("Donic");
    lcd->setCursor(0, 1);
    lcd->print("Welcome");
};

void Screen::drawLoadingbar(int progress, int start = 0, int end = 100)
{
    int index = map(progress, start, end, 0, 16);

    // Draw empty bar
    lcd->setCursor(0, 1);
    lcd->write(byte(0));
    for (int i = 0; i < 14; i++)
    {
        lcd->write(byte(1));
    }
    lcd->write(byte(2));
    lcd->setCursor(0, 1);

    if (index < 1)
    {
        return;
    }

    lcd->setCursor(0, 1);
    lcd->write(byte(3));

    for (int i = 1; i < index && i < 15; i++)
    {
        lcd->write(byte(5));
    }
    if (index > 15)
    {
        //lcd->setCursor(15, 1);
        lcd->write(byte(6));
    }
}

void Screen::drawDistance(int distance)
{
    lcd->setCursor(0, 0);
    lcd->print("Distance: ");
    lcd->setCursor(9, 0);
    lcd->print("       ");
    lcd->setCursor(10, 0);
    if (distance > 500)
    {
        lcd->print("OoR");
    }
    else
    {
        lcd->print(distance);
        lcd->print(" cm");
    }

    this->drawLoadingbar(distance, 0, 430);
}

void Screen:: drawStartMenu()
{
    Serial.begin(9600);
    String options[3] = {"Blind", "Measuring", "Social distance"};

    int index = 0;
    int previous = 0;
    bool selected = false;
    int direction;
    int pressed;
    lcd->setCursor(0, 0);
    lcd->print("Pick a mode");
    lcd->setCursor(0, 1);
    lcd->print("               ");
    lcd->setCursor(0, 1);
    lcd->print(options[0]);
    while (!selected)
    {
        do
        {
            joystick.readValues();
            direction = joystick.getDirection();
            pressed = joystick.getPressed();
            Serial.println(pressed);
        } while (!(direction == 1 || direction == 3) && pressed != 0);

        if (pressed == 0)
        {
            selected = true;
        }
        else
        {
            switch (direction)
            {
            case 3:
                if (index < 2)
                    index++;
                else if (index == 2)
                    index = 0;
                break;
            case 1:
                if (index > 0)
                    index--;
                else if (index == 0)
                    index = 2;
                break;
            }
            if (index != previous)
            {
                lcd->setCursor(0, 1);
                lcd->print("               ");
                lcd->setCursor(0, 1);
                lcd->print(options[index]);
                previous = index;
            }
        }
        delay(500);
    }
    switch (index)
            {
            case 0:
                lcd->clear();
                lcd->setCursor(0, 0);
                lcd->print("You chose");
                lcd->setCursor(0, 1);
                lcd->print("Blind");
                break;
            case 1:
                lcd->clear();
                lcd->setCursor(0, 0);
                lcd->print("You chose");
                lcd->setCursor(0, 1);
                lcd->print("Measuring");
                break;
            case 2:
                lcd->clear();
                lcd->setCursor(0, 0);
                lcd->print("You chose");
                lcd->setCursor(0, 1);
                lcd->print("Social distance");
                break;
            }
}

#endif
