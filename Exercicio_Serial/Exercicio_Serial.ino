const int yellowLed = 10; //Led amarelo está no pino 10
const int greenLed = 11; //Led verde está no pino 11
const int redLed = 12; //Led vermelho está no pino 12
const int buzzer = 9;

const int trimpotLevel = 0;
long buzzerFrequency = 1000;

const int statusLed = LED_BUILTIN; //Led para sinalizar que o programa está rodando (pino 13)
int statusLedState = LOW; //Inicializa o estado do Led de status
unsigned long previousMillisState = 0; //Variável auxiliar para registrar a ultima vez que o led de status mudou
const long intervalState = 500; //Ajuste de frequencia do led de status

//Estados da máquina de estados
const int LEDSOFF = 0x00;
const int YELLOWLEDON = 0x01;
const int GREENLEDON = 0x02;
const int REDLEDON = 0x04;
const int BUZZER = 0x08;
const int BUZZERCONTINUOS = 0x10;
const int LEDSBLINKING = 0xff;

//Variável de controle da máquina de estados
int machineState = LEDSOFF;

int ledState = LOW;// Registro de qual Led está aceso, LOW=nenhum led aceso
unsigned long previousMillis = 0;//Variável auxiliar para registrar a ultima vez que o led de status mudou
long interval = 500;//Ajuste de frequencia do led de status

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int buzzerState = LOW;
unsigned long previousMillisBuzzer = 0;

void setup() {
  Serial.begin(9600);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(statusLed, OUTPUT);
  inputString.reserve(200);
  analogReference(DEFAULT);
}

void loop() {

  unsigned long currentMillisState = millis();
  if(currentMillisState - previousMillisState >= intervalState){
    previousMillisState = currentMillisState;
    if(statusLedState)
      statusLedState = LOW;
    else
      statusLedState = HIGH;

    digitalWrite(statusLed, statusLedState);
  }

  
  unsigned long currentMillis = millis();
  unsigned long currentMillisBuzzer = millis();
      
  switch(machineState){
    case LEDSOFF:
      apagaLeds(yellowLed, greenLed, redLed);
      ledState = LOW;
      noTone(buzzer);
      break;
    case YELLOWLEDON:
      acendeApagaLed(yellowLed, greenLed, redLed);
      ledState = yellowLed;
      noTone(buzzer);
      break;
    case GREENLEDON:
      acendeApagaLed(greenLed, yellowLed, redLed);
      ledState = greenLed;
      noTone(buzzer);
      break;
    case REDLEDON:
      acendeApagaLed(redLed, yellowLed, greenLed);
      ledState = redLed;
      noTone(buzzer);
      break;
    case LEDSBLINKING:
      currentMillis = millis();
      if(currentMillis - previousMillis >= interval){
        previousMillis = currentMillis;
        if(ledState == LOW || ledState == redLed)
          ledState = yellowLed;
        else if(ledState == yellowLed)
          ledState = greenLed;
        else if(ledState == greenLed)
          ledState = redLed;
        switch(ledState){
          case LOW:
            apagaLeds(yellowLed, greenLed, redLed);
            break;
          case yellowLed:
            acendeApagaLed(yellowLed, greenLed, redLed);
            break;
          case greenLed:
            acendeApagaLed(greenLed, yellowLed, redLed);
            break;
          case redLed:
            acendeApagaLed(redLed, yellowLed, greenLed);
            break;
        }
      }
      interval = map(analogRead(trimpotLevel),0,1023,50,500);
      noTone(buzzer);
      break;
    case BUZZER:
      currentMillisBuzzer = millis();
      if(currentMillisBuzzer - previousMillisBuzzer >= 1000){
        noTone(buzzer);
        machineState = LEDSOFF;
      }
      break;
    case BUZZERCONTINUOS:
      tone(buzzer, buzzerFrequency);
      buzzerFrequency = map(analogRead(trimpotLevel),0,1023,2300,300);
      break;
  }

  if (stringComplete) {
    if(inputString.equalsIgnoreCase("y")||inputString.equalsIgnoreCase("yellow"))
      machineState = YELLOWLEDON;
    else if(inputString.equalsIgnoreCase("g")||inputString.equalsIgnoreCase("green"))
      machineState = GREENLEDON;
    else if(inputString.equalsIgnoreCase("r")||inputString.equalsIgnoreCase("red"))
      machineState = REDLEDON;
    else if(inputString.equalsIgnoreCase("b")||inputString.equalsIgnoreCase("blink"))
      machineState = LEDSBLINKING;
    else if(inputString.equalsIgnoreCase("s")||inputString.equalsIgnoreCase("stop"))
      machineState = LEDSOFF;
    else if(inputString.equalsIgnoreCase("Buzzer"))
      machineState = BUZZERCONTINUOS;
    else{
      machineState = BUZZER;
      tone(buzzer,1000);
      previousMillisBuzzer = millis();
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
  /*if (Serial.available()) {
    char texto = Serial.read();
    if(texto == 'Y' || texto == 'y')
      machineState = YELLOWLEDON;
    else if(texto == 'G' || texto == 'g')
      machineState = GREENLEDON;
    else if(texto == 'R' || texto == 'r')
      machineState = REDLEDON;
    else if(texto == 'B' || texto == 'b')
      machineState = LEDSBLINKING;
    else if(texto=='S' || texto=='s')
      machineState = LEDSOFF;
  }*/
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      Serial.println(analogRead(trimpotLevel),DEC);
      stringComplete = true;
    }
    else{// add it to the inputString:
      inputString += inChar;
    }
  }
}

void acendeApagaLed(int ledAceso, int ledApagado1, int ledApagado2){
  digitalWrite(ledAceso, HIGH);
  digitalWrite(ledApagado1, LOW);
  digitalWrite(ledApagado2, LOW);
  return;
}

void apagaLeds(int led1, int led2, int led3){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  return;
}

