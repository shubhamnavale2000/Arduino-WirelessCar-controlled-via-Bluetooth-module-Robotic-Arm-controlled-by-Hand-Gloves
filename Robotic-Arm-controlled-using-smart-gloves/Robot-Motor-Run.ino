#include <Wire.h>

#include <MPU6050.h>

#include <Servo.h>   

Servo base;    
Servo arm;      

int base1 = 4;
int arm1 = 2;
MPU6050 sensor ;

int16_t ax, ay, az ;

int16_t gx, gy, gz ;

void setup ( )

{ 

base.attach ( base1 );
arm.attach ( arm1 );
Wire.begin ( );

Serial.begin  (9600); 

Serial.println  ( "Initializing the sensor" ); 

sensor.initialize ( ); 

Serial.println (sensor.testConnection ( ) ? "Successfully Connected" : "Connection failed"); 

delay (1000); 

Serial.println ( "Taking Values from the sensor" );

delay (1000);

}




void loop ( ) 

{ 

sensor.getMotion6 (&ax, &ay, &az, &gx, &gy, &gz);

ax = map (ax, -17000, 17000, 0, 180) ;

Serial.println (ax);

base.write (ax); 

ay = map (ay, -17000, 17000, 0, 180) ;

Serial.println (ay);

arm.write (ay); 

delay (200);

}
