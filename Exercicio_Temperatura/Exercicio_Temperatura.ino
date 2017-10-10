const int statusLed = LED_BUILTIN; //Led para sinalizar que o programa está rodando (pino 13)
int statusLedState = LOW; //Inicializa o estado do Led de status
unsigned long previousMillisState = 0; //Variável auxiliar para registrar a ultima vez que o led de status mudou
const long intervalState = 500; //Ajuste de frequencia do led de status

const long pwmRampDuration = 10000;
unsigned long previousMillisPWM = 0;
int level = 0;

const int brightLed = 3;
const int trimpot = A0;
const int redColor = 10;
const int greenColor = 9;
const int blueColor = 8;
const int tempSensor = A1;
const int buzzer = 11;
const int button = 12;
const int ldr = A2;

//Estados da máquina de estados
const int LEDSOFF = 0x00;
const int REDLEDON = 0x01;
const int GREENLEDON = 0x02;
const int BLUELEDON = 0x04;
const int ALLLEDS = 0x08;
const int BUZZER = 0x10;
const int LDRHIGH = 0x11;
const int LDRLOW = 0x12;
const int LEDSBLINKING = 0xff;

//Variável de controle da máquina de estados
int machineState = LEDSOFF;

int ledState = LOW;// Registro de qual Led está aceso, LOW=nenhum led aceso
unsigned long previousMillis = 0;//Variável auxiliar para registrar a ultima vez que o led de status mudou
long interval = 500;//Ajuste de frequencia do led de status

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

const int maxTemperature = 22;
int buttonPreviousState = LOW;


float a = 1.0;
float b = 2.35;
float c = 3.33;

void setup() {
  Serial.begin(9600);
  pinMode(statusLed, OUTPUT);
  pinMode(brightLed, OUTPUT);
  pinMode(redColor, OUTPUT);
  pinMode(greenColor, OUTPUT);
  pinMode(blueColor, OUTPUT);
  inputString.reserve(200);
  analogReference(DEFAULT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {

  //Código para piscar led de status
  unsigned long currentMillisState = millis();
  if(currentMillisState - previousMillisState >= intervalState){
    previousMillisState = currentMillisState;
    if(statusLedState)
      statusLedState = LOW;
    else
      statusLedState = HIGH;

    digitalWrite(statusLed, statusLedState);
  }

  int trimpotLevel = analogRead(trimpot);
  //analogWrite(brightLed, map(trimpotLevel,0,1023,0,255));
  
  float temperatura = analogRead(tempSensor)*0.4887585532;
  unsigned long currentMillis = millis();
  switch(machineState){
    case LEDSOFF:
      apagaLeds(redColor, greenColor, blueColor);
      ledState = LOW;
      noTone(buzzer);
      break;
    case REDLEDON:
      acendeApagaLed(redColor, greenColor, blueColor);
      ledState = redColor;
      noTone(buzzer);
      break;
    case GREENLEDON:
      acendeApagaLed(greenColor, redColor, blueColor);
      ledState = greenColor;
      noTone(buzzer);
      break;
    case BLUELEDON:
      acendeApagaLed(blueColor, redColor, greenColor);
      ledState = blueColor;
      noTone(buzzer);
      break;
    case LEDSBLINKING:
      currentMillis = millis();
      if(currentMillis - previousMillis >= interval){
        previousMillis = currentMillis;
        if(ledState == LOW || ledState == blueColor)
          ledState = redColor;
        else if(ledState == redColor)
          ledState = greenColor;
        else if(ledState == greenColor)
          ledState = blueColor;
        switch(ledState){
          case LOW:
            apagaLeds(redColor, greenColor, blueColor);
            break;
          case redColor:
            acendeApagaLed(redColor, greenColor, blueColor);
            break;
          case greenColor:
            acendeApagaLed(greenColor, redColor, blueColor);
            break;
          case blueColor:
            acendeApagaLed(blueColor, redColor, greenColor);
            break;
          case 0xff:
            apagaLeds(redColor, greenColor, blueColor);
            ledState = LOW;
            break;
        }
      }
      noTone(buzzer);
      break;
    case ALLLEDS:
      acendeLeds(redColor, greenColor, blueColor);
      ledState = 0xff;
      break;
    case BUZZER:
      tone(buzzer, map(trimpotLevel,0,1023,300,2300));
      break;
    case LDRHIGH:
      analogWrite(brightLed, level);
      level = rampaPWM(level,0);
      if(analogRead(ldr)*0.0977517106549365<60){
        machineState = LDRLOW;
        previousMillisPWM = millis();
      }
      noTone(buzzer);
      break;
    case LDRLOW:
      analogWrite(brightLed, level);
      level = rampaPWM(level,1);
      if(analogRead(ldr)*0.0977517106549365>70){
        machineState = LDRHIGH;
        previousMillisPWM = millis();
      }
      noTone(buzzer);
      break;
  }

  if (stringComplete) {
    if(inputString.equalsIgnoreCase("b")||inputString.equalsIgnoreCase("blue"))
      machineState = BLUELEDON;
    else if(inputString.equalsIgnoreCase("g")||inputString.equalsIgnoreCase("green"))
      machineState = GREENLEDON;
    else if(inputString.equalsIgnoreCase("r")||inputString.equalsIgnoreCase("red"))
      machineState = REDLEDON;
    else if(inputString.equalsIgnoreCase("p")||inputString.equalsIgnoreCase("blink"))
      machineState = LEDSBLINKING;
    else if(inputString.equalsIgnoreCase("s")||inputString.equalsIgnoreCase("stop"))
      machineState = LEDSOFF;
    else if(inputString.equalsIgnoreCase("all"))
      machineState = ALLLEDS;
    else if(inputString.equalsIgnoreCase("temp")){
      Serial.print("Temperatura = ");
      Serial.print(temperatura);
      Serial.println("ºC");
    }
    else if(inputString.equalsIgnoreCase("buzzer")){
      machineState = BUZZER;
    }
    else if(inputString.equalsIgnoreCase("ldr")){
      machineState = LDRHIGH;
      Serial.print("LDR = ");
      Serial.print(analogRead(ldr)*0.0977517106549365);
      Serial.println("%");
    }
    else{
      
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  int buttonActualState = digitalRead(button);

  if(buttonActualState && !buttonPreviousState){
    switch(machineState){
      case LEDSOFF:
        machineState = REDLEDON;
        break;
      case REDLEDON:
        machineState = GREENLEDON;
        break;
      case GREENLEDON:
        machineState = BLUELEDON;
        break;
      case BLUELEDON:
        machineState = ALLLEDS;
        break;
      case ALLLEDS:
        machineState = BUZZER;
        break;
      case BUZZER:
        machineState = LEDSBLINKING;
        break;
      case LEDSBLINKING:
        machineState = LEDSOFF;
        break;
    }
  }
  buttonPreviousState = buttonActualState;
  if(buttonActualState)
    Serial.println("botão pressionado");
  
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      Serial.println(inputString);
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

void acendeLeds(int led1, int led2, int led3){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  return;
}

int rampaPWM(int valorAnterior, int crescente){
  unsigned long time = millis();
  if(time - previousMillisPWM >= pwmRampDuration/255){
    previousMillisPWM = time;
    if (crescente)
      valorAnterior++;
    else
      valorAnterior--;
  }
  if(valorAnterior>255)
    valorAnterior = 255;
  if(valorAnterior<0)
    valorAnterior = 0;

  return valorAnterior;
}

