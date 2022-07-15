#include "math.h"

const int  divi = 50;


unsigned long timerClock = 0;
unsigned long  timerClockPast = 0;
int dutyCycle  = 0;
int freq = 0;
int ConvADC = 0;
int aux = 0;

void setup() {
  Serial.begin(115200);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  analogReadResolution(10);
  digitalWrite(22,LOW);
  digitalWrite(23,HIGH);

 
  

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  timerClock = micros();


  if(aux <= divi*freq){
      if(timerClock - timerClockPast >= 200 ){
        
        timerClockPast = timerClock;
        dutyCycle = 50*sin(2*M_PI*(1000*aux/(divi*freq))*0.001) + 50;
        aux++;
        
      }
      else if(timerClock - timerClockPast <= (100 - dutyCycle)){
        
        digitalWrite(22,LOW);
        digitalWrite(23,HIGH); 
        
      }
      else if((timerClock - timerClockPast >= (100 - dutyCycle)) && (timerClock - timerClockPast <= (100 + dutyCycle)) ){
        digitalWrite(23,LOW);
        digitalWrite(22,HIGH);      
      }
      else if((timerClock - timerClockPast > (100 + dutyCycle)) && (timerClock - timerClockPast < 200)){
        
        digitalWrite(22,LOW);
        digitalWrite(23,HIGH); 
            
      }    
  }
        
  else{
    
    aux = 0;
    ConvADC = analogRead(15);
    freq = map(ConvADC,0,1023,1,50);
    
    }



  

  
}
