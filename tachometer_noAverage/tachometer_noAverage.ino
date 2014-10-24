volatile unsigned long lastEdge;
volatile unsigned long hz_count = 0;
volatile int count = 0;
unsigned long timerStart = 0;

float hz;

void setup(){
  Serial.begin(9500);
  attachInterrupt(0,risingInterrupt,RISING);
  timerStart = micros();
}

void loop(){
  if (micros() - timerStart >= 500000){
    //cli();
    //float perd = (hz_count)/float(count); 
    //float frq = ((1/perd*1000000));
                //1 over the average period / time elapsed converted to seconds which converts from Mhz to Hz
    //unsigned long timeElapsed = micros() - timerStart;
    //timerStart = micros();
    //hz_count = 0;
    //count = 0;
    //sei();
    
    Serial.println(hz,6);
    //Serial.println((perd/1000),6);
    Serial.println();
  }
    
}


void risingInterrupt(){
  hz = 1000000/(micros()-float(lastEdge));
  //count += 1;
  lastEdge = micros();

}
  


