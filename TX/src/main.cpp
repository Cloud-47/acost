#include <Arduino.h>
/*
*Send function take a string as paramater (the massege that we wanna send)
*/
void send(String msg){
   /*
   *variables we need
   */
   byte ch; // ch byte type so it can stor 8 bit
   unsigned int pos = 0;
   unsigned int sz = msg.length();
   /*
   *this while loop decompose the massege latter by latter
   */
   while(pos<sz){
      ch = msg.charAt(pos); //charAt(n) take the n'th carecter of a string and stor it in ch
      //Serial.print((char)ch);
      /*
      *inisilize the communication
      */
      tone(3,40000);//tone(pin number,frequency) genirate 40KHz square signal at pin 3
      delay(10);//whene you read the RX programe go to line 
      noTone(3);//stop the signal
      /*
      *this for loop decompose the carecters (latter) to assci code and bit by bit
      */

      for(int i=0;i<8;i++){
         boolean b;
         b = bitRead(ch,7-i);//store the assci bits of a carrecter by using bitRead(carecter,bit number)
         /*
         *if b is true (1) than we sen signal for 2ms
         */
         if(b){
            tone(3,40000);
            delay(2);
         }
         /*
         *if b is false (0) than we sen signal for 4ms
         */
         else{
            tone(3,40000);
            delay(4);
         }
         noTone(3);//no signal for 10ms
         delay(10);
      }

      pos++;//go to the next carecter
   }
}

void setup(){

    Serial.begin(115200);
    pinMode(3,OUTPUT);
}

void loop(){
   send("hilo world");
   send("\n\n");
}
