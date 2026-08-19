#include <Servo.h>

Servo servoX;
Servo servoY;

int posX = 90;
int posY = 90;

void setup() {
  servoX.attach(9);
  servoY.attach(10);
}

void loop() {

  int ldr1 = analogRead(A0);
  int ldr2 = analogRead(A1);
  int ldr3 = analogRead(A2);
  int ldr4 = analogRead(A3);

  // Difference between left and right sensors
  int diffX = ldr1 - ldr2;

  // Difference between top and bottom sensors
  int diffY = ldr3 - ldr4;

  // Horizontal movement - Azimuth
  if (abs(diffX) > 50) {

    if (diffX > 0)
      posX++;
    else
      posX--;
  }

  // Vertical movement - Elevation
  if (abs(diffY) > 50) {

    if (diffY > 0)
      posY++;
    else
      posY--;
  }

  // Limit servo angles
  posX = constrain(posX, 0, 180);
  posY = constrain(posY, 0, 180);

  // Move motors
  servoX.write(posX);
  servoY.write(posY);

  delay(100);
}