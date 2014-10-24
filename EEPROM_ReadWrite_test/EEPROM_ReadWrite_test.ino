#include <avr/eeprom.h>
#include <EEPROM.h>

unsigned int thisMeasurementTimeInSeconds;
uint16_t numberOfEvents=0;

volatile uint16_t lastEventTime = 0;
volatile uint16_t lastUploadTime = 0;

volatile boolean flag_UploadSavedEvents = false;
volatile boolean flag_SaveEvent = false;


void setup(){
    Serial.begin(9600);
    attachInterrupt(0,uploadSavedEvents, FALLING);
    attachInterrupt(1, saveEvent, FALLING);
//    eeprom_write_byte(0,0);
    EEPROM.write(0,0);
}

void loop(){
    if ((flag_UploadSavedEvents == true) && (millis()-lastUploadTime >=100)){ //Uploads saved events via Serial
        flag_UploadSavedEvents = false;
//        int numberOfEventsSaved = eeprom_read_byte(0);
        int numberOfEventsSaved = EEPROM.read(0);
        Serial.print("Displaying ");                        //Displays 
        Serial.print(numberOfEventsSaved);     //number 
        Serial.println(" events");                            //of events


        for (uint8_t i = 1; i <= numberOfEventsSaved; i ++){
//            Serial.println(eeprom_read_byte((uint8_t *) (i)));
            Serial.println(EEPROM.read(i));
        }
    }



    if ((flag_SaveEvent == true) && (millis()-lastEventTime >= 100)){
        flag_SaveEvent = false;

        numberOfEvents += 1;
//        eeprom_write_byte((uint8_t *) (numberOfEvents),   (uint8_t)((lastEventTime + 500) / 1000));
//        eeprom_write_byte(0,numberOfEvents);
        EEPROM.write(numberOfEvents, ((lastEventTime + 500) / 1000));
        EEPROM.write(0, numberOfEvents);

    }
}



void uploadSavedEvents(){
    flag_UploadSavedEvents = true;
    lastUploadTime = millis();
}

void saveEvent(){
    lastEventTime = millis();
    flag_SaveEvent = true;
}











