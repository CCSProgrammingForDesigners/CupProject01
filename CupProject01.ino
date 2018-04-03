#include "config.h"


/*
  State change detection (edge detection)

  Often, you don't need to know the state of a digital input all the time, but
  you just need to know when the input changes from one state to another.
  For example, you want to know when a button goes from OFF to ON. This is called
  state change detection, or edge detection.

  This example shows how to detect when a button or button changes from off to on
  and on to off.

  The circuit:
  - pushbutton attached to pin 2 from +5V
  - 10 kilohm resistor attached to pin 2 from ground
  - LED attached from pin 13 to ground (or use the built-in LED on most
    Arduino boards)

  created  27 Sep 2005
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ButtonStateChange
*/

// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int  resetPin = 3;    // the pin that the resetbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int resetButtonState = 0;    // current state of reset button

AdafruitIO_Feed *cup = io.feed("cup");


void setup() {

   Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);


  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
 // initialize the reset pin as a input:
  pinMode(resetPin, INPUT);
   // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  resetButtonState = digitalRead(resetPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
      cup->save(buttonPushCounter);
    } else {
      
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

 

  //Reset the counter to 0
  if(resetButtonState == HIGH) {
    buttonPushCounter = 0;
    }

 
}





//////////////////////////////////////////////////////////////////////////////////



