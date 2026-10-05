#include <Servo.h>

Servo servoX;
Servo servoY;

int posX = 90;
int posY = 90;

const int threshold = 50;

void setup() {

  // Servo pins
  servoX.attach(9);
  servoY.attach(10);

  // UART communication with ESP8266
  Serial.begin(9600);
}

void loop() {

  // Read four LDRs
  int ldr1 = analogRead(A0);
  int ldr2 = analogRead(A1);
  int ldr3 = analogRead(A2);
  int ldr4 = analogRead(A3);

  // Calculate light difference
  int diffX = ldr1 - ldr2;
  int diffY = ldr3 - ldr4;

  // -------- Horizontal / Azimuth --------
  if (abs(diffX) > threshold) {

    if (diffX > 0)
      posX++;
    else
      posX--;
  }

  // -------- Vertical / Elevation --------
  if (abs(diffY) > threshold) {

    if (diffY > 0)
      posY++;
    else
      posY--;
  }

  // Keep servo angle between 0 and 180
  posX = constrain(posX, 0, 180);
  posY = constrain(posY, 0, 180);

  // Move servos
  servoX.write(posX);
  servoY.write(posY);

  // -------- Send LDR data to ESP8266 through UART --------
  Serial.print(ldr1);
  Serial.print(" ");
  Serial.print(ldr2);
  Serial.print(" ");
  Serial.print(ldr3);
  Serial.print(" ");
  Serial.println(ldr4);

  delay(100);
}
