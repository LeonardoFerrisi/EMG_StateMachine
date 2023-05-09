# Making State Machines with the Backyard Brains Spiker Shield!

## What you'll need:
* Arduino Uno
* [Backyard Brains Spiker Shield](https://backyardbrains.com/products/muscleSpikershieldBundle)
* Limb with working muscles
* Assorted Arduino Accessories to make state machines
    * [*Recomendation*](https://www.amazon.com/ELEGOO-Project-Tutorial-Controller-Projects/dp/B01D8KOZF4/ref=sr_1_1_sspa?keywords=arduino+kit&qid=1681852351&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExTVZFNTU0VE84MlU4JmVuY3J5cHRlZElkPUEwMzkzMzg0NlhOTTM2OElJU1MzJmVuY3J5cHRlZEFkSWQ9QTEwMDEzNzYzVFNPV0pHQ01HTlNCJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==) 
* 2 **9V batteries**
* 2 **9V battery connectors**
* 1 **Arduino Servo Motor** 
* 1 3D Printed Claw to attatch to servo motor (https://www.thingiverse.com/thing:4811915)

# Using Filters library
Copy the `libFilter` located in `EMG_StateMachine\libraries\libFilter` folder into your **Arduino** `libraries` folder. Typically this is located in `Documents\Arduino\libraries`.

# Using Servo Library

## Installing Pre-requisites

### Arduino IDE
Download the latest version of the Arduino IDE from [here](https://www.arduino.cc/en/Main/Software).

## **Default Setup:**

### Setting up EMG_StateMachine
0. Make sure the the `filters` library is installed. See [Using Filters library](#using-filters-library).
1. Open `EMG_StateMachine.ino` in the Arduino IDE.
2. Make sure to select the correct board. Go to `Tools > Board` and select the board you are using. For example, if you are using the Arduino Uno, select `Arduino/Genuino Uno`.
3. Make sure to select the correct port. Go to `Tools > Port` and select the port that the board is connected to. On Windows, typically the port will be `COM1`, `COM2`, etc. On Mac, the port will be `/dev/cu.usbmodem`, etc. 
4. Click the `Upload` button to compile and upload the code onto the board.

### Wiring the arduino to the EMG
1. Place the SpikerShield onto the arduino such that it alights and each pin enters a slot on the arduino base.
2. Plug a **Servo Motor** into the top pins of the SpikerShield. (Note that the connector for the servo motor is specifically connected to the **D2** pin on the arduino)

### Setting up a 3D printable claw to the Servo
1. Please visit 

## Creating LED EMG - Controlled State Machine

- *Under Construction*

## Creating your own state machine

- *Under Construction*
* Try out some of the examples from **ArduinoExamples**

## Combining state machines!