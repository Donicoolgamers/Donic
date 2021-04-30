#ifndef screens_h
#define screens_h

#include "LiquidCrystal_I2C.h"
#include "chars.h"
#include "joystick.h"
#include "ultrasonic.h"
#include "util.h"

class Screen
{
private:
    LiquidCrystal_I2C *lcd;
    Joystick *joystick;
    Ultrasonic *sonic;
    Util *util;

public:
    int mode = 0, refreshTime = 500;
    unsigned long previousTime = 0;
    Screen(LiquidCrystal_I2C *LCD, Joystick *Joystick, Ultrasonic *Sonic, Util *Util)
    {
        lcd = LCD;
        joystick = Joystick;
        sonic = Sonic;
        util = Util;
    };
    void init()
    {
        lcd->init();
        lcd->clear();
        lcd->backlight();
    }

    /* Return index of selected mode*/
    void StartMenu();

    void drawWelcome();
    void drawLoadingbar(int progress, int start = 0, int end = 100);
    void drawBar(int progress, int start = 0, int end = 100);
    void drawDistance(int distance);
    void drawStartMenu(int option);
    void drawBlind(int distance);
    void drawMeasuring(int distance);
    void drawSocialDistance(int distance);
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

void Screen::drawBar(int progress, int start = 0, int end = 100)
{
    int index = map(progress, start, end, 0, 16);

    // Draw empty bar
    lcd->setCursor(0, 1);
    lcd->print("                ");

    if (index < 1)
    {
        return;
    }

    lcd->setCursor(0, 1);

    if (index > 16)
    {
        lcd->print('?');
        return;
    }

    for (int i = 0; i < index && i < 16; i++)
    {
        lcd->write(byte(0b11111111));
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

    this->drawBar(distance, 0, 450);
}

void Screen::drawStartMenu(int option)
{
    lcd->clear();
    delay(50);
    // Draw arrows
    lcd->setCursor(0, 1);
    lcd->write(byte(0b01111111));
    lcd->setCursor(15, 1);
    lcd->write(byte(0b01111110));

    // Draw options
    lcd->setCursor(2, 0);
    switch (option)
    {
    case 0:
        lcd->write(byte(0));
        lcd->write(byte(1));
        lcd->print(" Blind");
        lcd->setCursor(2, 1);
        lcd->print("/  mode");
        break;
    case 1:
        lcd->write(byte(2));
        lcd->write(byte(3));
        lcd->print(" Measuring");
        lcd->setCursor(4, 1);
        lcd->print(" mode");
        break;
    case 2:
        lcd->write(byte(4));
        lcd->write(byte(5));
        lcd->print(" Social");
        lcd->setCursor(2, 1);
        lcd->write(byte(6));
        lcd->write(byte(7));
        lcd->print(" distancing");
        break;
    }
};

void Screen::StartMenu()
{
    int index = 0;
    int previous = 0;
    bool selected = false;
    int direction;
    bool pressed = false;

    // Initialize custom characters and draw first screen
    lcd->createChar(0, sunglasses1[0]);
    lcd->createChar(1, sunglasses1[1]);
    lcd->createChar(2, ruler1[0]);
    lcd->createChar(3, ruler1[1]);
    for (int i = 0; i < 4; i++)
        lcd->createChar(i + 4, virus[i]);

    this->drawStartMenu(index);

    // logic
    while (!selected)
    {
        do
        {
            joystick->readValues();
            direction = joystick->getDirection();
            pressed = joystick->getPressed();

        } while (!(direction == 0 || direction == 2) && pressed != true);
        if (pressed == true)
        {
            selected = true;
        }
        else
        {
            switch (direction)
            {
            case 2:
                if (index < 2)
                    index++;
                else if (index == 2)
                    index = 0;
                break;
            case 0:
                if (index > 0)
                    index--;
                else if (index == 0)
                    index = 2;
                break;
            }

#ifdef VERBOSE
            Serial.print("Mode selection: ");
            Serial.println(index);
#endif

            if (index != previous)
            {
                // lcd->setCursor(0, 1);
                // lcd->print("               ");
                // lcd->setCursor(0, 1);
                // lcd->print(options[index]);
                previous = index;
                this->drawStartMenu(index);
            }
        }
        delay(500);
    }

#ifdef VERBOSE
    Serial.print("Selected mode: ");
    Serial.println(index);
#endif

    mode = index;
};

void Screen::drawBlind(int distance)
{
    if (util->delayHasPassed(previousTime, refreshTime))
        this->drawDistance(distance);
}

void Screen::drawMeasuring(int distance)
{
    if (util->delayHasPassed(previousTime, refreshTime))
        this->drawDistance(distance);
}

void Screen::drawSocialDistance(int distance)
{
    if (util->delayHasPassed(previousTime, refreshTime))
        this->drawDistance(distance);
}

#endif
