/*
    Donic Arduino project

    Read README.md for pin configuration
*/

//define this if you dont want to use ULTRASONE sensor
//#define ULTRASONE



#include "ultrasonic.h"
#include "screens.h"

// Pins
#define ECHO 11
#define TRIG 12

LiquidCrystal_I2C lcd(0x27, 16, 2);
Screen screen(&lcd);

Ultrasonic sonic(ECHO, TRIG);

long time;
int distance;

void setup() {
    screen.init();
    screen.drawWelcome();

    // Loading
    for (int i = 0; i < 7; i++)
    {
        lcd.createChar(i, loadingbar[i]);
    }

    // Ultrasonic sensor
    #ifndef ULTRASONE
    sonic.init();
    #endif

    Serial.begin(9600);

    #ifdef ULTRASONE
    Serial.println("--------------------DEBUG MODE : no ultrasone sensor--------------------");
    #endif

    delay(1000);
    lcd.clear();
}

void loop() {
    #ifndef ULTRASONE
    distance = sonic.distance();
    #endif
    #ifdef ULTRASONE
    String distanceInput = Serial.readStringUntil('\n');
    distance = distanceInput.toInt();
    #endif
    
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm\n");

    screen.drawDistance(distance);

    delay(1000);
}
