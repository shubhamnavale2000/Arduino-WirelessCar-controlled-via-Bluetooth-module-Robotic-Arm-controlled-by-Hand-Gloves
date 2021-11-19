#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo servobase;
Servo servoarm;

RF24 radio(9, 8); // CE, CSN

const byte address[6] = "00001";

int base = 5;
int arm = 4;



void setup() {
  Serial.begin(9600);
  radio.begin();
  servobase.attach (base) ;
  servoarm.attach (arm) ; 
  radio.openReadingPipe(0, address);
  //wire.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  Serial.println("chalu hoja");
  if (radio.available())
  {
    
     char text[32] ="";
     radio.read(&text, sizeof(text));
     Serial.println(text);
     delay(1000);
  
     int16_t ax, ay;
     radio.read(&ax, sizeof(ax));
     radio.read(&ay, sizeof(ay));
     
      ax = map (ax, -17000, 17000, 0, 180);
      ay = map (ay, -17000, 17000, 0, 180);
     
     servobase.write(ax);
     servoarm.write(ay);
     
     Serial.println(ax);
     Serial.println(ay);
  }
}
