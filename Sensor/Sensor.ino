#include "Ultrasoon.h"
#include "Robot.h"

Ultrasoon u(9, 10);
Robot Wagen(5, 6, 4, 8, 11, 12);

void setup() {
	Serial.begin(9600);

}

void loop() {
	//Serial.println(u.isCloser(10));

	if (u.isCloser(10))
		Wagen.Reverse(150);
	else
		Wagen.Forward(150);
}