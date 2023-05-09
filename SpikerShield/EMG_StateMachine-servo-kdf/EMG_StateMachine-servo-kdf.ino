// Setup Servo
//#include <filters.h> // See README for information on setting up filters library -- doesn't currently work; allows bandpass filter or lowpass filter, seems to work fine without this using absolute value currently
#include <Servo.h>

// Servo Setup //////////////////////////////////////
Servo myservo;  // create servo object to control a servo; based on assigned pins in servo.h.
#define SERVO_PIN 2                            //pin for servo motor; defines the pin of the servo that you will talk to
int pos = 8; // Default start position for claw so always starts at closed position. 

// DO NOT CHANGE /////////////////////////////////////
#define NUM_LED 6  //sets the maximum numbers of LEDs

int reading[10];
int finalReading;
byte litLeds = 0;
byte multiplier = 1;
byte leds[] = {8, 9, 10, 11, 12, 13};

bool state = false;
/////////////////////////////////////////////////////

#define MAX 150     //maximum posible reading. TWEAK THIS VALUE!!

// You change! Depending on how you wire your EMG sensors, your thereshold
// may be better off at a higher or lower value.
int THRESHOLD = 150;     // You define, may change to the amoung the LED's active

// You add (for state machine)
#define ledPin 2    // Example, turn on LED attatched to pin 2

void setup(){

  myservo.attach(SERVO_PIN);
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
  for(int i = 0; i < 10; i++){   //average the ten readings
    finalReading += abs(reading[i]);
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
  if (active && (state == false)){
    // ON STATE

    myservo.write(50);
    state = true;
    // digitalWrite(ledPin, HIGH);
    Serial.print("ON");
    Serial.print("\t");
  } else if ((active==false) && (state == true)){
    // INACTIVE 
    myservo.write(8);
    state = false;
    // digitalWrite(ledPin, LOW);
    Serial.print("OFF");
    Serial.print("\t");
  }

  else {
    if (state == true){
      Serial.print("ON");
      Serial.print("\t");
    }
    else{
      Serial.print("OFF");
    Serial.print("\t");
    }
  }

}
