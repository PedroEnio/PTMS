// 
/*CANAL L GUSTAVO - ROBOTICA E PROGRAMAÇÃO
 * PROJETO: Monitorando Energia Eletrica com potência ativa
 * Projetos Arduino
 * PROF. ENG. LUIZ GUSTAVO
 * 
*/

#include "EmonLib.h"
 
EnergyMonitor SCT013;
 
int pinSCT = A1;   //Pino analógico conectado ao SCT-013
int pinTrafo = A0;


unsigned long tempo_corr;
unsigned long tempo_ddp;
unsigned long defasagem;
unsigned long defasagem_medida;

unsigned long tempo_energia_eletrica_inicio;
unsigned long tempo_energia_eletrica_fim;
unsigned long tempo_total_energia_eletrica;

float Energia_eletrica_consumida;
float Energia_eletrica_consumida_acumulada;
float Energia_eletrica_relogio;

float angulo;
int Valor_analogico_Lido;
int valor_analogico_ddp;
int valor_analogico_ddp_maior;
int tensao_eficaz;

int contagem = 0;
float fator_de_potencia;
int Potencia_ativa_instantanea;
int Potencia_ativa_media;

void setup() {
  
  SCT013.current(pinSCT, 6.0606);
  Serial.begin(9600);
  tempo_energia_eletrica_inicio = millis();
}

// the loop routine runs over and over again forever:
void loop() {


 // Calculando fator de potência 
 
   Valor_analogico_Lido = analogRead(pinTrafo);
  
  if(Valor_analogico_Lido>510 && Valor_analogico_Lido<514) {
  tempo_ddp = micros();
  
   Valor_analogico_Lido = analogRead(pinSCT);// 112 us (leiura
    
  while(Valor_analogico_Lido<500 || Valor_analogico_Lido>520){
   Valor_analogico_Lido = analogRead(pinSCT);   
   }
  
  tempo_corr = micros(); 
  
  defasagem_medida = tempo_corr - tempo_ddp-224; // 224us : Deve ser utilizado para compensar as leituras da linha 54 e a ultima leitura do while na linha 57.
                                                 // o atmega328(microcontrolador) demora 112 us para realizar uma leitura analogica 

  // Elimina ruidos, e leituras indesejadas (tanto para mais quanto para menos)
  if(defasagem_medida<=3000 && defasagem_medida >224 ) {
    defasagem= defasagem_medida;
  }
  
  Serial.print("defasagem:");
  Serial.println(defasagem);

  angulo = map(defasagem,0,4166,0,90); // O periodo da onda da rede vale 16,6 ms(1/60----f = 60Hz) entao apos este tempo a onda avanca 360º.
                                       // Como a defasagem foi calculada em micro segundos(  micros() ) na linha 52 e 60, usamos 4166us = 4,16ms.
                                       // Logo, se 16,6ms vale 360º, 90º vale 4,16ms (4166 us)   
  
  Serial.print("angulo:");
  Serial.println(angulo);

  fator_de_potencia = cos(3.14*(angulo/180)); // transforma o angulo em radiano.  
  Serial.print("fator_de_potencia:");
  Serial.println(fator_de_potencia);
 
  

// Calcular tensão eficaz
  
  //calcular valor de pico ddp
   valor_analogico_ddp_maior = analogRead(A0);
   for(int i=0;i<1000;i++){
   valor_analogico_ddp = analogRead(A0);

    if(valor_analogico_ddp>valor_analogico_ddp_maior){
      valor_analogico_ddp_maior = valor_analogico_ddp;  
    }
     
   }

    Serial.print("maior valor analogico:");
    Serial.println(valor_analogico_ddp_maior);
    
    // Para valor analogigo 1008 a tensão eficaz foi 208 V (valores encontrado no monitor serial(1008) e no multimetro(208V) )
    // Logo, podemos criar um fator de multiplicação: 208/1008 = 0.2063
    // Para encontrar a tensão eficaz basta o multiplicar o valor_analogico_ddp_maior por 0.2063
    
    tensao_eficaz = valor_analogico_ddp_maior*0.2063; 
    
    Serial.print("tensao_eficaz:");
    Serial.println(tensao_eficaz);

// Calcular corrente eficaz

double corrente_eficaz = SCT013.calcIrms(1480);   // Calcula o valor da Corrente
    
    Serial.print("corrente_eficaz:");
    Serial.println(corrente_eficaz);


// Calcular potência ativa media

Potencia_ativa_instantanea = tensao_eficaz*corrente_eficaz*fator_de_potencia;

if(Potencia_ativa_instantanea>0){
  if(Potencia_ativa_media==0){
    Potencia_ativa_media = Potencia_ativa_instantanea;
  }
  Potencia_ativa_media = (Potencia_ativa_instantanea+Potencia_ativa_media)/2;
}


    Serial.print("Potencia_ativa_media:");
    Serial.println(Potencia_ativa_media);

// Contador do tamanho da amostra para calculo da potencia ativa media
      
      contagem = contagem +1;
      Serial.print("contagem:");
      Serial.println(contagem);
      delay(1000);
  }
  

// Calcula a Energia Eletrica consumida no periodo  
      if(contagem >=25){   // Linha que serve para definir o tamanho da amostra
       
      tempo_energia_eletrica_fim = millis();  // marca o fim do periodo de medicao
      
      contagem = 0;
      
      tempo_total_energia_eletrica = tempo_energia_eletrica_fim - tempo_energia_eletrica_inicio;
      
      tempo_energia_eletrica_inicio = millis(); // marca o inicio do proximo ciclo para nao perder a referencia do tempo

      tempo_total_energia_eletrica = (tempo_total_energia_eletrica/3600); // transforma de milissegundos para mili horas (10^-3 h)
      
      Energia_eletrica_consumida = Potencia_ativa_media*tempo_total_energia_eletrica;
    
      
      Potencia_ativa_media = 0;

      Energia_eletrica_consumida_acumulada = Energia_eletrica_consumida + Energia_eletrica_consumida_acumulada;

      
      if(Energia_eletrica_consumida_acumulada<10000){
      Energia_eletrica_relogio = Energia_eletrica_consumida_acumulada;  
      Serial.println("MEDIDOR DE ENERGIA_ELEtRICA:");
      Serial.print("Energia_eletrica_relogio:");
      Serial.print(Energia_eletrica_relogio);
      Serial.println(" mW.h");
      }

      if(Energia_eletrica_consumida_acumulada>=10000 && Energia_eletrica_consumida_acumulada <10000000){
      Energia_eletrica_relogio =  Energia_eletrica_consumida/1000; 
      Serial.println("MEDIDOR DE ENERGIA_ELEtRICA:");
      Serial.print("Energia_eletrica_consumida:");
      Serial.print(Energia_eletrica_relogio);
      Serial.println(" W.h");
      }

      
      if(Energia_eletrica_consumida_acumulada>=10000000){
      Energia_eletrica_relogio =  Energia_eletrica_consumida/1000000; 
      Serial.println("MEDIDOR DE ENERGIA_ELEtRICA:");
      Serial.print("Energia_eletrica_consumida:");
      Serial.print(Energia_eletrica_relogio);
      Serial.println(" KW.h");
      }

      delay(5000);
      
      }
  
  
  }
