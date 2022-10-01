#include "EmonLib.h"
 
EnergyMonitor SCT013;
 
int pinSCT = A1;   //Pino analógico conectado ao SCT-013
int pinTrafo = A0;
int Voltage_sensorValue, Current_sensorValue;
unsigned long time_crrt, time_ddp, defasagem, defasagem_medida;
float angulo, fator_potencia;



void setup() {
  
  SCT013.current(pinSCT, 6.0606);
  Serial.begin(9600);
}

void loop() {
  Voltage_sensorValue = analogRead(pinTrafo); // 112 us (leiura)
  
  if(Voltage_sensorValue>510 && Voltage_sensorValue<514) {
  time_ddp = micros();
  }
  Current_sensorValue = analogRead(pinSCT); // 112 us (leiura)
    
  while(Current_sensorValue<500 || Current_sensorValue>520){
   Current_sensorValue = analogRead(pinSCT);   
   }
  
  time_crrt = micros(); 
  
  defasagem_medida = time_crrt - time_ddp - 224; // 224us : Deve ser utilizado para compensar as leituras da linha 54 e a ultima leitura do while na linha 57.
                                                 // o atmega328(microcontrolador) demora 112 us para realizar uma leitura analogica 

  // Elimina ruidos, e leituras indesejadas (tanto para mais quanto para menos)
  if(defasagem_medida<=3000 && defasagem_medida >224 ) {
    defasagem= defasagem_medida;
  }
  
  Serial.print("defasagem em ms:");
  Serial.println(defasagem);

  angulo = map(defasagem,0,4166,0,90); // O periodo da onda da rede vale 16,6 ms(1/60----f = 60Hz) entao apos este tempo a onda avanca 360º.
                                       // Como a defasagem foi calculada em micro segundos(  micros() ) na linha 52 e 60, usamos 4166us = 4,16ms.
                                       // Logo, se 16,6ms vale 360º, 90º vale 4,16ms (4166 us)   
  
  Serial.print("angulo defasagem:");
  Serial.println(angulo);

  fator_potencia = cos(3.14*(angulo/180)); // transforma o angulo em radiano.  
  Serial.print("fator de potencia em rad:");
  Serial.println(fator_potencia);

}
