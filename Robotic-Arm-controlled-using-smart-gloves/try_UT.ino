const int forwardRight = 12;   
const int forwardLeft = 9;    
const int backwardRight = 10;   
const int backwardLeft = 8;      

const int trig1 = 2;
const int echo1 = 3;
const int trig2 = 4;
const int echo2 = 5;

long duration1;
int distance1;
long duration2;
int distance2;

void setup() {
  Serial.begin(9600);
  pinMode(forwardRight, OUTPUT);
  pinMode(forwardLeft, OUTPUT);
  pinMode(backwardRight, OUTPUT);
  pinMode(backwardLeft, OUTPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
}

void Fra()   //function for forward action of the right motor
{
   digitalWrite(forwardRight, HIGH);
   digitalWrite(forwardLeft, HIGH); 
}

/*void BR()   //function for backward action of the right motor
{
  digitalWrite(backwardRight, HIGH);
  digitalWrite(forwardRight, LOW);
}

void BL()   //function for backward action of the left motor
{
  digitalWrite(backwardLeft, HIGH);
  digitalWrite(forwardRight, LOW);
}*/

void right()   //function for right action of the robot
{
   digitalWrite(forwardLeft, HIGH);
   digitalWrite(backwardRight, LOW);
   
}

void left()    //function for left action of the robot
{
  digitalWrite(forwardRight, HIGH);
  digitalWrite(backwardLeft, LOW);
}

void allstop()    //function for stopping the robot
{
  
   
   digitalWrite(forwardRight, LOW);
   digitalWrite(backwardRight, LOW);
   digitalWrite(backwardLeft, LOW);
   digitalWrite(forwardLeft, LOW);
  
}

void loop() {
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = duration1 * 0.034/2;

  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = duration2 * 0.034/2;
  if(distance1 >= 7 && distance1 < 25 && distance2 >= 7 && distance2 < 25)
  {
  Fra();
  }
  else if(distance2 >= 7 && distance2 < 25)
  {
    right();
  }
  else if(distance1 >= 7 && distance1 < 25)
  {
   left();
  }
  else if(distance1 < 7 && distance2 < 7)
  {
  allstop();
  }
}
