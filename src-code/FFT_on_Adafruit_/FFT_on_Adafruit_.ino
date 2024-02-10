#include "Adafruit_ZeroFFT.h"

#define DATA_SIZE 256

#define FS 880

int16_t data[DATA_SIZE];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A2, INPUT);

  Serial.println("Setup Complete");

}

void loop() {
  // put your main code here, to run repeatedly:
  int32_t avg = 0;
  for(int i = 0; i < DATA_SIZE; i++){
    int16_t val = analogRead(A2);
    data[i] = val;
    avg+=val;
  }

  for (int i = 0; i < 4; i++) {
    
    for(int x = i*64; x < i*64+64; x++) {
      Serial.print(data[x] + "\t");
    }
    
  }
  
  //this removes the DC offset (since the microphone is bias to Vdd/2
  
  avg = avg/DATA_SIZE;
  for(int i=0; i<DATA_SIZE; i++) data[i] = (data[i] - avg) * 64;

  //run the fft
  ZeroFFT(data, DATA_SIZE);
  float maxVal = 0;
  //data is only meaningful up to sample rate/2, discard the other half
  for(int i=0; i<DATA_SIZE/2; i++){
    if(data[i] > maxVal) maxVal = data[i];
    //Serial.println(data[i]);
  }

  delay (5000);
  


}
