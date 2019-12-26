//=========================================================================================================================================================================
/*  
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  
 *####### ===========PROGRAMA DESENVOLVIDO PARA O CONTROLE DE NÍVEL DE ÁGUA ============== #######
=====>>>>> PROJETO INTERDISCIPLINAR 6 ---> CENTRO UNIVERSITÁRIO SALESIANO DE SÃO PAULO - UNISAL 
=====>>>>> PROFESSOR ---> WILSON DE FREITAS MUNIZ 
=====>>>>> GRUPO G5 ---> 
=====>>>>> ARDUINO UTILIZADO ---> ARDUINO UNO 
=====>>>>> BATERIA 12 V .DC. .9 Ah.
=====>>>>> SENSOR UTILIZADO ---> SENSOR ULTRASÔNICO.
=====>>>>> COMUTADOR UTILIZADO ---> 2 RELES.
=====>>>>> PLACA SOLAR UTILIZADA ---> .
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/
//=========================================================================================================================================================================
// INCLUSÃO DE BIBLIOTECAS

#include "Ultrasonic.h" //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO

//=========================================================================================================================================================================
//DECLARAÇÃO DE VARIÁVEIS

const int echoPin = 7; //PINO DIGITAL 7. UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 6; //PINO DIGITAL 6. UTILIZADO PELO HC-SR04 TRIG(ENVIA)
const int rele1 = 12; // PINO DIGITAL 12. UTILIZADO PARA O RELE 1. ACIONA BATERIA 
const int rele2 = 11; // PINI DIGITAL 11. UTILIZADO PARA O RELE 2. CONTROLE DOS LEDS
 
Ultrasonic ultrasonic(trigPin,echoPin); //INICIALIZANDO OS PINOS DO ARDUINO
 
float distancia; //VARIÁVEL DO TIPO INTEIRO
String result; //VARIÁVEL DO TIPO STRING

//=========================================================================================================================================================================
// FUNÇÃO DE SETUP

void setup(){
  Serial.begin(9600); //INICIALIZA A PORTA SERIAL
  pinMode(echoPin, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT); //DEFINE O PINO COMO SAIDA (ENVIA)
  pinMode(rele1, OUTPUT); // DEFINE  O PINO DO RELE1 COMO SAIDA
  pinMode (rele2,OUTPUT); // DEFINE O PINI DO RELE 2 COMO SAIDA
 
  }

//=========================================================================================================================================================================
// FUNÇÃO DE LOOP

void loop(){
  
  hcsr04(); // FAZ A CHAMADA DO MÉTODO "hcsr04()"
  Serial.print("\nDistancia: ----> "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(result); ////IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
  Serial.println(" : cm : "); //IMPRIME O TEXTO NO MONITOR SERIAL
  
  if(distancia >=8){ // SE A DISTÂNCIA FOR MAIOR QUE 8, ACIONA BOMBA
  digitalWrite(rele2, LOW); //liga bateria
  delay(5); // DELAY DE 5 MILISEGUNDOS
  digitalWrite(rele1, HIGH); //liga bomba 
  }
  else if (distancia < 3){ // SE A DISTÂNCIA FOR MENOR QUE TRÊS BOMBA DESLIGA
  digitalWrite(rele2, HIGH); // desliga bateria
  delay(5); // DELAY DE 5 MILESEGUNDOS
  digitalWrite(rele1, LOW);// liga bomba
  }
  else{ // SE NÃO LER ENTRE ESSE PADRÃO DA UM DELAY DE 400 MILISEGUNDOS
  //IMPRIME O TEXTO NO MONITOR SERIAL
  delay(5); // DELAY DE 5 MILESEGUNDOS
  }
  }
  
//=========================================================================================================================================================================

//MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
void hcsr04(){
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    distancia = (ultrasonic.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result = String(distancia); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    delay(500); //INTERVALO DE 500 MILISSEGUNDOS
 }

