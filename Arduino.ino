#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);

int R_IS = 1;
int R_EN = 2;;
int R_PWM = 3;
int L_IS = 4;
int L_EN = 5;
int L_PWM = 6;

char state;
int currentVoltage = 0;

const int ACCELERATION = 5;
const int FRACTION = 15;

void setup() {
  //Setup BTS's pins
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
  
  //Setup Bluetooth
  BTSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  //Handle Bluetooth data
  if (BTSerial.available() > 0) {
    state = BTSerial.read();
  }
  
  switch (state) {
    case 'F':
      Serial.println("Move Forward");
      moveForward();
      break;
    case 'B':
      Serial.println("Move Backward");
      moveBackward();
      break;
    default:
      Serial.println("Slowing Down")
      moveStop();
  }
}

void moveForward() {
  analogWrite(L_PWM, 0);
  increaseCurrentVoltage();
  analogWrite(R_PWM, currentVoltage);
}

void moveBackward() {
  analogWrite(R_PWM, 0);
  increaseCurrentVoltage();
  analogWrite(L_PWM, currentVoltage);
}

void moveStop() {
  decreaseCurrentVoltage();
}

void increaseCurrentVoltage() {
  if (currentVoltage < 255) {
    currentVoltage += ACCELERATION;
  } else {
    currentVoltage = 255;
  }
  delay(10);
}

void decreaseCurrentVoltage() {
  if (currentVoltage > 0) {
    currentVoltage -= FRACTION;
  } else {
    currentVoltage = 0;
  }
  delay(10);
}