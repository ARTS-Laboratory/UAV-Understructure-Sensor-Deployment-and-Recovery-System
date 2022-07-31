//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(7, 6);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

int PWM = A0;
int val = 0;
int MAG = 9;

void setup()
{
  Serial.begin(9600);
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}
void loop()
{

  val = pulseIn(PWM, HIGH);
  Serial.println(val);

  
  //Send message to receiver
  if (val < 1000 ){
    
  // Package Magnet Control (Charge)
  const int text3 = 3;
  radio.write(&text3, sizeof(text3));
  delay(1000);

  //UAV Magnet Control(Discharge)
      digitalWrite(MAG, HIGH);
      delay(1);
      digitalWrite(MAG, LOW);
      delay(19);
      digitalWrite(MAG, HIGH);
      delay(1);
      digitalWrite(MAG, LOW);
      delay(19);
      digitalWrite(MAG, HIGH);
      delay(1);
      digitalWrite(MAG, LOW);
      delay(19);

  
  }

  else if ((1000<val) && (val<1900)){
  // All Magnets Control (Neutral)   
  const int text2 = 2;
  radio.write(&text2, sizeof(text2));
  delay(1000);
  
  digitalWrite(MAG, LOW);
  }

  else if (1900<val)  {
  
  //Package Magnet Control(Discharge)    
  const int text1 = 1;
  radio.write(&text1, sizeof(text1));
  delay(1000);
  
  //UAV Magnet Control(Charge)
      digitalWrite(MAG, HIGH);
      delay(2);
      digitalWrite(MAG, LOW);
      delay(18);
      digitalWrite(MAG, HIGH);
      delay(2);
      digitalWrite(MAG, LOW);
      delay(18);
      digitalWrite(MAG, HIGH);
      delay(2);
      digitalWrite(MAG, LOW);
      delay(18);
  }

  else {}

}
