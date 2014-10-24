#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 9, 8, 7, 6);

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

int seed = 72;
int c = 0;

int hz  = 635;
int db_in= 37;

void setup() {
      

    
    lcd.createChar(0,pix1);
    lcd.createChar(1,pix2);
    lcd.createChar(2,pix3);
    lcd.createChar(3,pix4);
    lcd.createChar(4,pix5);
    
    lcd.begin(20,4);
    lcd.clear();
}

void loop(){
    lcd.setCursor(0,0);
    lcd.print(" SPEED ");
    lcd.print((2.4*hz)/381);
    lcd.print(" CM/SEC. ");
    
    lcd.setCursor(0,1); //Left bar graph
    lcd.print("L ");
    for(int i = 0; i<db_in/5; i++){
        lcd.write(4);
    }
    lcd.write((db_in % 5) - 1);
    
    lcd.setCursor(0,3); //Right bar graph
    lcd.print("R ");
    for(int i = 0; i<db_in/5; i++){
        lcd.write(4);
    }
    lcd.write((db_in % 5) - 1);
}

