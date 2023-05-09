// Setup Servo
#include <filters.h> // See README for information on setting up filters library
#include <Servo.h>

// Servo Setup //////////////////////////////////////
Servo myservo;         // create servo object to control a servo
#define SERVO_PIN 2    // pin for servo motor
int pos = 8;           // Default start pos
int maxpos = 50;       // Maximum position
bool state = false;    // State of the machine

// DO NOT CHANGE /////////////////////////////////////
#define NUM_LED 6  //sets the maximum numbers of LEDs

int reading[10];    // EMG window
int finalReading;   // Final Average EMG reading
byte litLeds = 0;                      
byte multiplier = 1;

int READ_DELAY = 2; // Delay between readings
/////////////////////////////////////////////////////

#define MAX 150     //maximum posible EMG reading. TWEAK THIS VALUE!!

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
  for(int i = 0; i < 10; i++){    //take ten data points in ~0.02 seconds
    reading[i] = analogRead(A0) * multiplier;   // 1 ms
    delay(READ_DELAY);                          // 2 ms
  }
  
  // Average the readings into final reading

  for(int i = 0; i < 10; i++){   //average the ten readings
    finalReading += abs(reading[i]);
  }
  finalReading /= 10;

  // TURN EVERY LED OFF
  for(int j = 0; j < NUM_LED; j++){  //write all LEDs low
    digitalWrite(leds[j], LOW);
  }

  // Print finalReading to Serial Monitor
  Serial.print(finalReading);
  Serial.print("\t");

  if (finalReading >= THRESHOLD){
    
    // Set StateMachine to active
    StateMachine(true);
    
  } else {

    // Set StateMachine to inactive
    StateMachine(false);
    
  }

  finalReading = constrain(finalReading, 0, MAX);       // Convert finalReading to a value between 0 and MAX VALUE
  litLeds = map(finalReading, 0, MAX, 0, NUM_LED);      // Figure out how many LEDs to turn on based on final Reading
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

/// Do stepper on action

    // digitalWrite(ledPin, HIGH);
    Serial.print("ON");
    Serial.print("\t");

  } else if ((active==false) && (state == true)){
    // INACTIVE 
    myservo.write(8);
    state = false;

/// Do stepper off action

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