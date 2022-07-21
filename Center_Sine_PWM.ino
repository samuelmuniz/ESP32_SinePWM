#include "math.h"

const int  divi = 50;
const float sinus[] = {0.13,
0.25,
0.37,
0.48,
0.59,
0.68,
0.77,
0.84,
0.90,
0.95,
0.98,
1.00,
1.00,
0.98,
0.95,
0.90,
0.84,
0.77,
0.68,
0.59,
0.48,
0.37,
0.25,
0.13,
0.00,
-0.13,
-0.25,
-0.37,
-0.48,
-0.59,
-0.68,
-0.77,
-0.84,
-0.90,
-0.95,
-0.98,
-1.00,
-1.00,
-0.98,
-0.95,
-0.90,
-0.84,
-0.77,
-0.68,
-0.59,
-0.48,
-0.37,
-0.25,
-0.13,
0.00};


//unsigned long micros()= 0;
unsigned long  timerClockPast = 0;
unsigned long  timerClockPastHz = 0;
int dutyCycle1  = 0;
int freq = 1;
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



  if(aux <= divi*freq){
      if(micros()- timerClockPast >= 200 ){
        
        timerClockPast = micros();
        //dutyCycle1 = 50*sin(2*M_PI*(1000*aux/(divi*freq))*0.001) + 50;
        dutyCycle1 = 50*sinus[aux/freq] + 50;

        aux++;

      }
      else if(micros()- timerClockPast <= (100 - dutyCycle1)){
        
        digitalWrite(22,LOW);
        digitalWrite(23,HIGH); 
        
      }
      else if((micros()- timerClockPast >= (100 - dutyCycle1)) && (micros()- timerClockPast <= (100 + dutyCycle1)) ){

        digitalWrite(23,LOW);
        digitalWrite(22,HIGH); 

      }
      else if((micros()- timerClockPast > (100 + dutyCycle1)) && (micros()- timerClockPast < 200)){
        
        digitalWrite(22,LOW);
        digitalWrite(23,HIGH); 
            
      }    
  }
        
  else{
    
    aux = 0;
    ConvADC = analogRead(15);
    freq = map(ConvADC,0,1023,1,50);
    timerClockPastHz = micros();
    

    
    }



  

  
}
