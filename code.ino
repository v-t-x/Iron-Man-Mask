// C++ code
//We will make a Iron Man Helmet. This helmet will contain
// The mask will be moving with a dc motor to open and close it 
// the mask will have buttons on it in order to light up certain 
// colors like: red, ylow, blue, and white.  

#include <Servo.h>

Servo myservo;

//Varible for servo
const int servoButtonPin = 7;  //pin location
int pos = 0; //servo poition           
int servoState = LOW;      
int servoButtonState = LOW;   

//location of buttons for LED1
int led1_redPin = 11;
int led1_bluePin = 10;
int led1_greenPin = 9;

//location of buttons for LED2
int led2_redPin = 6;
int led2_bluePin = 5;
int led2_greenPin = 3;

// location of buttons for lights 
int buttonPins[] = {4, 2, 8};
int numButtons = 3;

// tur or flase states of buttons for lights 
int buttonState[3];
int lastButtonState[3];

unsigned long lastDebounceTime[3];
unsigned long debounceDelay = 50;

char currentColor = 'W';  // W = white (default)

void setup() 
{  
//servo set up
  pinMode(servoButtonPin, INPUT);   
  myservo.attach(13);
  myservo.write(0);
  
// button and RGB output / input types
// first LED RGB
  pinMode(led1_redPin, OUTPUT);
  pinMode(led1_bluePin, OUTPUT);
  pinMode(led1_greenPin, OUTPUT);
  // second LED RGB
  pinMode(led2_redPin, OUTPUT);
  pinMode(led2_bluePin, OUTPUT);
  pinMode(led2_greenPin, OUTPUT);
  
  //botton set up
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT);
    buttonState[i] = LOW;
    lastButtonState[i] = LOW;
    lastDebounceTime[i] = 0;
  }
  
  // set initial LED to white
  lightUpLed(currentColor);
  
}


void loop() {
// this chunk reads what the buttons recive 
  servoButtonState = digitalRead(servoButtonPin);

//Turn 180 degree if the servobotton is pressed
  if (servoButtonState == HIGH) {
    servoState = !servoState;
    if (servoState) {
		for (pos = 0; pos <= 180; pos++) {
         	myservo.write(pos);
          	delay(15);
        }
    }
      else {
        for (pos = 180; pos >= 0; pos--) {
           myservo.write(pos);
           delay(15);
        }
      }
  	} 
  
  //Check each botton
  for (int i = 0; i < numButtons; i++) {
    int reading = digitalRead(buttonPins[i]);

    if (reading != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
    }  
  //reading != buttonState[i]
   if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (reading != buttonState[i]) {
        buttonState[i] = reading;

        if (buttonState[i] == HIGH) {
          handleButtonPress(i);
        }
      }
    }

    lastButtonState[i] = reading;
  } 
}


void setBothLEDs(int r, int g, int b) {
  analogWrite(led1_redPin, r);
  analogWrite(led1_greenPin, g);
  analogWrite(led1_bluePin, b);

  analogWrite(led2_redPin, r);
  analogWrite(led2_greenPin, g);
  analogWrite(led2_bluePin, b);
}

void lightUpLed(char color) {
  switch (color) {
    case 'R': setBothLEDs(255, 0, 0); break;       // Red
    case 'Y': setBothLEDs(255, 255, 0); break;     // Yellow
    case 'B': setBothLEDs(0, 0, 255); break;       // Blue
    default:  setBothLEDs(255, 255, 255); break;   // White (off)
  }
}

//Handle Button Press
void handleButtonPress(int button) {
  char newColor;

  // Assign color per button
  if (button == 0) newColor = 'R'; 
  else if (button == 1) newColor = 'Y';
  else if (button == 2) newColor = 'B';

  // if pressed same color again → white
  if (currentColor == newColor) {
    currentColor = 'W';
  } 
  else {
    currentColor = newColor;
  }

  lightUpLed(currentColor);
}

