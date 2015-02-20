#include "Ultrasoon.h"

Ultrasoon u(12, 13);

void setup() {
	Serial.begin(9600);

}

void loop() {
	Serial.println(u.isCloser(10));
}