/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 10;
int led1 = 13;
int led2 = 12;
int led3 = 11;
int brightess = 255;
boolean on = false;
int fadeAmount = 10;
unsigned long remote_receive = 0;
int led_number = 1;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);  
}

void loop() {
  if (irrecv.decode(&results)) {
    remote_receive = results.value;
    Serial.println(remote_receive, HEX);
    
    
    switch(remote_receive)
    {
      case 0x540A:
        on = (!on);
        if(on == true){ onLed(led_number);}
        else{ allOff();}
        break;
      case 0xDE108:
         led_number++;
         if (led_number == 8)
         {
           led_number = 1;
         }
         onLed(led_number);
         break;
         
      case 0x5E108:
         led_number--;
         if (led_number == 0)
         {
           led_number = 7;
         }
         onLed(led_number);
         break;
         
      case 0x1E108:
        brightess = brightess + fadeAmount;
        if(brightess > 255){brightess = 255;};
        onLed(led_number);
        break;
       
      case 0x9E108:
        brightess = brightess - fadeAmount;
        if(brightess < 0){brightess = 0;};
        onLed(led_number);
        break;
      case 0x3E108:
        brightess = 255;
        led_number = 1;
        onLed(led_number);
        
    }
    
    
    
    irrecv.resume(); // Receive the next value
  }
  
  delay(100);
}
















void allOff()
{
  analogWrite(led1, 0);
  analogWrite(led2, 0);
  analogWrite(led3, 0);
}

void onLed(int nb)
{
  allOff();
  switch (nb)
  {
    case 1:
      analogWrite(led1, brightess);
      break;
    case 2:
      analogWrite(led2, brightess);
      break;
    case 3:
      analogWrite(led3, brightess);
      break;
    case 4:
      analogWrite(led1, brightess);
      analogWrite(led2, brightess);
      break;
    case 5:
      analogWrite(led1, brightess);
      analogWrite(led3, brightess);
      break;
    case 6:
      analogWrite(led2, brightess);
      analogWrite(led3, brightess);
      break;
    case 7:
      analogWrite(led1, brightess);
      analogWrite(led2, brightess);
      analogWrite(led3, brightess);
      break;
  }
}
