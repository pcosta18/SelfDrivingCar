#include <Servo.h>
#include <AFMotor.h>
#include <HCSR04.h>

#define trigger A0
#define echo A1

HCSR04 hc(trigger,echo);   //HCSR04 (trig pin , echo pin)
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

// velocidade dos motores, convémnão colocar a velocidade máxima para não gastar as baterias tão rapidamente e não aquecer o arduino e evitar perdas de performance
motoresquerdo1.setSpeed(130);
motordireito1.setSpeed(130);
motordireito2.setSpeed(130);
motoresquerdo2.setSpeed(130);

// servo na minha posição inicial. Pode variar de projeto para projeto
myservo.attach(10); // 10 é o pin ao qual corresponde SER1 no motor shield
myservo.write(90); // 90º é o servo a olhar para a frente na nossa montagem
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
 while (distancia<30) {
  
  // parar e recuar um pouco
  parar();
  andar_atras();
  parar();

  // olhar para a direita e para a esquerda
  // Nota: é importante colocar um delay depois de deslocar o servo e só depois ler a distância para que quando for lida, não esteja a ser lida quando o servo está em movimento
  
  // olhar para a direita
  myservo.write(0); 
  delay(1000);
  distanciaD=hc.dist();
  
  // olhar para a esquerda
  myservo.write(180); 
  delay(1000);
  distanciaE=hc.dist();
  
  //posicao inicial
  myservo.write(90);
  delay(500);
  
  if (distanciaE>distanciaD){ // se a a distancia da esquerda for maior, vai para a esquerda)
    virar_esquerda();
    distanciaD=0;
    distanciaE=0;
    delay(100);
    }
  else { // se a distancia da esquerda for maior, vai para a direita)
    virar_direita();
    distanciaD=0;
    distanciaE=0;
    delay(100);
  }
  distancia = 400; // para sair do while
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
  delay(200);
}

void virar_esquerda(){
  motoresquerdo1.run(BACKWARD);
  motordireito1.run(FORWARD);
  motordireito2.run(FORWARD);
  motoresquerdo2.run(BACKWARD);
  delay(350);
}

void virar_direita(){
  motoresquerdo1.run(FORWARD);
  motordireito1.run(BACKWARD);
  motordireito2.run(BACKWARD);
  motoresquerdo2.run(FORWARD);
  delay(350);
}
