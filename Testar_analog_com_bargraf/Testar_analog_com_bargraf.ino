#define ANALOGCONVERSION 0.1075268817204301;//no Leonardo usar 0.4887585532
//#define ANALOGCONVERSION 0.4887585532;

const int LM35 = 0; //Sensor de temperatura está no pino analógico 0
float temperature = 0;
int ADClido = 0;

//const int Buzzer = 12; //Buzina está no pino digital 12
const int BARGRAF[] = {2,3,4,5,6,7,8,9,10,11}; //Bargraf está nos pinos digitais de 2 a 11

const int ledPin = LED_BUILTIN;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;

const int button = 12;
const int redLed = 11;
const int greenLed = 10;
int redLedState = LOW;
int greenLedState = LOW;
int previousButtonState = LOW;
int actualButtonState = LOW;


void setup() {
  analogReference(DEFAULT);
  //pinMode(Buzzer, OUTPUT);
  for(int i = 0; i < 10; i++)
    pinMode(BARGRAF[i], OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  pinMode(button, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
}

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    if(ledState)
      ledState = LOW;
    else
      ledState = HIGH;

    digitalWrite(ledPin, ledState);
  }

  actualButtonState = digitalRead(button);
  if(actualButtonState && !previousButtonState){
    Serial.println(1000);
    if(!redLedState){
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);
      redLedState = HIGH;
      greenLedState = LOW;
    }
    else{
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
      redLedState = LOW;
      greenLedState = HIGH;
    }
  }
  else
    Serial.println(10000);
  previousButtonState = actualButtonState;

  
  ADClido = analogRead(LM35);
  temperature = ADClido*0.0977517106549365;

  float temperatureSetPoint = 9.9;
  if(temperature > temperatureSetPoint){
    digitalWrite(BARGRAF[0], HIGH);
  }
  else{
    digitalWrite(BARGRAF[0], LOW);
  }

  temperatureSetPoint += 10.0;

  if(temperature > temperatureSetPoint){
    digitalWrite(BARGRAF[1], HIGH);
  }
  else{
    digitalWrite(BARGRAF[1], LOW);
  }

  temperatureSetPoint += 10.0;

  if(temperature > temperatureSetPoint){
    digitalWrite(BARGRAF[2], HIGH);
  }
  else{
    digitalWrite(BARGRAF[2], LOW);
  }

  temperatureSetPoint += 10.0;

  if(temperature > temperatureSetPoint){
    digitalWrite(BARGRAF[3], HIGH);
  }
  else{
    digitalWrite(BARGRAF[3], LOW);
  }

  temperatureSetPoint += 10.0;

  if(temperature > temperatureSetPoint){
    digitalWrite(BARGRAF[4], HIGH);
  }
  else{
    digitalWrite(BARGRAF[4], LOW);
  }

  temperatureSetPoint += 10.0;

  if(temperature > temperatureSetPoint){
    digitalWrite(BARGRAF[5], HIGH);
  }
  else{
    digitalWrite(BARGRAF[5], LOW);
  }

  temperatureSetPoint += 10.0;

  if(temperature > temperatureSetPoint){
    digitalWrite(BARGRAF[6], HIGH);
  }
  else{
    digitalWrite(BARGRAF[6], LOW);
  }

  temperatureSetPoint += 10.0;

  if(temperature > temperatureSetPoint){
    digitalWrite(BARGRAF[7], HIGH);
  }
  else{
    digitalWrite(BARGRAF[7], LOW);
  }

  temperatureSetPoint += 10.0;

  /*if(temperature > temperatureSetPoint){
    digitalWrite(BARGRAF[8], HIGH);
  }
  else{
    digitalWrite(BARGRAF[8], LOW);
  }

  temperatureSetPoint += 10.0;

  if(temperature > temperatureSetPoint){
    digitalWrite(BARGRAF[9], HIGH);
    //tone(Buzzer, 500);
  }
  else{
    digitalWrite(BARGRAF[9], LOW);
    //noTone(Buzzer);
  }*/
  //Serial.println(temperature);

}
