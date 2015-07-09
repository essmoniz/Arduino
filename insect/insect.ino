
#include <Servo.h>
#include <string.h>

Servo frontServo;
Servo rearServo;

int pingPin = 8;

int frontServoPin = 2;
int rearServoPin = 3;

int centerPos    = 90;
int centerTurnPos = 81;
int frontRightUp = 72;
int frontLeftUp  = 108;
int backRightForward = 75;
int backLeftForward = 105;
int backTurnLeftForward = 96;
int backTurnRightForward = 66;
int frontTurnLeftUp = 117;
int frontTurnRightUp = 63;

void setFrontLegs(int front)
{
  //Serial.print("Front: ");
  //Serial.println(front);
  frontServo.write(front);
}

void setRearLegs(int rear)
{
  //Serial.print("Rear: ");
  //Serial.println(rear);
  rearServo.write(rear);
}

void moveLegs(int front, int rear, int d)
{
  setFrontLegs(front);
  delay(d);
  setRearLegs(rear);
  delay(d);
}

void moveForward()
{
  moveLegs(frontRightUp, backLeftForward, 100);
  moveLegs(centerPos,centerPos, 100);
  moveLegs(frontLeftUp,backRightForward, 100);
  moveLegs(centerPos,centerPos, 100);
}

void moveBackward()
{
  moveLegs(frontRightUp, backRightForward, 250);
  moveLegs(centerPos,centerPos, 120);
  moveLegs(frontLeftUp,backLeftForward, 250);
  moveLegs(centerPos,centerPos, 120);
}

void moveBackRight()
{
  moveLegs(frontRightUp,backRightForward-6, 250);
  moveLegs(centerPos,centerPos-6, 120);
  moveLegs(frontLeftUp+9,backLeftForward-6, 250);
  moveLegs(centerPos,centerPos,120);
}

void moveTurnLeft()
{
  moveLegs(frontTurnRightUp,backTurnLeftForward,250);
  moveLegs(centerTurnPos,centerTurnPos,120);
  moveLegs(frontTurnLeftUp,backTurnRightForward,250);
  moveLegs(centerTurnPos,centerTurnPos,120);
}

void setup()
{
  Serial.begin(9600);
  
  frontServo.attach(frontServoPin);
  rearServo.attach(rearServoPin);
}

void doCmd(char *cmd)
{
  Serial.println(cmd);
  if (cmd[0] == char('f'))
    setFrontLegs(atoi(cmd+1)); 
  if (cmd[0] == char('r'))
    setRearLegs(atoi(cmd+1));
}

long microsecondsToCentimetres(long microseconds)
{
  return microseconds / 29 / 2;
}

long getDistance(int pin)
{
  long duration, cm;
  
  pinMode(pin, OUTPUT);
  digitalWrite(pin,LOW);
  delayMicroseconds(2);
  digitalWrite(pin,HIGH);
  delayMicroseconds(5);
  digitalWrite(pin,LOW);
  
  pinMode(pin, INPUT);
  duration = pulseIn(pin, HIGH);  
  return microsecondsToCentimetres(duration);
}

void readCmd()
{
/*
  while(ch != '\n') {
    if (Serial.available() > 0) {
      ch = Serial.read();
      buf[n++] = ch;
    }
  }
  buf[n-1] = (char)0;

  cmd = strtok_r(buf, ",", &crnt);
  doCmd(cmd);
  while (cmd=strtok_r(NULL,",",&crnt)) {
    doCmd(cmd);
  }
*/
  
/*  
  if (buf[0] == char('f'))
    setFrontLegs(atoi(buf+1)); 
  if (buf[0] == char('r'))
    setRearLegs(atoi(buf+1));
*/

}

int goForward = 1;

void loop()
{
  char buf[1024];
  char ch = 'a';
  int n = 0;
  char *cmd;
  char *crnt;


  if (goForward) {
    moveForward();
  }
  else {
    moveBackward();
  }
  //moveBackward();
  // moveBackRight();
  // moveTurnLeft();

  long cm = getDistance(pingPin);
  Serial.println(cm);
  Serial.println(goForward);
  if (cm < 20) {
    goForward = 0;
  }

  delay(100);
}





