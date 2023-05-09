#include <filters.h> // See README for information on setting up filters library

// DO NOT CHANGE /////////////////////////////////////
#define NUM_LED 6  //sets the maximum numbers of LEDs

int reading[10];
int finalReading;
byte litLeds = 0;
byte multiplier = 1;
byte leds[] = {8, 9, 10, 11, 12, 13};
/////////////////////////////////////////////////////

#define MAX 150     //maximum posible reading. TWEAK THIS VALUE!!

// You change! Depending on how you wire your EMG sensors, your thereshold
// may be better off at a higher or lower value.
int THRESHOLD = 100;     // You define, may change to the amoung the LED's active

// You add (for state machine)
#define ledPin 2    // Example, turn on LED attatched to pin 2

void setup(){
  Serial.begin(9600); //begin serial communications
  for(int i = 0; i < NUM_LED; i++){ //initialize LEDs as outputs
    pinMode(leds[i], OUTPUT);
  }
  pinMode(ledPin, OUTPUT);
}

void loop(){
  for(int i = 0; i < 10; i++){    //take ten readings in ~0.02 seconds
    reading[i] = analogRead(A0) * multiplier;
    delay(2);
  }


  // Apply bandpass filter to reading

  int filteredReading[10];
  for (int i = 0; i < 10; i++) {
  filteredReading[i] = 0.0976 * reading[i] + 0.9054 * filteredReading[max(i-1,0)] - 0.0976 * filteredReading[max(i-2,0)];
  }
  for (int i = 0; i < 10; i++) {
    reading[i] = filteredReading[i];
  }

  //

  for(int i = 0; i < 10; i++){   //average the ten readings
    finalReading += abs(reading[i]);    // Take the absolute value of the reading.
  }
  finalReading /= 10;
  for(int j = 0; j < NUM_LED; j++){  //write all LEDs low
    digitalWrite(leds[j], LOW);
  }
  Serial.print(finalReading);
  Serial.print("\t");

  if (finalReading >= THRESHOLD){
    
    // Set StateMachine to active
    StateMachine(true);
    
  } else {

    // Set StateMachine to inactive
    StateMachine(false);
    
  }

  finalReading = constrain(finalReading, 0, MAX);       // Convert finalReading to a value between 0 and 6
  litLeds = map(finalReading, 0, MAX, 0, NUM_LED);
  Serial.println(litLeds);
  for(int k = 0; k < litLeds; k++){
    digitalWrite(leds[k], HIGH);
  }
  //for serial debugging, uncomment the next two lines.
  //Serial.println(finalReading);
  //delay(100);
}

void StateMachine(bool active){
  if (active){
    // ON STATE
    digitalWrite(ledPin, HIGH);
    Serial.print("ON");
    Serial.print("\t");
  } else {
    // INACTIVE STATE
    digitalWrite(ledPin, LOW);
    Serial.print("OFF");
    Serial.print("\t");
  }

}

// Function to apply a bandpass filter to an int array
int* applyBandpass(int* input) {
  static float coefficients[5];
  dsp::design::butterworth_bandpass(20, 500, 2, coefficients);  // 20 Hz to 500 Hz bandpass filter with 2nd order
  dsp::Filter<float> bandpass(coefficients);
  static float filteredReading[NUM_READINGS];
  for (int i = 0; i < NUM_READINGS; i++) {
    filteredReading[i] = bandpass.process(input[i]);
  }
  static int filteredIntReading[NUM_READINGS];
  for (int i = 0; i < NUM_READINGS; i++) {
    filteredIntReading[i] = (int)filteredReading[i];
  }
  return filteredIntReading;
}


