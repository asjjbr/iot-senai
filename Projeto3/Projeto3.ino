#define PWD "123456"

#define COLUNA1 1<<8
#define COLUNA2 1<<7
#define COLUNA3 1<<6
#define LINHA1 1<<5
#define LINHA2 1<<4
#define LINHA3 1<<3
#define LINHA4 1<<2
#define ONE (COLUNA1|LINHA1)
#define TWO (COLUNA2|LINHA1)
#define THREE (COLUNA3|LINHA1)
#define FOUR (COLUNA1|LINHA2)
#define FIVE (COLUNA2|LINHA2)
#define SIX (COLUNA3|LINHA2)
#define SEVEN (COLUNA1|LINHA3)
#define EIGHT (COLUNA2|LINHA3)
#define NINE (COLUNA3|LINHA3)
#define ZERO (COLUNA2|LINHA4)
#define STAR (COLUNA1|LINHA4)
#define HASH (COLUNA3|LINHA4)

#define KEYPAD_PINS (COLUNA1|COLUNA2|COLUNA3|LINHA1|LINHA2|LINHA3|LINHA4)

unsigned int keypad = 0;
String senha;
String tecla;

#define WAITING_STAR 0x00
#define WAITING_PWD 0x01
#define ENTERED_PWD 0x02

#define BUZZER1 9
#define BUZZER2 10
#define BUZZER_TIME 500

byte stateMachine = WAITING_STAR;
void setup() {
  Serial.begin(9600);

  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
}

void loop() {
  
  keypad = 0;
  for(int i=0; i<=13; i++){
    keypad |= digitalRead(i);
  }
  
  keypad = teclado();
  keypad &= KEYPAD_PINS;
  
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
    Serial.println(tecla);
      

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
  if (Serial.available()>0){
    char tecla = (char)Serial.read();
    switch(tecla){
      case '1':
        saida = ONE;
        break;
      case '2':
        saida = TWO;
        break;
      case '3':
        saida = THREE;
        break;
      case '4':
        saida = FOUR;
        break;
      case '5':
        saida = FIVE;
        break;
      case '6':
        saida = SIX;
        break;
      case '7':
        saida = SEVEN;
        break;
      case '8':
        saida = EIGHT;
        break;
      case '9':
        saida = NINE;
        break;
      case '0':
        saida = ZERO;
        break;
      case '*':
        saida = STAR;
        break;
      case '#':
        saida = HASH;
        break;
    }
  }
  return saida;
}

