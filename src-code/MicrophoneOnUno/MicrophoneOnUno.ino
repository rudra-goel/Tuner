#include "arduinoFFT.h"


#define SAMPLES 128
#define SAMPLING_FREQUENCY 1065 // two times expected frequency based on the Nyquist Theorem

arduinoFFT fft = arduinoFFT();

unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[SAMPLES]; // array representing a vector to hold all the real components 
double vImag[SAMPLES]; // array representing a vector to hold all the imaginary components 

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  
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

  double cents = calculateCents(peak-5);
  
  Serial.print("Frequency Sampled: ");
  Serial.print(peak-5);
  Serial.print("\tCents: ");
  Serial.print(cents);
  int dutyCycleOffset = 0;
  int tolerance = 5;
  int outerTolerance = 175;
  
  if (cents > outerTolerance || cents < -outerTolerance) { // display purple
    setColor(27,0,27);
  } else {
     dutyCycleOffset = (int)map(cents, -outerTolerance, outerTolerance, -55, 55);
     if (dutyCycleOffset > -tolerance && dutyCycleOffset < tolerance) {
      setColor(0, 55, 0);
     } else if (dutyCycleOffset > tolerance) {
        setColor((int)dutyCycleOffset*1.5 , 55-dutyCycleOffset, 0);
     } else if (dutyCycleOffset < tolerance) {
        setColor(0,55+dutyCycleOffset, -dutyCycleOffset);
     }
  }
  
  Serial.print("\n");
    

  
  
}

double calculateCents( double sampledFreq ) {
   double freqRatio = sampledFreq/(440);
   double cents = (log10(freqRatio))*1200*3.322038403;
   return cents;
}

void setColor(int red, int green, int blue) {
  analogWrite(10, red);
  analogWrite(6, green);
  analogWrite(3, blue);
}
