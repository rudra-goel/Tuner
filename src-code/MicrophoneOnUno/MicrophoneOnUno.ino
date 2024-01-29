#include "arduinoFFT.h"


#define SAMPLES 128
#define SAMPLING_FREQUENCY 1056 // two times expected frequency based on the Nyquist Theorem

arduinoFFT fft = arduinoFFT();

unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[SAMPLES]; // array representing a vector to hold all the real components 
double vImag[SAMPLES]; // array representing a vector to hold all the imaginary components 

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(9600);
  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); // period in microseconds
}

void loop() {
  //We must sample SAMPLE many times (our case is 880)
  
  for(int i = 0; i < SAMPLES; i++){
    microSeconds = micros(); // # of microseconds since arduino executed script
    vReal[i] = analogRead(A0);
    vImag[i] = 0; // imaginary term as always zero

    
    while(micros() < (microSeconds + samplingPeriod)) {}
    
  }
  
  //This is performing the FFT on the sample
  fft.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  fft.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  fft.ComplexToMagnitude(vReal, vImag, SAMPLES);

  //Find the peak frequency and print the peak

  double peak = fft.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

  Serial.println(peak);

  delay(100);

  
  
}

void adjustLED(frequency) {

  int trueFreq = SAMPLING_FREQUENCY / 2; 
}

double calculateCents( sampledFreq ) {
   double freqRatio = sampledFreq/(SAMPLING_FREQ/2);
   
}
