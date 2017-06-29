/*
  Automaton Cocar 0.0.1 26/06/2017
*/

//#define S_INATIVO 1 //led verde
//#define S_ALARMEON 2 //led vermelho
//#define S_ALARMEOFF 3 // aguarda luz acesa para desligar após 10 minutos, led ao inves de piscar fica constante aceso vermelho pra indicar o tempo de desligamento da luz
//#define S_LUZESON 4 //led azul
//#define S_LUZESOFF 5 //apenas delisga luz e o led azul
//#define S_TURNOFF 6 //aqui faz o clean de todos, manda tudo pra low e volta para estado inativo

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

}

void loop() {
  ledVerde.Update();
  ledAmarelo.Update();
  ledVermelho.Update();
}
