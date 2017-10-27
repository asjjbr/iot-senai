// include the library code:
#include <LiquidCrystal.h>

#define STRINGVAZIA "                "

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mensagem foi:");
  lcd.setCursor(0, 1);
}

void loop() {
  if(Serial.available()){
    lcd.setCursor(0, 1);
    lcd.print(STRINGVAZIA);
    lcd.setCursor(0, 1);
    lcd.print(Serial.readString());
  }
}

