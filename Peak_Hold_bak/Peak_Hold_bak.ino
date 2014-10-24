#define REFVOLT 3.33

#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,9,8,7,6);

byte mod1[8] = {
    B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000};    //Characters for 
byte mod2[8] = {
    B11000, B11000, B11000, B11000, B11000, B11000,B11000, B11000};     //the normal
byte mod3[8] = {
    B11100, B11100, B11100, B11100, B11100, B11100, B11100, B11100};    //graphing
byte mod4[8] = {
    B11110, B11110, B11110, B11110, B11110, B11110, B11110, B11110};
byte mod5[8] = {
    B11111, B11111, B11111, B11111, B11111, B11111, B11111,B11111};


byte line1[8] = {
    B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000};    //Characters for
byte line2[8] = {
    B01000, B01000, B01000, B01000, B01000, B01000, B01000, B01000};    //the peak hold
byte line3[8] = {
    B00100, B00100, B00100, B00100, B00100, B00100, B00100, B00100};    //bar
byte line4[8] = {
    B00010, B00010, B00010, B00010, B00010, B00010, B00010, B00010};
byte line5[8] = {
    B00001, B00001, B00001, B00001, B00001, B00001, B00001, B00001}; 


int peak;
byte* addressOfPeakByte;
byte lastCharacter[8];
int testVal;
int offset;

void setup(){

    lcd.createChar(0,mod1);
    lcd.createChar(1,mod2);
    lcd.createChar(2,mod3);
    lcd.createChar(3,mod4);
    lcd.createChar(4,mod5);

    lcd.begin(20,4);
    Serial.begin(9600);
}






void loop(){
    testVal = 21;//random(0,70);

    printGraph(0,testVal,peak);
    //    Serial.print("Column: " + String(testVal/5) + "\n");

//    if (testVal > peak){
//        peak = testVal;
//        createPeakCharacter(peak);    //Creates the character for the peak hold, value of 6
//
//    }
//    else{                                                                    //Otherwise, set the pixel location to the place where the last character should be drawn
//        lcd.setCursor((peak/5) - offset, 0);
//
//        if (testVal -1 / 5 == peak -1 / 5){                            //If both the normal graph and the peak are in the same character then an OR 
//            createLastCharacter(peakByte, testVal);  //operation needs to be performed on each individual byte in the byte array.
//            lcd.write(7);
//        }
//        else{
//            lcd.write(6);
//        }
//    }



    delay(500);
    //lcd.setCursor(0,0);
    //    for (int z; z <= 20; z++){
    //        lcd.print(" ");}
    lcd.clear();

}









/*******************************************************************************
 ***************************FUNCTIONS***************************************
 *******************************************************************************/
void printGraph(int line, int db, int peak)
{
    
    if (db > peak){
        peak = db;
        byte* peakCharacterPointer = createPeakCharacter(peak);    //Creates the character for the peak hold, write value of 6
    }
    
    lcd.setCursor(0,2);
    lcd.print("Peak: " + String(peak));
    lcd.setCursor(0,3);
    lcd.print("Value: " + String(testVal));
    lcd.setCursor(0,line); 
    
    
    for(int i = 0; i<db/5; i++){   //Draw all of the full characters
        lcd.write(4);
    }
    
    if (db / 5 == peak / 5){                                 //If the last character exists in the same character as the peak
        if (db % 5 > 0){                                         //And if the current level is not a perfect multiple of 5, create custom character
            createLastCharacter(db);
            lcd.write(7);
            Serial.println("Draw peak and last character in same character -- 1");
        }
  
        else{                                                          //Else if the current level is a perfect multiple of five, 
            lcd.setCursor((peak/5) - offset, 0);  //I only need to draw the peak hold.
            lcd.write(6);
            Serial.println("Draw peak only -- 2");
        }
    }

    else{                                            //If the last character does not exist in the same character as the peak,
    
        if (db % 5 > 0){                       //and the current level is not a multiple of 5, then I need to draw both the peak,
            lcd.write((db%5)-1);           //and the last character of the current level seperately.
            lcd.setCursor((peak/5) - offset, 0);
            lcd.write(6);
            Serial.println("Draw peak and last character seperately");
        }
        else{                                        //and if the current level is a perfect multiple of 5,
            lcd.setCursor((peak/5) -offset, 0);//Only write the peak hold.
            lcd.write(6);
            Serial.println("Draw peak only -- 2");
        }
    }
}




void bitwiseOR_Array(byte arr1[8], byte arr2[8]){ //bitwise_OR creates a character that has all of the "on" pixels of
    for (int i = 0; i <= 8; i++){                                        //two different characters.
        lastCharacter[i] = arr1[i] | arr2[i];
    }
}


void createLastCharacter( int val){          //This function creates a character that has all the pixels in it from both
    switch(val%5 - 1){                                                                 //the normal bar graph and the bar hold. This character is needed so that
    case 0:                                                                                    //the graph will show both the current value and the peak value in the same pixel
        bitwiseOR_Array(peakByte, mod1);
        lcd.createChar(7,lastCharacter);
        break;
    case 1:
        bitwiseOR_Array(createPeakCharacter(val), mod2);
        lcd.createChar(7,lastCharacter);
        break;
    case 2:
        bitwiseOR_Array(createPeakCharacter(val), mod3);
        lcd.createChar(7,lastCharacter);
        break;
    case 3:
        bitwiseOR_Array(addressOfPeakByte, mod4);
        lcd.createChar(7,lastCharacter);
        break;
    case 4:
        bitwiseOR_Array(&addressOfPeakByte, mod5);
        lcd.createChar(7,lastCharacter);
        break;
    }
}




byte* createPeakCharacter(int val){
    switch (val%5){
    case 0:
        lcd.createChar(6, line5);        //X mod 5 == 0 only when X is a multiple of 5,
        lcd.setCursor(0,1);                  // byte line5 is 00001, or the fifth value in the 
        lcd.print("Case 0");                  //character
        peakByte = *
        offset  = 1;
        return line5;
    case 1:
        lcd.createChar(6, line1);    //If X mod 5 ==1, then 10000 should
        offset = 0;                              //be drawn for the peak hold.
        lcd.setCursor(0,1);
        lcd.print("Case 1");
        return line5;
    case 2:
        lcd.createChar(6, line2);    //If X mod == 2, then 01000
        offset = 0;                              //should be drawn for the peak hold
        lcd.setCursor(0,1);
        lcd.print("Case 2");
        return line1;
    case 3:
        lcd.createChar(6, line3);    //If X mod 5 == 3, then 00100 should
        offset = 0;                              //be drawn for the peak hold
        lcd.setCursor(0,1);
        lcd.print("Case 3");
        return line2;
    case 4:
        lcd.createChar(6, line4);  //If X mod 5 == 4, then 00010 should
        offset = 0;                            //be drawn for the peak hold
        lcd.setCursor(0,1);
        lcd.print("Case 4");
        return line4;
    }
}

