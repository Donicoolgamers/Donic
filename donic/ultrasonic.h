#ifndef ultrasonic_h
#define ultrasonic_h

class Ultrasonic {
    private:
        double speedAir = 0.034;
        long time;
        int dist;
        int echo, trig;

    public:
        Ultrasonic(int echoPin, int trigPin)
        {
            echo = echoPin;
            trig = trigPin;
        };
        void init()
        {
            pinMode(echo, INPUT);
            pinMode(trig, OUTPUT);
            digitalWrite(trig, LOW);
        }
        // Returns distance in cm
        int distance()
        {
            #ifndef ULTRASONE
            digitalWrite(trig, LOW);
            delayMicroseconds(5);

            digitalWrite(trig, HIGH);
            delayMicroseconds(10);
            digitalWrite(trig, LOW);
            //29060 is about how many microseconds it takes for 5m 
            time = pulseIn(echo, HIGH, 29060);
            // s = t * v | v_air = 340 m/s | travels back and forth so /2
            dist = time * speedAir/2;
            #endif

            #ifdef ULTRASONE
            String distanceInput = Serial.readStringUntil('\n');
            dist = distanceInput.toInt();
            #endif
            #ifdef DEBUG
            Serial.print("SONIC distance: ");
            Serial.println(dist);
            #endif

            return dist;
        };
};

#endif
