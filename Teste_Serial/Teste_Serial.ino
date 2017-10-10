const int ledPin = LED_BUILTIN;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
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
  
  if (Serial.available()) {
    int texto = Serial.read();
    Serial.println("teste");
    Serial.print("teste2\n");
  }
}
