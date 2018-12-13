#include <Arduino.h>

int pos = 0;
unsigned char CH = 0;
unsigned int bits1 = 0;
boolean capture = false;

void setup(){
   Serial.begin(115200);
   pinMode(5,INPUT_PULLUP);
}

void loop(){
   if(digitalRead(5)){
      bits1 = 0;
      unsigned long deltaT = millis();
      while(millis()-deltaT <= 10) if(digitalRead(5)) bits1 ++;
      //Serial.println(bits1);
      if(capture){
         boolean b = 0;
         if(bits1 > 211 && bits1 < 400) b = 0;
         if(bits1 > 70 && bits1 < 210) b = 1;
         if(b) bitSet(CH,7-pos); else bitClear(CH,7-pos);
         //Serial.println(b);
         pos++;
         if(pos == 8){
            //Serial.println("\n");
            //Serial.println("ch is here ");
            Serial.print((char)CH);
            //Serial.println("\n");
            pos = 0;
            capture = false;
         }
      }
      if(bits1 > 600){
         capture = true;
         pos = 0;
      }
   }
}
