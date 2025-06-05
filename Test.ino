#include <Servo.h>

Servo pickServo;
Servo dropServo;

#define S0 4
#define S1 5
#define S2 7
#define S3 6
#define sensorOut 8

int frequency = 0;
int color = 0;

int detectColor() {
  // Activate red photodiodes
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  Serial.print("Red = ");
  Serial.print(R);
  Serial.print("   ");
  delay(50);

  // Activate blue photodiodes
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  Serial.print("Blue = ");
  Serial.print(B);
  Serial.println("   ");
  delay(50);

  // Activate green photodiodes
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("Green = ");
  Serial.print(G);
  Serial.print("   ");
  delay(50);

  // Threshold conditions (customize as per setup)
  if (R > 20 && R < 22 && G > 27 && G < 29) {
    color = 1;
    Serial.println("Detected Color is = RED");
  }
  else if (G > 22 && G < 25 && B > 19 && B < 22) {
    color = 2;
    Serial.println("Detected Color is = ORANGE");
  }
  else if (R > 20 && R < 21 && G > 25 && G < 28) {
    color = 3;
    Serial.println("Detected Color is = GREEN");
  }
  else if (R > 24 && R < 38 && G > 30 && G < 44) {
    color = 4;
    Serial.println("Detected Color is = YELLOW");
  }
  else if (G > 27 && G < 29 && B > 19 && B < 22) {
    color = 5;
    Serial.println("Detected Color is = BLUE");
  }

  return color;
}

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Frequency-scaling to 20%
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);

  pickServo.attach(9);
  dropServo.attach(10);

  Serial.begin(9600);
}

void loop() {
  // Initial position
  pickServo.write(115);
  delay(600);

  for (int i = 115; i > 65; i--) {
    pickServo.write(i);
    delay(2);
  }
  delay(500);

  color = detectColor();
  delay(1000);

  switch (color) {
    case 1: dropServo.write(50); break;
    case 2: dropServo.write(80); break;
    case 3: dropServo.write(110); break;
    case 4: dropServo.write(140); break;
    case 5: dropServo.write(170); break;
    case 0: break;
  }

  delay(500);

  for (int i = 65; i > 29; i--) {
    pickServo.write(i);
    delay(2);
  }
  delay(300);

  for (int i = 29; i < 115; i++) {
    pickServo.write(i);
    delay(2);
  }

  color = 0;
}

