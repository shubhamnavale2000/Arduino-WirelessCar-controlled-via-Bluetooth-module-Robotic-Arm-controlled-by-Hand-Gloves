#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <MPU6050.h>


MPU6050 sensor;
RF24 radio(9,8); //CE, CSN
//detachInterrupt(digitalPinToInterrupt(2));

const byte address[6] = "00001";

int16_t ax ,ay, az, gx, gy, gz;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  //wire.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}

void loop() {

  
 sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 Serial.println(ax);
 Serial.println(ay);
 Serial.println(az);
 Serial.println("yes");
 
delay(1000);
  if(radio.available())
 {
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  //data[0] = map (ax, -17000, 17000, 0, 180);
  // data[1] = map (ay, -17000, 17000, 0, 180);
  radio.write(&ax, sizeof(ax));
  radio.write(&ay, sizeof(ay));
  //Serial.println(data[0]);
  Serial.println("nRF is working");
  
 }
}
