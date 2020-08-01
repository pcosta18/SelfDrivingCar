#include <Servo.h>
#include <AFMotor.h>
#include <HCSR04.h>

#define trigger A0
#define echo A1

HCSR04 hc(trigger,echo);
Servo myservo;

AF_DCMotor motordireito1(1);
AF_DCMotor motoresquerdo1(2);
AF_DCMotor motoresquerdo2(3);
AF_DCMotor motordireito2(4);

int distancia;
float distanciaE;
float distanciaD;

void setup() {
  // começar paraado
motoresquerdo1.run(RELEASE);
motordireito1.run(RELEASE);
motordireito2.run(RELEASE);
motoresquerdo2.run(RELEASE);
// velocidade dos motores, convém não colocar a velocidade máxima para não gastar as baterias tão rapidamente
motoresquerdo1.setSpeed(180);
motordireito1.setSpeed(180);
motordireito2.setSpeed(180);
motoresquerdo2.setSpeed(180);
// servo na minha posição inicial. Pode variar de projeto para projeto
myservo.attach(10);
myservo.write(90);
delay(1000);


}

void loop() {
  // ler a distancia e andar para frente
distancia=hc.dist();
motoresquerdo1.run(FORWARD);
motordireito1.run(FORWARD);
motordireito2.run(FORWARD);
motoresquerdo2.run(FORWARD);


  // se a distancia for menor que 30, anda um bocado para tras, olha para a direita e para a esquerda , e escolhe a porxima direção
 if (distancia<30) {
  parar();
  andar_atras();
  parar();
  myservo.write(10); // olhar para a direita
  distanciaD=hc.dist();
  delay(1000);
  myservo.write(170); // olhar para a esquerda
  distanciaE=hc.dist();
  delay(1000);
  myservo.write(90); //posicao inicial
  delay(500);
  if (distanciaE>distanciaD){ // se a a distancia da esquerda for maior, vai para a esquerda
    virar_esquerda();
    distanciaD=0;
    distanciaE=0;
  }
  if (distanciaD>distanciaE){ // se a distancia da esquerda for maior, vai para a direita
    virar_direita();
    distanciaD=0;
    distanciaE=0;
  }
  
 }
}

void parar(){
  motoresquerdo1.run(RELEASE);
  motordireito1.run(RELEASE);
  motordireito2.run(RELEASE);
  motoresquerdo2.run(RELEASE);
  delay(1000);
}

void andar_atras(){
  motoresquerdo1.run(BACKWARD);
  motordireito1.run(BACKWARD);
  motordireito2.run(BACKWARD);
  motoresquerdo2.run(BACKWARD);
  delay(400);
}

void virar_esquerda(){
  motoresquerdo1.run(BACKWARD);
  motordireito1.run(FORWARD);
  motordireito2.run(FORWARD);
  motoresquerdo2.run(BACKWARD);
  delay(600);
}

void virar_direita(){
  motoresquerdo1.run(FORWARD);
  motordireito1.run(BACKWARD);
  motordireito2.run(BACKWARD);
  motoresquerdo2.run(FORWARD);
  delay(600);
}
