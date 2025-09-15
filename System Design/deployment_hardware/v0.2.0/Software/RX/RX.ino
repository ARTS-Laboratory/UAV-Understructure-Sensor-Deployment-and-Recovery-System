//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(7, 6);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

int num=0;
int MAG=3;
int LED = 4;
void setup()
{
  
  Serial.begin(9600);
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    delay(1000);
    //char text[32] = {0};
    int msg = 0;
    radio.read(&msg, sizeof(msg));

    if (msg==3){
      digitalWrite(LED, HIGH);
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
      Serial.println("charge");
      }
    else if (msg==2){  
      digitalWrite(LED, LOW); 
      digitalWrite(MAG, LOW);
      Serial.println("neutral");
      
      }
    else {
      digitalWrite(LED, LOW);
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
      Serial.println("Discharge");
      }
  }
}
