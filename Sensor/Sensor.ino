#include "Ultrasoon.h"

Ultrasoon u(13, 12);

void setup() {
	Serial.begin(9600);

}

void loop() {
	u.printSerialDistance();
	delay(100);
}