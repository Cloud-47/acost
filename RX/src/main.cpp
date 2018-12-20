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
   /*
   *if the pin 5 ditect a signal do staff
   */
   if(digitalRead(5)){
      bits1 = 0;
      unsigned long deltaT = millis();//take the presint time storet in deltaT
      /*
      *in this loop we decode our bits
      */
      while(millis()-deltaT <= 10) if(digitalRead(5)) bits1 ++;//go to line 44
      //Serial.println(bits1);

      if(capture){
         boolean b = 0;
         if(bits1 > 220 && bits1 < 400) b = 0;//here we decode our bits
         if(bits1 > 100 && bits1 < 220) b = 1;
         if(b) bitSet(CH,7-pos); else bitClear(CH,7-pos); // compose our carecter
         //Serial.println(b);

         pos++;//count the number of bits

         //now print our carecter and reinisilise
         if(pos == 8){
            //Serial.println("\n");
            //Serial.println("ch is here ");
            Serial.print((char)CH);
            //Serial.println("\n");
            pos = 0;
            capture = false;
         }
      }
      if(bits1 > 600){// if bits is more than 600 thas mean that it is signal inisilizition(TX code line 21)
         capture = true;
         pos = 0;
      }
   }
}
