/*
 *NRF module connection  
Radio -> Arduino
CE    -> 9
CSN   -> 10 (Hardware SPI SS)
MOSI  -> 11 (Hardware SPI MOSI)
MISO  -> 12 (Hardware SPI MISO)
SCK   -> 13 (Hardware SPI SCK)
IRQ   -> No connection in this example
VCC   -> No more than 3.6 volts
GND   -> GND

 *H Bridge L293D Connectioon

H-Bridge -> Arduino
1   -> 5  (RHS motor PWM) 
2   -> 2  (RHS motor Direction a)
7   -> 3  (RHS motor Direction B)
9   -> 6  (LHS motor PWM)
15  -> 4  (LHS motor Direction a)
10  -> 7  (LHS motor Direction a)
*/
#include <SPI.h> // NRFLite uses Arduino SPI when used with an ATmega328.  This include is not necessary when using an ATtiny84/85.
#include <NRFLite.h>// NRF librady

  int mot1en = 5 ;   // RHS motor PWM
  int mot2en = 6 ;   // LHS motor PWM
  int mot1dira = 2;  // RHS motor direction a
  int mot1dirb = 3;  // RHS motor direction b
  int mot2dira = 4;  // LHS motor direction a
  int mot2dirb = 7;  // LHS motor direction b
  int NRF_connt = 8; // NRF interface working status led
  bool for_rev_en_bit,lft_rt_en_bit,for_bit,rev_bit,lft_bit,rt_bit; // motor control bit will derived from gyro signal 
  double for_rev,lft_rt; // Actual angle value of "X" and "Y" axis recieved from transmitter 
  byte count;
  int datapac,led_state;
  const static uint8_t RADIO_ID      = 0;   // Our radio's id.  The transmitter will send to this id.
  const static uint8_t PIN_RADIO_CE  = 9;   // CE pin of NRF
  const static uint8_t PIN_RADIO_CSN = 8;  // CSN pin of NRF
  struct RadioPacket1 {  // Data structure for NRF recieved data storage. it shoud match with Transmitter NRF Data Structure. 
  	uint8_t FromRadioId; // We'll load this with the Id of the radio who sent the packet.
  	uint8_t GYROX;
    uint8_t GYROY;
  };
NRFLite _radio;
RadioPacket1 _radioData1;
void setup()
{
	delay(500); // Give the serial monitor a little time to get ready so it shows all serial output.
	Serial.begin(115200);
//Motor setup
  pinMode(mot1en,OUTPUT);
  pinMode(mot2en,OUTPUT);
  pinMode(mot1dira,OUTPUT);
  pinMode(mot1dirb,OUTPUT);
  pinMode(mot2dira,OUTPUT);
  pinMode(mot2dirb,OUTPUT);
  pinMode(mot2en,OUTPUT);
    pinMode(NRF_connt,OUTPUT);
//Motor setup closed
	if (_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)) {
		Serial.println("Radio initialized");
	}
 
	else {
		Serial.println("Cannot communicate with radio");
		while (1) {} // Wait here forever.
	}
}
void loop()
{
	uint8_t packetSize = _radio.hasData(); // hasData returns 0 if there is data packet.
  if (packetSize == sizeof(RadioPacket1)) {
		_radio.readData(&_radioData1);
		for_rev = _radioData1.GYROY;
    lft_rt =  _radioData1.GYROX;
    if(for_rev>169 &  for_rev <= 255){ for_rev = map(for_rev,169,255,-86,0);}
    if(lft_rt>169 &  lft_rt <= 255){ lft_rt = map(lft_rt,169,255,-86,0);}    
	}
if(count <= 200){
  datapac = datapac + packetSize;
  count ++;
  }
if(count >= 201){ 
  if(datapac == 0){for_rev = 0; lft_rt = 0;count = 0;led_state= LOW;Serial.println("NRF fail");}
  else {datapac =0; count=0;Serial.println("NRF working");led_state = HIGH;}
  }
if (for_rev > -6 & for_rev < 6 ){
    for_rev_en_bit = LOW;
    }
    else {
      for_rev_en_bit = HIGH;
      if(for_rev >6){for_bit = HIGH; }else {for_bit = LOW;}
      if(for_rev <-6){rev_bit = HIGH;} else {rev_bit = LOW;}
    }
if (lft_rt > -6 & lft_rt < 6){  //no speed variation moment
    lft_rt_en_bit = LOW;
    }
    else{ 
    lft_rt_en_bit = HIGH;   
    if(lft_rt >6)lft_bit = HIGH; else lft_bit = LOW;
    if(lft_rt <-6)rt_bit = HIGH; else rt_bit = LOW;
    }
if (for_rev_en_bit == HIGH & for_bit == HIGH)forward();
else if (for_rev_en_bit == HIGH & rev_bit == HIGH)revarse();
//else if (for_rev_en_bit == LOW & lft_rt_en_bit == HIGH & lft_bit == HIGH)leftonly();
//else if (for_rev_en_bit == LOW & lft_rt_en_bit == HIGH & rt_bit == HIGH)rightonly();
else {stopped();}
digitalWrite(NRF_connt,led_state);
}
void forward(){
    digitalWrite(mot1dira,HIGH);  
    digitalWrite(mot1dirb,LOW);
    digitalWrite(mot2dira,HIGH);  
    digitalWrite(mot2dirb,LOW);
    //Serial.println("forward on");
  if (lft_rt_en_bit == LOW){
    int x = map(for_rev,6,20,80,255);
        x = constrain(x,80,255);
        analogWrite(mot1en,x);
        analogWrite(mot2en,x);
        Serial.print("lft rt bit,");Serial.print(lft_rt_en_bit);Serial.print(",");Serial.print(x);  
        delay(2000);      
    }  
  if (lft_rt_en_bit == HIGH & lft_bit == HIGH){
    int x = map(for_rev,6,20,80,255);
    int y = map(lft_rt,6,50,80,255);
        x = constrain(x,80,255);
        y = constrain(y,50,255);
        analogWrite(mot1en,x-y);
        analogWrite(mot2en,x);
        delay(2000);
    }
  if (lft_rt_en_bit == HIGH & rt_bit == HIGH){
        int x = map(for_rev,6,20,80,255);
        int y = map(lft_rt,-6,-50,80,255);
        x = constrain(x,80,255);
        y = constrain(y,50,255);
        analogWrite(mot1en,x);
        analogWrite(mot2en,x-y);
        delay(2000);
    }    
  }
void revarse(){
    digitalWrite(mot1dira,LOW);  
    digitalWrite(mot1dirb,HIGH);
    digitalWrite(mot2dira,LOW);  
    digitalWrite(mot2dirb,HIGH);
    //Serial.println("reverse on");
     if (lft_rt_en_bit == LOW){
    int x = map(for_rev,-6,-20,80,255);
    x = constrain(x,80,255);
        analogWrite(mot1en,x);
        analogWrite(mot2en,x);
        Serial.print("lft rt bit,");Serial.print(lft_rt_en_bit);Serial.print(",");Serial.print(x);  
        delay(2000);      
    }  
  if (lft_rt_en_bit == HIGH & lft_bit == HIGH){
    int x = map(for_rev,-6,-20,80,255);
    int y = map(lft_rt,6,50,80,255);
        x = constrain(x,80,255);
        y = constrain(y,80,255);
        analogWrite(mot1en,x-y);
        analogWrite(mot2en,x);
    }
  if (lft_rt_en_bit == HIGH & rt_bit == HIGH){
        int x = map(for_rev,-6,-20,80,255);
        int y = map(lft_rt,-6,-50,80,255);
        x = constrain(x,80,255);
        y = constrain(y,80,255);
        analogWrite(mot1en,x);
        analogWrite(mot2en,x-y);
        delay(2000);
    }    
}
void leftonly(){
    digitalWrite(mot1dira,LOW);  
    digitalWrite(mot1dirb,HIGH);
    digitalWrite(mot2dira,HIGH);  
    digitalWrite(mot2dirb,LOW);
    //Serial.println("Only right on");
        analogWrite(mot1en,180);
        analogWrite(mot2en,180);
        delay(2000);}
void rightonly(){
    digitalWrite(mot1dira,HIGH);  
    digitalWrite(mot1dirb,LOW);
    digitalWrite(mot2dira,LOW);  
    digitalWrite(mot2dirb,HIGH);
    //Serial.println("Only left on");
        analogWrite(mot1en,180);
        analogWrite(mot2en,180);
        delay(2000);}
void stopped(){
    analogWrite(mot1en,0);
    analogWrite(mot2en,0);
    digitalWrite(mot1dira,LOW);  
    digitalWrite(mot1dirb,LOW);
    digitalWrite(mot2dira,LOW);  
    digitalWrite(mot2dirb,LOW);
    Serial.println("Stopped");  
    delay(2000);
}
