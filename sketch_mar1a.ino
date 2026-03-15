#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

SoftwareSerial BT(8,9);
Servo myServo;
LiquidCrystal_I2C lcd(0x27,16,2);

// Motor pins
int enB = 2;
#define N1 3
#define N2 4
#define N3 5
#define N4 7

// Ultrasonic Pins
#define trigPin 11
#define echoPin 12

// Buzzer & Led
int buzzerPin = 6;
int backLed = 13;

// Variables
char command;
bool movingBack = false;
bool obstacleDetected = false;

long duration;
int distance;


// Buzzer timer
unsigned long buzzerTimer = 0;

void setup() {

    // Motors Setup
    pinMode(enB, OUTPUT);
    pinMode(N1, OUTPUT);
    pinMode(N2, OUTPUT);
    pinMode(N3, OUTPUT);
    pinMode(N4, OUTPUT);
    digitalWrite(enB,HIGH);

    // Ultrasonic Setup
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    pinMode(buzzerPin, OUTPUT);
    pinMode(backLed, OUTPUT);

    // Servo Setup
    myServo.attach(10);
    myServo.write(90);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0,0);
    lcd.print("I'M AN ENGINEER");

    lcd.setCursor(0,1);
    lcd.print("ENG. AHMED");

    Serial.begin(9600);
    BT.begin(9600);
}

int getDistance() {

  int d1, d2, d3;

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  d1 = pulseIn(echoPin,HIGH) * 0.034 / 2;

  delay(10);

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  d2 = pulseIn(echoPin,HIGH) * 0.034 / 2;

  delay(10);

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  d3 = pulseIn(echoPin,HIGH) * 0.034 / 2;

  return (d1 + d2 + d3) / 3;
}


void Stop(){

  digitalWrite(N1,LOW);
  digitalWrite(N2,LOW);
  digitalWrite(N3,LOW);
  digitalWrite(N4,LOW);
}

void Forward(){

  digitalWrite(N1,LOW);
  digitalWrite(N2,HIGH);
  digitalWrite(N3,LOW);
  digitalWrite(N4,HIGH);
}

void Backward(){

  digitalWrite(N1,HIGH);
  digitalWrite(N2,LOW);
  digitalWrite(N3,HIGH);
  digitalWrite(N4,LOW);
}

void Left(){

  digitalWrite(N1,LOW);
  digitalWrite(N2,HIGH);
  digitalWrite(N3,LOW);
  digitalWrite(N4,LOW);
}

void Right(){

  digitalWrite(N1,LOW);
  digitalWrite(N2,LOW);
  digitalWrite(N3,LOW);
  digitalWrite(N4,HIGH);
}

void servoCode() {

  distance = getDistance();

    Serial.print("Distance: ");
  Serial.println(distance);

  delay(200);

  if(distance < 20 && distance > 0 && !obstacleDetected) {

    obstacleDetected = true;

    Stop();

    digitalWrite(buzzerPin, HIGH);
    delay(400);
    digitalWrite(buzzerPin, LOW);

    Backward();
    delay(500);
    Stop();
    delay(300);

    myServo.write(0);
    delay(700);
    int leftDist = getDistance();

    myServo.write(90);
    delay(400);

    myServo.write(180);
    delay(700);
    int rightDist = getDistance();

    myServo.write(90);
    delay(400);

    if(rightDist > leftDist) {

      Right();
      delay(600);

    } else {

      Left();
      delay(600);

    }

    Stop();

    obstacleDetected = false;
  }
}


void loop() {

  servoCode();

  digitalWrite(backLed,movingBack);

  if(millis() - buzzerTimer > 500){
  digitalWrite(buzzerPin,LOW);
  }
  

  if(BT.available()){

  command = BT.read();

  switch(command){

  case 'F':
  Forward();
  movingBack=false;
  break;

  case 'B':
  Backward();
  movingBack=true;
  break;

  case 'L':
  Left();
  movingBack=false;
  break;

  case 'R':
  Right();
  movingBack=false;
  break;

  case 'S':
  Stop();
  movingBack=false;
  break;

  case 'Y':
  digitalWrite(buzzerPin,HIGH);
  buzzerTimer = millis();
  break;

  }
  }

}
