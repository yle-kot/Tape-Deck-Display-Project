//.#include <LiquidCrystal.h>
//LiquidCrystal lcd(12, 11, 9, 8, 7, 6);
//
//int timerStart = 0;
//int counter = 0;
//boolean complete = 0;

void setup(){
//    lcd.begin(20, 4);
//    timerStart = micros();
    pinMode(1,OUTPUT);
}

void loop(){
    //    if ((micros() - timerStart < 500000) && complete != 1){
    //        
    //        counter +=1;
    //    }
    //    else{
    //        complete = 1;
    //        lcd.setCursor(0,0);
    //        lcd.print(counter);
    //        delay(500);
    //    }
    digitalWrite(1,HIGH);
    log10(1569);
    digitalWrite(1,LOW);


}

