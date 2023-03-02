#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);

#include <Servo.h>
Servo myServo;

int R_IS = 1;
int R_EN = 2;;
int R_PWM = 3;
int L_IS = 4;
int L_EN = 5;
int L_PWM = 6;

char state;

int currentSpeed = 0;
const int ACCELERATION = 1;
const int FRACTION = 3;

void setup() {
  //Setup Bluetooth
  BTSerial.begin(9600);
  Serial.begin(9600);
  
  //Setup Servo
  myServo.attach(9);
  myServo.write(90);
  
  //Setup Motor;
  pinMode(R_IS, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_IS, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  
  digitalWrite(R_IS, LOW);
  digitalWrite(L_IS, LOW);
  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);
}

void loop() {
  if (BTSerial.available() > 0) {
    state = BTSerial.read();
  }
  
  switch (state) {
    case 'F':
      myServo.write(90);
      moveForward();
      break;
    case 'B':
      myServo.write(90);
      moveBackward();
      break;
    case 'R':
      myServo.write(180);
      moveStop();
      break;
    case 'L':
      myServo.write(0);
      moveStop();
      break;
    case 'I':
      myServo.write(135);
      moveForward();
      break;
    case 'G':
      myServo.write(45);
      moveForward();
      break;
    case 'J':
      myServo.write(135);
      moveBackward();
      break;
    case 'H':
      myServo.write(45);
      moveBackward();
      break;
    default:
      myServo.write(90);
      moveStop();
      break;
  }
  
  delay(10);
}

//Motor's related Functions
void moveForward() {
  speedUp();
  analogWrite(L_PWM, currentSpeed);
  analogWrite(R_PWM, 0);
}

void moveBackward() {
  speedUp();
  analogWrite(R_PWM, currentSpeed);
  analogWrite(L_PWM, 0);
}

void moveStop() {
  slowDown();
  if (analogRead(R_PWM) != 0) {
    analogWrite(R_PWM, currentSpeed);
    analogWrite(L_PWM, 0);
  } else if (analogRead(L_PWM) != 0) {
    analogWrite(L_PWM, currentSpeed);
    analogWrite(R_PWM, 0);
  }
}

//Speed's related Functions
void speedUp() {
  if (currentSpeed < 255) {
    currentSpeed += ACCELERATION;
  } else {
    currentSpeed = 255;
  }
}

void slowDown() {
  if (currentSpeed > 0) {
    currentSpeed -= FRACTION;
  } else {
    currentSpeed = 0;
  }
}