/*
<==================================================================================================================================================================>
***** Autor ---> Ramon Oliveira Borges dos Santos
***** Curso Engenharia Mecânica
* ========================================================
***** <---> Integrantes <---> 
***** Fernando Henrique Almeida de Oliveira 
***** Lincoln Oliveira Gomes 
***** Luiz Felipe Freire Honorato 
***** Ramon Oliveira Borges do Santos 
***** Pedro Henrique Colman Prado 
***** Kathleen Cristina Silveira Cunha
***** Prof: Esp. Carlos Dolberth Jaeger
***** Prof: Msc. Thiago Averaldo Bimestre
***** Prof: Dra. REGINA ELAINE SANTOS CABETTE 
***** Prof: Dr.  RENANN PEREIRA GAMA
***** Prof: Msc. WILSON DE FREITAS MUNIZ 
***** Prof: Msc. GIULLIANO ASSIS SODERO BOAVENTURA
*****  Prof: Esp. JOSELITO MOREIRA CHAGAS
*========================================================
*Orientações 
Prof: Esp. Carlos Dolberth Jaeger
Prof: Msc. Thiago Averaldo Bimestre
Prof: Dra. REGINA ELAINE SANTOS CABETTE 
Prof: Dr.  RENANN PEREIRA GAMA
Prof: Msc. WILSON DE FREITAS MUNIZ 
Prof: Msc. GIULLIANO ASSIS SODERO BOAVENTURA
Prof: Esp. JOSELITO MOREIRA CHAGAS
*========================================================
*Qualquer projeto que utilizar dessa programa deve citar os referentes autores.
*========================================================
Instituição --> Centro Universitário Salesiano de São Paulo - UNISAL
Instituição --> Faculdade de Roseira - FARO
*========================================================
*Módulo Utilizado 
*Módulo UsinaInfo
*Site: https://www.usinainfo.com.br/dimmer-arduino/modulo-dimmer-para-arduino-pic-mc-8a-com-sinal-zero-cross-2799.html
*Sensor de Temperatura Utilizado: Lm35
*========================================================
*
--- DESENVOLVIMENTO DE UM CONTROLE DISCRETO PID DE TEMPERATURA PARA UMA CARGA RESISTIVA UTILIZANDO MÓDULO DIMMER E MICROCONTROLADOR ARDUINO ---

*/

//<===================================================================================================================================>
//INCLUSÃO DE BIBLIOTECAS
#define PINO_ZC 2
#define PINO_DIM 9

//<===================================================================================================================================>
//DECLARAÇÃO DE VARIAVEIS GLOBAIS
volatile long luminosidade = 0;  // 0 a 100 
float temperatura;//variável recebe temperatura

float p,i,d;//VARIÁVEIS DO CÁLCULO DO PID
float sp = 40.0; //variável set point
float pid; //variável pid pv variável de processo
float er, ei, ea;//calcula a variação entre a temperatura medida e a temperatura alvo. Faz parte da realimentação do sistema e no cálculo de cada controlador.; //erro integral e anterior

float kp = 1.3; //cte do kp
float ki = 0.07; //cte do ki
float kd = 0.05; // cte kd

//<===================================================================================================================================>
//FUNÇÃO DO PROGRAMA
//Essa função será respponsável pelo controle da luminosidade da lâmpada
void zeroCross()  {
  if (luminosidade>85) luminosidade=85;
  if (luminosidade<2) luminosidade=2;
  long t1 = 8200L * (100L - luminosidade) / 100L;      
  delayMicroseconds(t1);   
  digitalWrite(PINO_DIM, HIGH);  
  delayMicroseconds(6);      // t2
  digitalWrite(PINO_DIM, LOW);   
}

//<===================================================================================================================================>
//FUNÇÃO DE SETUP
void setup() {
  Serial.begin(9600);//Comunicação Serial 9600
  pinMode(PINO_DIM, OUTPUT);//Pino 9 do arduino configurado como saida 
  attachInterrupt(0, zeroCross, RISING);//Interrupção a cada pasagem por zero
}

//<===================================================================================================================================>
//FUNÇÃO DE LOOP
void loop() {
  temperatura = analogRead(A2)/2.46;//CALCULANDO A TEMPERATURA DO LM35
  er = sp - temperatura; //calcula a variação entre a temperatura medida e a temperatura alvo. Faz parte da realimentação do sistema e no cálculo de cada controlador.
  
  //controle proporcional
  p = kp*er;
  
  //controle integral
  ei = ei + er; //ERRO INTEGRAL
  i = ki * ei;//controle integral
  
  //controle derivativo
  ea = er; //Erro Anterior
  d = kd*(er - ea);//Controle derivativo
 
  //PID
  pid = p+i+d; //CONTROLE PID

  luminosidade = pid;//ATUAÇÃO DO PID
  
  // DADOS DO MONITOR SERIAL
  Serial.print("Setpoint:"); Serial.print(sp);
  Serial.print(" Temperatura:"); Serial.print(temperatura);
  Serial.print(" pid:"); Serial.println(pid);

  // DADOS DO PLOTER SERIAL
  Serial.print(sp);
  Serial.print(" ");
  Serial.println(temperatura);
 
}





