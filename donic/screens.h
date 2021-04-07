#ifndef screens_h
#define screens_h

#include "LiquidCrystal_I2C.h"
#include "chars.h"

class Screen
{
private:
    LiquidCrystal_I2C *lcd;

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
    void drawWelcome();
    void drawLoadingbar(int progress, int start = 0, int end = 100);
    void drawDistance(int distance);
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
    lcd->setCursor(0,0);
    lcd->print("Distance: ");
    lcd->setCursor(9,0);
    lcd->print("       ");
    lcd->setCursor(10,0);
    if (distance > 500)
    {
        lcd->print("OoR");
    }
    else {
        lcd->print(distance);
        lcd->print(" cm");
    }
    
    this->drawLoadingbar(distance, 0, 430);
}

#endif
