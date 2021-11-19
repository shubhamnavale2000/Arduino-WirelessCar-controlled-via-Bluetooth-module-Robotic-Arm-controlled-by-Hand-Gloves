int forwardRight = 12;   //right motor, forward action 
 int forwardLeft = 9;    //left motor, forward action 
 int backwardRight =10 ;   //right motor, backward action 
 int backwardLeft = 8;    //left motor, backward action 
 char in;     //variable to store the character received from bluetooth module 
 
 
 void setup() 
 { 
   pinMode(forwardRight, OUTPUT); 
   pinMode(forwardLeft, OUTPUT); 
   pinMode(backwardRight, OUTPUT); 
   pinMode(backwardLeft, OUTPUT); 
   Serial.begin(9600);   //for establishing communication between arduino and others at 9600 bauds(standard value) 
 } 
 
 
 void FR()   //function for forward action of the right motor 
 { 
   digitalWrite(forwardRight, HIGH); 
   digitalWrite(backwardRight, LOW); 
 } 
 
 
 void FL()   //function for forward action of the left motor 
 { 
   digitalWrite(forwardLeft, HIGH); 
   digitalWrite(backwardLeft, LOW); 
 } 
 
 
 void BR()   //function for backward action of the right motor 
 { 
   digitalWrite(backwardRight, HIGH); 
   digitalWrite(forwardRight, LOW); 
 } 
 
 
 void BL()   //function for backward action of the left motor 
 { 
   digitalWrite(backwardLeft, HIGH); 
   digitalWrite(forwardRight, LOW); 
   } 
 
 
 void right()   //function for right action of the robot 
 { 
   digitalWrite(forwardLeft, HIGH); 
   digitalWrite(backwardRight, HIGH); 
 } 
 
 
 void left()    //function for left action of the robot 
 { 
   digitalWrite(forwardRight, HIGH); 
   digitalWrite(backwardLeft, HIGH); 
 } 
 
 
 void allstop()    //function for stopping the robot 
 { 
   digitalWrite(forwardRight, LOW); 
   digitalWrite(backwardRight, LOW); 
   digitalWrite(backwardLeft, LOW); 
   digitalWrite(forwardLeft, LOW); 
 } 
 
 
 void loop() 
 { 
   if(Serial.available())    //checking whether signal is reaching the arduino or not 
   { 
    in = Serial.read();    //storing the value of incoming character from bluetooth module 
    if(in == 'F')    //if the value from bluetooth is F, then move forward 
    { 
     // right();
     FR(); 
     FL();   
    } 
 
 
    else if(in == 'B')   //if the value from bluetooth is B, then move backward 
    { 
     // left();
     BR(); 
     BL(); 
    } 
 
 
    else if(in == 'L')    //if the value from bluetooth is L, then move left 
    { 
     left();
     //BR(); 
     //BL(); 
    } 
 
 
    else if(in == 'R')    //if the value from bluetooth is R, then move right 
    { 
      right();
      //FR(); 
     //FL(); 
    } 
 
 
    else 
    { 
     allstop();    // if nothing from the bluetooth module, then stop 
    } 
   } 
 }  
