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
int maxSpeed = 0;
const int ACCELERATION = 1;
const int FRACTION = 3;

int currentPos = 90;

void setup() {
  //Setup Bluetooth
  BTSerial.begin(9600);
  Serial.begin(9600);
  
  //Setup Servo
  myServo.attach(9);
  myServo.write(currentPos);
  
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
        increaseServoPos();
        myServo.write(currentPos);
        moveStop();
        break;
    case 'L':
        decreaseServoPos()
        myServo.write(currentPos);
        moveStop();
        break;
    case 'I':
        increaseServoPos();
        myServo.write(currentPos);
        break;
    case 'G':
        decreaseServoPos()
        myServo.write(currentPos);
        moveForward();
        break;
    case 'J':
        increaseServoPos();
        myServo.write(currentPos);
        moveBackward();
        break;
    case 'H':
        decreaseServoPos()
        myServo.write(currentPos);
        moveBackward();
        break;
    case '0':
        maxSpeed = 0;
        break;
    case '1':
        maxSpeed = 30;
        break;
    case '2':
        maxSpeed = 55;
        break;
    case '3':
        maxSpeed = 80;
        break;
    case '4':
        maxSpeed = 105;
        break;
    case '5':
        maxSpeed = 130;
        break;
    case '6':
        maxSpeed = 155;
        break;
    case '7':
        maxSpeed = 180;
        break;
    case '8':
        maxSpeed = 205;
        break;
    case '9':
        maxSpeed = 230;
        break;
    case '10':
        maxSpeed = 255;
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
  } else {
    analogWrite(R_PWM, 0);
    analogWrite(L_PWM, 0);
  }
}

//Speed's related Functions
void speedUp() {
  if (currentSpeed < maxSpeed) {
    currentSpeed += ACCELERATION;
  } else {
    currentSpeed = maxSpeed;
  }
}

void slowDown() {
  if (currentSpeed > 0) {
    currentSpeed -= FRACTION;
  } else {
    currentSpeed = 0;
  }
}

//Servo's related Functions
void increaseServoPos() {
    if (currentPos < 180) {
        currentPos += 1;
    } else {
        currentPos = 180;
    }
}

void decreaseServoPos() {
    if (currentPos > 0) {
        currentPos -= 1;
    } else {
        currentPos = 0;
    }
}