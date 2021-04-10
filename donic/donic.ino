/*
    Donic Arduino project

    Read README.md for pin configuration
*/

//define this if you want all debug info in serial
#define DEBUG

//define this if you dont want to use ULTRASONE sensor
//#define ULTRASONE

//define this if you just want to test with the joystick
//#define JOYSTICK


#include "ultrasonic.h"
#include "screens.h"
#include "buzzer.h"

// Pin setup
#define ECHO 11
#define TRIG 12

#define JOYX A0
#define JOYY A1
#define JOYSW 2


LiquidCrystal_I2C lcd(0x27, 16, 2);

Joystick joystick(JOYSW, JOYX, JOYY);

Ultrasonic sonic(ECHO, TRIG);

Screen screen(&lcd, &joystick, &sonic);

int mode, distance;

void setup() {
    Serial.begin(9600);
    
    screen.init();
    joystick.init();

    screen.drawWelcome();
    delay(1000);

    // Ultrasonic sensor
    #ifndef ULTRASONE
    sonic.init();
    #endif

    #ifdef ULTRASONE
    Serial.println("--------------------DEBUG MODE : no ultrasone sensor--------------------");
    #endif

    #ifdef JOYSTICK
    Serial.println("--------------------DEBUG MODE : joystick debugging--------------------");
    #endif

    screen.StartMenu();
}

void loop() {
    
    #ifndef ULTRASONE
    distance = sonic.distance();
    #endif

  

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

    
    
    switch (screen.mode)
    {
    case 0:
        screen.Blind(distance);
        break;
    case 1: //Measuring
        screen.Measuring(distance);
        break;
    case 2: //SocialDistance
        screen.SocialDistance(distance);
        break;
    default:
        lcd.clear();
        lcd.print("Wrong mode???");
        delay(1000);
        screen.StartMenu();
        break;
    }
    delay(100);
}
