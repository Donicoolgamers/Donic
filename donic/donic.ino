
/*
    Donic Arduino project

    Read README.md for pin configuration
*/

//define this if you want all debug info in serial
//#define VERBOSE

//define this if you dont want to use ULTRASONE sensor
//#define ULTRASONE

//define this if you just want to test with the joystick
//#define JOYSTICK


#include "ultrasonic.h"
#include "screens.h"
#include "buzzer.h"
#include "motor.h"
#include "util.h"

// Pin setup
#define ECHO 11
#define TRIG 12

#define JOYX A0
#define JOYY A1
#define JOYSW 2

#define MOTOR 3

#define BUZZER 9

#define AVERAGELENGTH 10

Util util;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Joystick joystick(JOYSW, JOYX, JOYY);
Ultrasonic sonic(ECHO, TRIG);
Motor motor(MOTOR, &util);
Buzzer buzzer(BUZZER);
Screen screen(&lcd, &joystick, &motor, &util);

int mode, distance, savedDistance, position,average = 0;

int measurements[AVERAGELENGTH] = {0};

void setup()
{
    buzzer.init();
    Serial.begin(9600);
    motor.init();
    screen.init();
    joystick.init();
    screen.drawWelcome();
    delay(1000);

    // Ultrasonic sensor
    #ifndef ULTRASONE
    sonic.init();
    #endif

    #ifdef VERBOSE
    Serial.println("--------------------DEBUG MODE : verbose output-------------------------");
    #endif

    #ifdef ULTRASONE
    Serial.println("--------------------DEBUG MODE : no ultrasone sensor--------------------");
    #endif

    #ifdef JOYSTICK
    Serial.println("--------------------DEBUG MODE : joystick debugging---------------------");
    #endif

    screen.StartMenu();
}

void loop()
{
    #ifdef JOYSTICK
    joystick.readValues();
    
    Serial.print("x: ");
    Serial.print(joystick.getX());
    Serial.print("\n");
    Serial.print("y: ");
    Serial.print(joystick.getY());
    Serial.print("\n");
    Serial.print("pressed: ");
    Serial.print(joystick.getPressed());
    Serial.print("\n");
    #endif

    #ifndef ULTRASONE
        distance = sonic.distance();
        measurements[position] = distance;
        position++;
        if(position == AVERAGELENGTH)
        {
            position = 0;
        }
        average = 0;
        for(int a = 0; a < AVERAGELENGTH; a++)
        {
            average += measurements[a];
        }
        average = average/AVERAGELENGTH;
    #endif
    #ifdef ULTRASONE
    if (Serial.available() > 0)
    {
        String distanceInput = Serial.readStringUntil('\n');
        distance = distanceInput.toInt();
    }
    #endif

    joystick.readValues();
    
    switch (screen.mode)
    {
    case 0:
        screen.drawBlind(average);
        motor.vibrateOnDistance(average);
        if(joystick.getPressed())
        {
            lcd.backlight();
            screen.StartMenu();
        }
        break;
    case 1:
        screen.drawMeasuring(average, savedDistance);
        if (joystick.getPressed())
        {
            if (screen.drawSaveDistance(average) == 0)
            {
                savedDistance = average;
            }
            else
            {
                screen.StartMenu();
            }
        }
        break;
    case 2:
        screen.drawSocialDistance(average);
        motor.vibrateOnDistance(average, true, 150);
        if(joystick.getPressed())
        {
            screen.StartMenu();
        }
        break;
    default:
        lcd.clear();
        lcd.print("Wrong mode???");
        delay(1000);
        screen.StartMenu();
        break;
    }
}
