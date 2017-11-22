#include <AsyncDelay.h>

#define PWD "123456"

#define COLUNA1 8
#define COLUNA2 7
#define COLUNA3 6
#define LINHA1 5
#define LINHA2 4
#define LINHA3 3
#define LINHA4 2

AsyncDelay delayDebounce;

unsigned int keypad = 0;
unsigned int keypadOld = 0;
String senha;
String tecla = "x";

#define WAITING_STAR 0x00
#define WAITING_PWD 0x01
#define ENTERED_PWD 0x02

#define BUZZER1 9
#define BUZZER2 10
#define BUZZER_TIME 100
#define DEBOUNCE_TIME 50

#define ONE (1<<1)
#define TWO (1<<2)
#define THREE (1<<3)
#define FOUR (1<<4)
#define FIVE (1<<5)
#define SIX (1<<6)
#define SEVEN (1<<7)
#define EIGHT (1<<8)
#define NINE (1<<9)
#define ZERO (1<<0)
#define STAR (1<<10)
#define HASH (1<<11)

byte stateMachine = WAITING_STAR;
void setup() {
  Serial.begin(9600);

  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
  
  pinMode(COLUNA1,INPUT_PULLUP);
  pinMode(COLUNA2,INPUT_PULLUP);
  pinMode(COLUNA3,INPUT_PULLUP);
  pinMode(LINHA1,OUTPUT);
  pinMode(LINHA2,OUTPUT);
  pinMode(LINHA3,OUTPUT);
  pinMode(LINHA4,OUTPUT);

  delayDebounce.start(DEBOUNCE_TIME, AsyncDelay::MILLIS);
}


void loop() {

  if(delayDebounce.isExpired())
    keypad = teclado();
  else
    keypad = keypadOld;
    
  if(keypad != keypadOld){
    keypadOld = keypad;
    delayDebounce.expire();
    delayDebounce.repeat();
  }
  else{
    keypad = 0;
  }

//  for(int i=0; i<12; i++){
//    unsigned int aux = 0;
//    aux = (keypad>>i)&0x01;
//    if(aux){
//      if(i<10)
//        Serial.println(i);
//      else{
//        if(i==10)
//          Serial.println("*");
//        if(i==11)
//          Serial.println("#");
//      }
//    }
//  }
  
  switch(keypad){
    case ONE:
      tecla = F("1");
      tone(BUZZER1, 697, BUZZER_TIME);
      tone(BUZZER2, 1209, BUZZER_TIME);
      break;
    case TWO:
      tecla = F("2");
      tone(BUZZER1, 697, BUZZER_TIME);
      tone(BUZZER2, 1336, BUZZER_TIME);
      break;
    case THREE:
      tecla = F("3");
      tone(BUZZER1, 697, BUZZER_TIME);
      tone(BUZZER2, 1477, BUZZER_TIME);
      break;
    case FOUR:
      tecla = F("4");
      tone(BUZZER1, 770, BUZZER_TIME);
      tone(BUZZER2, 1209, BUZZER_TIME);
      break;
    case FIVE:
      tecla = F("5");
      tone(BUZZER1, 770, BUZZER_TIME);
      tone(BUZZER2, 1336, BUZZER_TIME);
      break;
    case SIX:
      tecla = F("6");
      tone(BUZZER1, 770, BUZZER_TIME);
      tone(BUZZER2, 1477, BUZZER_TIME);
      break;
    case SEVEN:
      tecla = F("7");
      tone(BUZZER1, 852, BUZZER_TIME);
      tone(BUZZER2, 1209, BUZZER_TIME);
      break;
    case EIGHT:
      tecla = F("8");
      tone(BUZZER1, 852, BUZZER_TIME);
      tone(BUZZER2, 1336, BUZZER_TIME);
      break;
    case NINE:
      tecla = F("9");
      tone(BUZZER1, 852, BUZZER_TIME);
      tone(BUZZER2, 1477, BUZZER_TIME);
      break;
    case ZERO:
      tecla = F("0");
      tone(BUZZER1, 941, BUZZER_TIME);
      tone(BUZZER2, 1336, BUZZER_TIME);
      break;
    case STAR:
      tecla = F("*");
      tone(BUZZER1, 941, BUZZER_TIME);
      tone(BUZZER2, 1209, BUZZER_TIME);
      break;
    case HASH:
      tecla = F("#");
      tone(BUZZER1, 941, BUZZER_TIME);
      tone(BUZZER2, 1477, BUZZER_TIME);
      break;
    default:
      tecla = F("x");
      break;
  }
  if(tecla != F("x"))
    Serial.print(tecla);
  if(tecla == F("#"))
    Serial.println("");
      

  switch(stateMachine){
    case WAITING_STAR:
      if(tecla == F("*")){
        stateMachine = WAITING_PWD;
        senha = "";
      }
      break;
    case WAITING_PWD:
      if(tecla == F("*")){
        senha = "";
        stateMachine = WAITING_STAR;
      }
      else{
        if(tecla == F("#")){
          stateMachine = ENTERED_PWD;
        }
        else{
          if(tecla != F("x")){
            senha += tecla;
          }
        }
      }
      break;
    case ENTERED_PWD:
      if(senha == F(PWD)){
        Serial.println("Senha correta");
        Serial.println(senha);
      }
      else{
        Serial.println("Senha incorreta");
        Serial.println(senha);
      }
      senha = "";
      stateMachine = WAITING_STAR;
      break;
  }
}



unsigned int teclado(){
  unsigned int saida = 0;
  digitalWrite(LINHA1,LOW);
  digitalWrite(LINHA2,HIGH);
  digitalWrite(LINHA3,HIGH);
  digitalWrite(LINHA4,HIGH);
  saida |= (!digitalRead(COLUNA1)<<1)|(!digitalRead(COLUNA2)<<2)|(!digitalRead(COLUNA3)<<3);
  
  digitalWrite(LINHA1,HIGH);
  digitalWrite(LINHA2,LOW);
  digitalWrite(LINHA3,HIGH);
  digitalWrite(LINHA4,HIGH);
  saida |= (!digitalRead(COLUNA1)<<4)|(!digitalRead(COLUNA2)<<5)|(!digitalRead(COLUNA3)<<6);

  digitalWrite(LINHA1,HIGH);
  digitalWrite(LINHA2,HIGH);
  digitalWrite(LINHA3,LOW);
  digitalWrite(LINHA4,HIGH);
  saida |= (!digitalRead(COLUNA1)<<7)|(!digitalRead(COLUNA2)<<8)|(!digitalRead(COLUNA3)<<9);

  digitalWrite(LINHA1,HIGH);
  digitalWrite(LINHA2,HIGH);
  digitalWrite(LINHA3,HIGH);
  digitalWrite(LINHA4,LOW);
  saida |= (!digitalRead(COLUNA1)<<10)|(!digitalRead(COLUNA2)<<0)|(!digitalRead(COLUNA3)<<11);

  return saida;
}

