#define AMOSTRAS 512
int DADO[AMOSTRAS];
int sensorValue, i, tensao, cont; 
int turn = 1;


void setup() {
  Serial.begin(9600);
}

void loop(){

  // COLETANDO AMOSTRAS
  for(i=0; i<AMOSTRAS;i++)
  {
    sensorValue = analogRead(A0);
    DADO[i] = sensorValue; 
    //delayMicroseconds(148);
  }

  // IMPRIMINDO AMOSTRAS 
  for(i=0; i<AMOSTRAS;i++)
  {
    tensao = map(DADO[i], 0, 1024, 0, 220);
    //tensao = DADO[i];
    //Serial.println(tensao); 
    
    if(tensao <= 6)
    {
      cont++;       // contador para evitar inverter os valores quando temos medidas consecutivas menores quer 5 (por exemplo, tensao = 3 e depois tensao = 4) 
      if(cont<2)
      {
        turn = -1*turn;
      }
    }
    else{cont = 0;}

    
    // 'if' e 'else' para inverter valor de meio ciclo 
    if(turn > 0)
    {
      Serial.println(tensao); 
    }
    
    else
    {  
      Serial.println(-1*tensao);   
    }
  
  }
 // while(1){};0
}














#include <Console.h>
/*
int valor_analogico_ddp;
//int valor_analogico_ddp_maior;

void setup() {
  Serial.begin(9600);
  //tempo_energia_eletrica_inicio = millis();

}

void loop() {
 
  //calcular valor de pico ddp
   //valor_analogico_ddp_maior = analogRead(A0);
   //for(int i=0;i<1000;i++){
   valor_analogico_ddp = analogRead(A0);
   Serial.print("valor analogico:");
   Serial.println(valor_analogico_ddp);

   //if(valor_analogico_ddp>valor_analogico_ddp_maior){
      //valor_analogico_ddp_maior = valor_analogico_ddp;  
    //}
     
   //}

   //Serial.print("################## maior valor analogico:");
   //Serial.println(valor_analogico_ddp_maior);
}
*/


//int tensao = 0;
//int r0, r1, r2, u0, u1, u2, v , i= 0;
//float VMS, Vrms, Ptot, vf = 0;

/*
int sensorValue, pause,i  = 0;
float tensao, message, value = 0;
unsigned long time;
char buf[32];
//int ValorPico     = 0;
//int VpicoAnterior = 0;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(A5);
  tensao = map(sensorValue, 0, 1024, 0, 5);
  //Serial.print("Valor DDP: ");

  dtostrf(tensao, 8, 2, buf); //A funcao dtostrf() que converte variaveis do tipo float em uma string. dtostrf(floatvar, StringLengthIncDecimalPoint, numVarsAfterDecimal, charbuf);
  
  value = buf;

  if (pause == 0) {
      if (i < 10000) {
          message += ',';
          message += value;
          i++;
      }
      else {
          pause = 1;
          Serial.println(message);
      }
  }
  
}
*/


  // Codigo para calcular o calor de pico 
 /*
  if (sensorValue > ValorPico){
    ValorPico = sensorValue;
  }
  if (ValorPico != VpicoAnterior) {
    Serial.print("Valor Pico");
    Serial.println(ValorPico);
    VpicoAnterior = ValorPico;
  }

 
}

 /*
 void loop() {
  r2 = r1;
  r1 = r0;
  r0 = analogRead(A0);
  u2 = u1;
  u1 = u0;
  // 0.5Hz to 200Hz Band Pass Filter
  u0 = 0.2929*(r0-r2) + 1.411*u1 -0.4142*u2;
  v = u0;

  // Calculate Mean-Square Current (Amps)
  VMS = 0.99*VMS +0.01*v*v;
  // Calculate Root-Mean-Square (Amps)
  //Vrms = sqrt(VMS);
  // Convert to RMS Power:
  // Multipy by 230V (rms)
  // 30*5/1024 is the accounts for the gain of the Current Transformer and ADC
  delay(1);
  
  if (millis() - time > 5000)
  {
    // Print the RMS Power in the last 5 seconds to the Console
    Console.print("V = ");
    Console.println(VMS);
  }
}
*/
