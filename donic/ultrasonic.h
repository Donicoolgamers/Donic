class Ultrasonic {
    private:
        double speedAir = 0.034;
        long time;
        int dist;
        int echo, trig;

    public:
        Ultrasonic(int echoPin, int trigPin)
        {
            echo = echo;
            trig = trig;
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
            digitalWrite(trig, LOW);
            delayMicroseconds(5);

            digitalWrite(trig, HIGH);
            delayMicroseconds(10);
            digitalWrite(trig, LOW);

            time = pulseIn(echo, HIGH);
            // s = t * v | v_air = 340 m/s | travels back and forth so /2
            dist = time * speedAir/2;
            return dist;
        };
};