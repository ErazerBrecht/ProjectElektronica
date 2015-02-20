#define trigPin 13
#define echoPin 12

void setup() {
	Serial.begin(9600);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
}

void loop() {
	double duration, distance;

	// The sensor is triggered by a HIGH pulse of 10 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);

	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);

	//Calculate the distance (in cm).
	distance = duration / 58.2;

	Serial.print(distance);
	Serial.println(" cm");

	delay(100);
}