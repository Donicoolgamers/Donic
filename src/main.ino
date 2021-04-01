#include <LiquidCrystal_I2C.h>

#define ECHO 11
#define TRIG 12

LiquidCrystal_I2C lcd(0x27, 16, 2);

long time;
int distance;

void setup() {
    // LCD
    lcd.init();
    lcd.clear();
    lcd.backlight();
    lcd.print("Donic");
    lcd.setCursor(0,1);
    lcd.print("Welcome");

    // Loading
    for (int i = 0; i < 7; i++)
    {
    lcd.createChar(i, loadingbar[i]);
    }

    // Ultrasonic sensor
    pinMode(ECHO, INPUT);
    pinMode(TRIG, OUTPUT);
    digitalWrite(TRIG, LOW);

    Serial.begin(9600);

    delay(100);
    lcd.clear();
}

void loop() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(5);

    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    time = pulseIn(ECHO, HIGH);
    // s = t * v | v_air = 340 m/s | travels back and forth so /2
    distance = time * 0.034/2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm");

    lcd.setCursor(0,0);
    lcd.print("Distance: ");
    lcd.setCursor(9,0);
    lcd.print("       ");
    lcd.setCursor(10,0);
    if (distance > 500)
    {
        lcd.print("OoR");
    }
    else {
        lcd.print(distance);
        lcd.print(" cm");
    }
    drawDistance(distance);

    delay(1000);
}

void drawDistance(int distance) {
    int index  = map(distance, 0, 430, 0, 16);
  
    // if (distance > 500) {
    //     lcd.setCursor(0,1);
    //     lcd.print("                ");
    //     lcd.setCursor(0,1);
    //     lcd.print("OoR");
    //     return;
    // }

    // Draw empty bar
    lcd.setCursor(0,1);
    lcd.write(byte(0));
    for(int i = 0; i < 14; i++)
    {
    lcd.write(byte(1));
    }
    lcd.write(byte(2));
    lcd.setCursor(0,1);

    if (index < 1)
    {
        return;
    }
    lcd.setCursor(0,1);
    lcd.write(byte(3));
    for (int i = 1; i < index && i < 15; i++)
    {
        lcd.write(byte(5));
    }
    if (index > 15)
    {
        lcd.setCursor(15,1);
        lcd.write(byte(6));
    }
}