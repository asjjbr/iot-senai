#include <Servo.h> //Este comando inclui a biblioteca Servo neste código
Servo Servo1; //Identifica um objeto do tipo Servo chamado Servo1
int Recebido; //Variável que armazenará o valor recebido pela serial
int posicao; //Variável que armazenará as posições do servo
void setup(){
Servo1.attach(3); //Pino onde o servo deve estar colocado
Serial.begin(9600); //Inicia a comunicação serial com taxa de 9600
}
void loop(){
if (Serial.available() > 0) { //Se algo vier pela porta serial...
Recebido = Serial.read(); //O que receber, armazenar na variavel Recebido
if (Recebido == '+'){ //se receber o sinal de + pela serial faça:
posicao = posicao + 10; //adicione 10 à variável incremento
Serial.println(posicao); //mostra no Monitor Serial o valor da posição
}
if (Recebido == '-'){ //se receber o sinal de - pela serial faça:
posicao = posicao - 10; //subtraia 10 à variável incremento
Serial.println(posicao); //mostra no Monitor Serial o valor da posição
}
Servo1.write(posicao); //Escreve a posição no servo
}
}
