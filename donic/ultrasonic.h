#ifndef ultrasonic_h
#define ultrasonic_h

class Ultrasonic {
    private:
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
        /** Returns distance measures from ultrasonic
         * @param metric if true will return in cm, if false will return in inches.
         */
        int distance(bool metric = true)
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
            if (metric)
                dist = time * 0.034/2;
            else
                dist = time * 0.0133/2;
            dist = map(dist, 0,500, 0, 450);
            #endif

            #ifdef VERBOSE
            Serial.print("SONIC distance: ");
            Serial.println(dist);
            #endif

            return dist;
        };
};

#endif
