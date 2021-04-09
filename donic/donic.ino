/*
    Donic Arduino project

    Read README.md for pin configuration
*/

//define this if you dont want to use ULTRASONE sensor
//#define ULTRASONE

//define this if you just want to test with the joystick
//#define JOYSTICK


#include "ultrasonic.h"
#include "screens.h"
#include "buzzer.h"

// Pins
#define ECHO 11
#define TRIG 12



LiquidCrystal_I2C lcd(0x27, 16, 2);

Screen screen(&lcd);



Ultrasonic sonic(ECHO, TRIG);

long time;
int distance;

void setup() {
    Serial.begin(9600);
    
    screen.init();
    joystick.init();
    screen.drawWelcome();
    delay(1000);
  
    screen.drawStartMenu();

    // Loading
    for (int i = 0; i < 7; i++)
    {
        lcd.createChar(i, loadingbar[i]);
    }

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

    delay(1000);
    
}

void loop() {
/*
    #ifndef ULTRASONE
    distance = sonic.distance();
    #endif

    #ifdef ULTRASONE
    String distanceInput = Serial.readStringUntil('\n');
    distance = distanceInput.toInt();
    #endif
    
    #ifndef JOYSTICK
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm\n");
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

    screen.drawDistance(distance);
*/
    /*
    joystick.readValues();
    Serial.print("x: ");
    Serial.print(joystick.getX());
    Serial.print("\n");
    Serial.print("y: ");
    Serial.print(joystick.getY());
    Serial.print("\n");
    */
    

    delay(1000);
}
