
#include "EmonLib.h"
 
EnergyMonitor SCT013;

// PINOS
#define pinTrafo A0 //Pino analógico conectado ao sensor de tensão do Transformador
#define LM35_1 A1   //Pino analógico conectado ao sensor de temperatura 1
#define pinSCT A2   //Pino analógico conectado ao sensor de corrente SCT-013



// AMOSTRAS
#define AMOSTRAS 595     // Para uma taxa de amostragem de aproximadamente 8900Hz 

// CALIBRAÇÃO
#define FATOR 240     
int DADO[AMOSTRAS];


// TEMPO DE EXECUÇÃO
unsigned long start_time;
unsigned long finish_time;
unsigned long total_time;

// TEMPERATURA
float sensor_temperatura_1, temperatura_1, temperatura_media; 


// FATOR DE POTENCIA
int aux = 0;
int sensor_tensao_zero, sensor_corrente_zero;
unsigned long tempo_corr;
unsigned long tempo_ddp;
unsigned long defasagem;
unsigned long defasagem_medida;
float angulo;
float fator_de_potencia;

// POTENCIA 
int i;
int sensor_tensao, sensor_corrente;
int tensao, tensao_a, corrente;
int potencia_inst = 0;
int potencia_media = 0;
int potencia_ativa = 0;
int potencia_aparente = 0;

// ENERGIA 
float energia_consumida;
float energia_consumida_acumulada;
float energia_eletrica;


void setup() {
  
  //SCT013.current(pinSCT, 39.22);   
  Serial.begin(9600);
  start_time = millis();
  pinMode (LM35_1, INPUT);
}


void loop() {


 // ############################################################################ Calcular fator de potência ############################################################################
 
  sensor_tensao_zero = analogRead(pinTrafo);  
  
  if(sensor_tensao_zero > 510 && sensor_tensao_zero < 514) //Instante em que a tensão possui valor 0 
  {
    
    tempo_ddp = micros();
  
    sensor_corrente_zero = analogRead(pinSCT);
    
    while(sensor_corrente_zero < 500 || sensor_corrente_zero > 520) //Instante em que a corrente possui valor 0 após a tensão passar pelo 0 
    {
      sensor_corrente_zero = analogRead(pinSCT); 
      aux = aux + 1;  
    }
  
    tempo_corr = micros(); 
  
    defasagem_medida = tempo_corr - tempo_ddp - (112+112*aux); // (112+112*aux) us utilizado para compensar as leituras dos sensores 
                                                               // o atmega328 demora 112 us para realizar uma leitura analogica 
                                                  
    // Elimina ruidos
    if(defasagem_medida<=3000 && defasagem_medida >224 ) 
    {
      defasagem = defasagem_medida;
    }

    angulo = map(defasagem,0,4166,0,90);  // Se 16,6ms (periodo da onda da rede de 60Hz) vale 360º, 90º vale 4,16ms (4166 us)
  
    fator_de_potencia = cos(3.14*(angulo/180)); 
  
  }

  // ############################################################################ Calcular Potencia ############################################################################
  /*
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
  */


  // COLETANDO AMOSTRAS
  
  potencia_media = 0;       // GARANTIR QUE O VALOR MEDIA SEJA CALCULADO DENTRO DO PERIODO ESCOLHIDO
  
  for(i=0; i<AMOSTRAS;i++)  // O NUMERO DE AMOSTRAS FOI DENIFINIDO PARA COLETAR CORRENTE E TENSAO DURANTE 4 CICLOS DA ONDA DA REDE 
  {
    sensor_tensao = analogRead(pinTrafo);
    sensor_corrente = analogRead(pinSCT);
    
    tensao_a = map(sensor_tensao,0,1024,0, 5000);   //map para a tensao de referencia do arduino
    tensao = ((tensao_a - 2500)/1000)*FATOR;      //conversao da tensao para Volts com fator de multiplicação   
             
    corrente = map(sensor_corrente, 0, 1024, 0, 5000);    
    corrente = (5*(corrente-2500))/1000;                    //conversao para corrente em A 
    
    potencia_inst = tensao*corrente;
    //DADO[i] = potencia_inst; 
    potencia_media = potencia_media + potencia_inst;
  }

  potencia_ativa = potencia_media/AMOSTRAS;
  potencia_aparente = potencia_ativa/fator_de_potencia;

  // ############################################################################ Medir Temperatura ############################################################################
  sensor_temperatura_1 = analogRead(LM35_1);
  temperatura_1 = (sensor_temperatura_1)*0.48875855327;             //    5/(1023))/0.01 = 0.48875855327 

  temperatura_media = temperatura_1 ; 

// Calcula a Energia Eletrica consumida no periodo  
  finish_time = millis();  // marca o fim do periodo de medicao
      
  total_time = finish_time - start_time;
      
  start_time = millis(); // marca o inicio do proximo ciclo para nao perder a referencia do tempo

  total_time = (total_time/3600); // transforma de milissegundos para mili horas (10^-3 h)

  // ############################################################################        Plot       ############################################################################
  
  Serial.print("Potência ativa:");
  Serial.println(potencia_ativa);
  Serial.print("Potência aparente:");
  Serial.println(potencia_aparente);
  Serial.print("FP:");
  Serial.println(fator_de_potencia);
  Serial.print("Temperatura:");
  Serial.println(temperatura_media);
  /*
  energia_consumida = potencia_ativa*total_time;

  energia_consumida_acumulada = energia_consumida + energia_consumida_acumulada;

      
  if(energia_consumida_acumulada<10000){
    energia_eletrica = energia_consumida_acumulada;  
    Serial.println("MEDIDOR DE ENERGIA:");
    Serial.print("Consumo:");
    Serial.print(energia_eletrica);
    Serial.println(" mW.h");
  }

  if(energia_consumida_acumulada>=10000 && energia_consumida_acumulada <10000000){
    energia_eletrica = energia_consumida/1000; 
    Serial.println("MEDIDOR DE ENERGIA:");
    Serial.print("Consumo:");
    Serial.print(energia_eletrica);
    Serial.println(" W.h");
  }

  if(energia_consumida_acumulada>=10000000){
    energia_eletrica =  energia_consumida/1000000; 
    Serial.println("MEDIDOR DE ENERGIA:");
    Serial.print("Consumo:");
    Serial.print(energia_eletrica);
    Serial.println(" KW.h");
  }
*/
  delay(5000);
      
}
 
  
  
