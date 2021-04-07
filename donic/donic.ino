/*
    Donic Arduino project

    Read README.md for pin configuration
*/

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
    sonic.init();

    Serial.begin(9600);

    delay(1000);
    lcd.clear();
}

void loop() {
    distance = sonic.distance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm");

    screen.drawDistance(distance);

    delay(1000);
}
