/*
  Automaton Cocar 0.0.1 26/06/2017
*/
#include <Servo.h>
Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int buttonPin = 9;
int buttonState = 0;         // variable for reading the pushbutton status

class Flasher
{
    // Class Member Variables
    // These are initialized at startup
    int ledPin;      // the number of the LED pin
    long OnTime;     // milliseconds of on-time
    long OffTime;    // milliseconds of off-time

    // These maintain the current state
    int ledState;                 // ledState used to set the LED
    unsigned long previousMillis;   // will store last time LED was updated

    // Constructor - creates a Flasher
    // and initializes the member variables and state
  public:
    Flasher(int pin, long on, long off)
    {
      ledPin = pin;
      pinMode(ledPin, OUTPUT);

      OnTime = on;
      OffTime = off;

      ledState = LOW;
      previousMillis = 0;
    }

    void Update()
    {
      // check to see if it's time to change the state of the LED
      unsigned long currentMillis = millis();

      if ((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
      {
        ledState = LOW;  // Turn it off
        previousMillis = currentMillis;  // Remember the time
        digitalWrite(ledPin, ledState);  // Update the actual LED
      }
      else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
      {
        ledState = HIGH;  // turn it on
        previousMillis = currentMillis;   // Remember the time
        digitalWrite(ledPin, ledState);   // Update the actual LED
      }
    }
    void High()
    {
      digitalWrite(ledPin, HIGH);
    }
    void Clean()
    {
      digitalWrite(ledPin, LOW);
    }
};

Flasher ledVerde(2, 550, 400); //led azul
Flasher ledAmarelo(3, 800, 700); //led verde
Flasher ledVermelho(4, 300, 200); //led vermelho

void setup() {
  Serial.begin(9600);          //  setup serial
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  buttonState = digitalRead(buttonPin);
//  button = digitalRead(9);    // read the input pin
//  Serial.println(button);             // debug value
//  delay(1500);
  ledVerde.Update();
  ledAmarelo.Update();
  ledVermelho.Update();
  if (buttonState == LOW) {
    // turn LED on:
    myservo.write(90);
  } else {
    // turn LED off:
    val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
    val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
    myservo.write(val);                  // sets the servo position according to the scaled value
  }
  delay(15);                           // waits for the servo to get there
}
