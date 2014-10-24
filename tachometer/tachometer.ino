#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 9, 8, 7, 6);

unsigned long time_elapsed = 0;
float hz = 0;
float cmSec;
unsigned long timer_start = 0;
volatile unsigned int edges = 0;

//TODO: Create an array for rolling average

void setup(){
  Serial.begin(9600);
  lcd.begin(20, 4);
 
  //disable interrupts
  //Set timer1 or timer2 to 0
  //Set the selected timer's clock speed
  //attach an interrupt to calculate the time
  attachInterrupt(0,isr,CHANGE); //Interrupt on PIN D3
  //capture current time
  timer_start = micros();
}

/******************************************************************************
*******************************************************************************/

void loop(){
  if (micros() - timer_start >= 1000000){
    //If 1000000 micros (1 seconds) has passed, stop the interrupt counter,
    //and stop all interrupts in order to get an accurate time read
    cli();
    
    // ** detachInterrupt(0); ** //
    
    //calculate the ticks/second, i.e. frequency and display on screen.
    time_elapsed = micros() - timer_start; //time since timer started
    
    
    hz = edges/2.0/(time_elapsed/1000000);
    cmSec = convert(hz);
    /*divide by 2.0 because I measure each rise/fall for greater accuracy.
      divide by 1,000,000 because this is the scaler for converting between us
      and seconds, which is what I have been using.*/
    
//   lcd.setCursor(0,0);
//   for(int i = 0; i<20;i++){
//       lcd.print(" ");
//   }
//   lcd.setCursor(0,0);
//   lcd.print(hz);
//   lcd.print(" HZ");
//   
//   lcd.setCursor(0,1);
//    for(int i = 0; i<20;i++){
//       lcd.print(" ");
//   }
//   lcd.setCursor(0,1);
//   lcd.print(cmSec);
//   lcd.print(" CM/SEC");
    lcd.setCursor(0,0);
    for(int i = 0; i<20;i++){
        lcd.print(" ");
    }
    lcd.setCursor(0,0);
    lcd.print(" SPEED ");
    lcd.print(cmSec);
    lcd.print(" CM/SEC. ");
//Start interrupts back up
    sei();
    
    /****DEBUG***/
//    Serial.println("hz, edges, time_elapsed:");
//    Serial.println(hz); //DEBUGGING
//    Serial.println(edges);
//    Serial.println(time_elapsed);
//    Serial.println(" ");
    /***DEBUG***/
    
    
    
    //reset the edges counter
    edges = 0;
    
    //Restart the timer,
    timer_start = micros();
  }
}

/******************************************************************************
*******************************************************************************/
float convert(float hz){
   return (2.4*hz)/381;
}

void print_lcd(int l,float s){
  lcd.setCursor(0,l);
  lcd.print(s);
}

void isr(){ //Interrupts Service Routine
  edges += 1;
}

/******************************************************************************
*******************************************************************************/

