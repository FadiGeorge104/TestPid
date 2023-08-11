#include "ring.h"
#define ENCODEROUTPUT 400
    // M1 --> EN 8 - DIR1 7 - DIR2 6 -- En1 18 - En2 19
    // M2 --> EN 3 - DIR1 4 - DIR2 5 -- En1 20 - En2 21
    // Read PB 43 -- Start circuit 45
    // Read Battery Level -- A12
    // WP 12 -- Main Brush 13
    // Sb 10 "Left" - 11 "Right" --> PWM 90
    // Blower 9 --> PWM -- FB 2
    // limit Switch 15 - 16
    // WT sensor --> 52 
const int HALLSEN_A = 20;
const int HALLSEN_B = 21;

const int HALLSEN_A2 = 18;
const int HALLSEN_B2 = 19;

int motorPWM = 8;
int motorDir = 6;
int motorDir2 = 7;

int motor2PWM = 3;
int motor2Dir = 4;
int motor2Dir2 = 5;

volatile long encoderValue1 = 0;
volatile long encoderValue2 = 0;
int interval = 650;
long previousMillis = 0;
long currentMillis = 0;

int rpm1 = 0;
int rpm2 = 0;

int motorPwm1 = 0;
int motorPwm2 = 0;
float diff1 = 0;
float diff2 = 0;
float ratio_value = 0.5;

// Variables for PID controller
double input, output;
int pwm = 0;
int pwm2 = 0;
int readDir = 0;

int setPoint = 20; // Desired speed in RPM

void setup()
{
  Serial.begin(9600);
  // Encoder Iint
  pinMode(HALLSEN_A, INPUT);
  pinMode(HALLSEN_B, INPUT);
  pinMode(HALLSEN_A2, INPUT);
  pinMode(HALLSEN_B2, INPUT);
  EncoderInit();
  // Ring Init
  ringSetup();
  //Motor
  pinMode(motorDir, OUTPUT);
  pinMode(motorDir2, OUTPUT);
  pinMode(motor2Dir, OUTPUT);
  pinMode(motor2Dir2, OUTPUT);
  previousMillis = millis();
  pinMode(43, INPUT);
  pinMode(45, OUTPUT);
  digitalWrite(45, 0);
  pinMode(A12, INPUT); // Battery Level
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
}
int counter = 0;
int motorspeed = 180;
void loop()
{
  
  int ls1 = digitalRead(15);
  int ls2 = digitalRead(16);
  int battery = analogRead(A12);
  if (ls1 == 0)
  {
    setmotor(0);
    ringRed();
  }
  if (ls2 == 0)
  {
    setmotor(0);
    ringRed();
  }
  int dir1 = 0;
  char direction = Serial.read();
  switch (direction)
  {
  case 'a':
  {
    setmotor(4);
    break;
  }
  case 'd':

  {
    setmotor(3);
    break;
  }
  case 'w':
  {
    setmotor(1);
    break;
  }
  case 's':
    // right
    {
      setmotor(2);
      break;
    }
  case 'x':
  {
    setmotor(0);
    break;
  }
  default:
    break;
  }
  // if (rpm1 < 10 && motorspeed > 200) {
  //   motorspeed = 30;
  // }
  // if (rpm2 < 10 && motorspeed > 200) {
  //   motorspeed = 30;
  // }
  encoderValue1 = 0;
  encoderValue2 = 0;
}


void EncoderInit()
{
  attachInterrupt(digitalPinToInterrupt(HALLSEN_A), updateEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(HALLSEN_B), updateEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(HALLSEN_A2), updateEncoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(HALLSEN_B2), updateEncoder2, RISING);
}

void updateEncoder()
{
  // Read both channels of the encoder to determine direction
  int channelA1 = digitalRead(HALLSEN_A);
  int channelB1 = digitalRead(HALLSEN_B);
  if (channelA1 == LOW && channelB1 == HIGH)
  {
    encoderValue1++;
  }
  if (channelA1 == HIGH && channelB1 == LOW)
  {
    encoderValue1++;
  }
}

void updateEncoder2()
{
  // Read both channels of the encoder to determine direction
  int channelA1 = digitalRead(HALLSEN_A2);
  int channelB1 = digitalRead(HALLSEN_B2);
  if (channelA1 == LOW && channelB1 == HIGH)
  {
    encoderValue2++;
  }
  if (channelA1 == HIGH && channelB1 == LOW)
  {
    encoderValue2++;
  }
}

void setmotor(int dir)
{
  if (dir == 1)
  {
    digitalWrite(motorDir2, 1);
    digitalWrite(motorDir, 0);
    analogWrite(motorPWM, motorspeed);
    digitalWrite(motor2Dir2, 1);
    digitalWrite(motor2Dir, 0);
    analogWrite(motor2PWM, motorspeed);
  }

  if (dir == 2)
  {
    digitalWrite(motorDir2, 0);
    digitalWrite(motorDir, 1);
    analogWrite(motorPWM, motorspeed);
    digitalWrite(motor2Dir2, 0);
    digitalWrite(motor2Dir, 1);
    analogWrite(motor2PWM, motorspeed);
  }
  if (dir == 3)
  {
    digitalWrite(motorDir2, HIGH);
    digitalWrite(motorDir, LOW);
    analogWrite(motorPWM, 250);
    digitalWrite(motor2Dir2, !HIGH);
    digitalWrite(motor2Dir, !LOW);
    analogWrite(motor2PWM, 0);
  }
  if (dir == 4)
  {
    digitalWrite(motor2Dir2, HIGH);
    digitalWrite(motor2Dir, LOW);
    analogWrite(motor2PWM, 250);
    digitalWrite(motorDir2, !HIGH);
    digitalWrite(motorDir, !LOW);
    analogWrite(motorPWM, 0);
  }
  if (dir == 5)
  {
    digitalWrite(motorDir2, HIGH);
    digitalWrite(motorDir, LOW);
    analogWrite(motorPWM, motorspeed);
    digitalWrite(motor2Dir2, LOW);
    digitalWrite(motor2Dir, HIGH);
    analogWrite(motor2PWM, motorspeed);
  }
  if (dir == 0)
  {
    digitalWrite(motorDir2, HIGH);
    digitalWrite(motorDir, LOW);
    analogWrite(motorPWM, 0);
    digitalWrite(motor2Dir2, HIGH);
    digitalWrite(motor2Dir, LOW);
    analogWrite(motor2PWM, 0);
  }
}