const int forwardRight = 12;   
const int forwardLeft = 9;    
const int backwardRight = 10;   
const int backwardLeft = 8;  
const char in;     

const int trig1 = 2;
const int echo1 = 3;
const int trig2 = 5;
const int echo2 = 4;

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

void FR()   //function for forward action of the right motor
{
  if(distance1 >= 5 && distance1 < 25 && distance2 >= 5 && distance2 < 25)
  {

   digitalWrite(forwardRight, HIGH);
   digitalWrite(backwardRight, LOW);
  }
}

void FL()   //function for forward action of the left motor
{
  if(distance1 >= 5 && distance1 < 25 && distance2 >= 5 && distance2 < 25)
  {
   digitalWrite(forwardLeft, HIGH);
   digitalWrite(backwardLeft, LOW);
  }
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
  if(distance2 >= 5 && distance2 < 25 && distance1 > 30)
  {
    Serial.println("Distance1 = ");
   Serial.println(distance1);
   Serial.println("Distance2 = ");
   Serial.println(distance2);
   digitalWrite(forwardLeft, HIGH);
   digitalWrite(backwardRight, LOW);
  } 
}

void left()    //function for left action of the robot
{
  if(distance1 >= 5 && distance1 < 25 && distance2 > 30)
  digitalWrite(forwardRight, HIGH);
  digitalWrite(backwardLeft, LOW);
}

void allstop()    //function for stopping the robot
{
  if(distance1 < 6 && distance2 < 6)
  { 
   digitalWrite(forwardRight, LOW);
   digitalWrite(backwardRight, LOW);
   digitalWrite(backwardLeft, LOW);
   digitalWrite(forwardLeft, LOW);
  }
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
      Serial.println("Distance1 = ");
   Serial.println(distance1);
   Serial.println("Distance2 = ");
   Serial.println(distance2);
  FR();
  FL();
  right();
  left();
  allstop();
  
}
