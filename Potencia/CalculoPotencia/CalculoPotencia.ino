// =============================================================================================================
// --- Bibliotecas ---

#include "EmonLib.h"            //Biblioteca para o sensor de corrente
#include <SPI.h>                //Biblioteca SPI
 
EnergyMonitor emon1;            //cria objeto para sensor de corrente

// =============================================================================================================

// --- Mapeamento de Hardware ---
#define     pin_sct     A0     //sensor de corrente

// =============================================================================================================

void setup() {

  Serial.begin(9600);                  //inicia serial com 9600 baud rate
  
  pinMode(pin_sct, INPUT);             //entrada para sensor de corrente
  
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/33 = 60
  emon1.current(pin_sct, 60.607);
 
}

// =============================================================================================================

void loop() {

  //Calcula a corrente
  double Irms = emon1.calcIrms(1480);  // 1480 = n° de amostras lidas

  //Mostra o valor da corrente no serial monitor e display
  Serial.print("Corrente : ");
  Serial.print(Irms); // Irms
  Serial.println(" A");
  delay(10);  
  
}
