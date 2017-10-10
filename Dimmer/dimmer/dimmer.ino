const int ledPin = LED_BUILTIN;
int ledState = LOW;
unsigned long previousMillisState = 0;
const long intervalState = 500;

const int redLed = 3;
const int trimpot = A0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  analogReference(DEFAULT);
}

void loop() {
  unsigned long currentMillisState = millis();
  if(currentMillisState - previousMillisState >= intervalState){
    previousMillisState = currentMillisState;
    if(ledState)
      ledState = LOW;
    else
      ledState = HIGH;

    digitalWrite(ledPin, ledState);
  }

  int level = analogRead(trimpot);
  level = map(level,0,1023,0,255);
  analogWrite(redLed, level);
  
}
