#define REFVOLT 3.33

#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,9,8,7,6);

byte pix1[8] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000
};

byte pix2[8] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000
};

byte pix3[8] = {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100
};

byte pix4[8] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110
};

byte pix5[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};


float db;
unsigned int val;
float volts;
int peak;
void setup(){

    lcd.createChar(0,pix1);
    lcd.createChar(1,pix2);
    lcd.createChar(2,pix3);
    lcd.createChar(3,pix4);
    lcd.createChar(4,pix5);

    lcd.begin(20,4);
    //WARNING!
    analogReference(EXTERNAL);//DO NOT RUN WITH AREF PIN-IN 
    //IF THIS CMD IS COMMENTED OUT!
}

void loop(){

    scrollGraph();



}

/****************************************************************************************
 ****************************************************************************************/



float get_db(float i){
    return 20*log10(i);
}


void printGraph(int line, int db, String side)
{
    lcd.setCursor(0,line); 
    lcd.print(side);
    for(int i = 0; i<db/5; i++){   //Draws all of the full characters
        lcd.write(4);
    }
    if (db%5 > 0){                    //then,
        lcd.write((db % 5) - 1); //draws the remaining pixels
    }

}

/*******************************************************************************************
 *******************************************************************************************/

void scrollGraph(){
    for (int i = 0;i < 70;i++){
        printGraph(1,i,"A L-R ");

//        if (i > peak){
//            peak = i;
//            lcd.setCursor((6+ (i/5) - 1),1);
//            lcd.write((i%5) - 1);
//        }

        printGraph(3,i,"A L+R ");
//
//        if (i > peak){
//            peak = i;
//            lcd.setCursor((6+ (i/5) - 1),2);
//            lcd.write(i%5);
//        }


        lcd.setCursor(0,2);
        lcd.print("DB: "+String(i - 60));
        lcd.setCursor(10,2);                                          //Static Location for Peak Value Display
//        lcd.print("  Peak: " + String(peak - 60));        //Display Peak Val
        
        delay(250);
        lcd.clear();
    }
    
    
    
    
    for (int i = 70; i > 0; i--){
        printGraph(1,i,"A L-R ");
        if (i > peak){
            peak = i;
            lcd.setCursor((6+ (i/5) - 1),1);
            lcd.write(i%5);
        }
        printGraph(3,i,"A L+R ");
        if (i > peak){
            peak = i;
            lcd.setCursor((6+ (i/5) - 1),2);
            lcd.write(i%5);
        }


        lcd.setCursor(0,2);
        lcd.print("DB: "+String(i - 60));
        lcd.setCursor(10,2);                                          //Static Location for Peak Value Display
//        lcd.print("  Peak: " + String(peak - 60));        //Display Peak Val  

        delay(250);
        lcd.clear();
    }
}

void lcd_debug_info(){
    val = analogRead(A0);
    volts = val * (REFVOLT / 1023.0);
    lcd.setCursor(0,0);
    lcd.print("VAL: " + String(val));
    lcd.setCursor(0,1);
    lcd.print("VOLTS: ");
    lcd.print(volts,4);
    lcd.setCursor(0,3);
    lcd.print("DB: ");
    lcd.print(get_db(volts),3);


    delay(750);
    lcd.clear();
}


/*void halving_db(){
 for (double i = 1024; i > 0; i = i/2){
 int val = 10;//analogRead(0);
 
 lcd.setCursor(0,0);
 lcd.print("VAL: ");
 lcd.print(i,5);
 
 lcd.setCursor(0,2);
 lcd.print("DB : " + String(round(20 * log10(i))));
 delay(750);
 lcd.clear();
 }
 }*/


