/********************************************************************************
 * Example of HTTPS GET with SoftwareSerial and Arduino-SIM800L-driver          *
 *                                                                              *
 * Author: Olivier Staquet                                                      *
 * Last version available on https://github.com/ostaquet/Arduino-SIM800L-driver *
 ********************************************************************************
 * MIT License
 *
 * Copyright (c) 2019 Olivier Staquet
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************/
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "SIM800L.h"

#define pinTrafo A0
#define pinSCT A1 
#define DS18B20_OneWire 7
#define SIM800_RX_PIN 10
#define SIM800_TX_PIN 11
#define SIM800_RST_PIN 6
#define INTERVAL 60000
#define AMOSTRAS 595 
#define FATOR 240 // (tensao-2500) = filtro -> O valor maximo encontrado foi 1440, ou 1,44 volts a mais. Dai, 1,44*x=311 -> x = 215.97 + constante compensadora do trafo 9V

int DADO[AMOSTRAS];
const char APN[] = "zap.vivo.com.br";
const String URL_BASE = "https://api.thingspeak.com/update?api_key=2SI6SD2L6GLGILN3";
float temperature;
long now, lastSent;
int sensor_tensao, sensor_corrente;
float tensao, tensao_a, corrente, corrente_a, tensao_quad, corrente_quad;
float potencia_inst = 0;
float potencia_media = 0;
float potencia_ativa = 0;
float potencia_aparente = 0;
float sum_tensao = 0;
float sum_corrente = 0;

SIM800L* sim800l;
OneWire oneWire(DS18B20_OneWire);
DallasTemperature sensorTemp(&oneWire);

void sendMeasures(float temperature, float power)
{
  String url = URL_BASE + "&field1=" + temperature + "&field2=" + power;  

  // Establish GPRS connectivity (5 trials)
  bool connected = false;
  for(uint8_t i = 0; i < 5 && !connected; i++) {
    delay(1000);
    connected = sim800l->connectGPRS();
  }

  // Check if connected, if not reset the module and setup the config again
  if(connected) {
    Serial.println(F("GPRS connected !"));
  } else {
    Serial.println(F("GPRS not connected !"));
    Serial.println(F("Reset the module."));
    sim800l->reset();
    setupModule();
    return;
  }
  
  Serial.println(F("Start HTTP GET..."));

  // Do HTTP GET communication with 10s for the timeout (read)
  uint16_t rc = sim800l->doGet(url.c_str(), 10000);
   if(rc == 200) {
    // Success, output the data received on the serial
    Serial.print(F("HTTP GET successful ("));
    Serial.print(sim800l->getDataSizeReceived());
    Serial.println(F(" bytes)"));
    Serial.print(F("Received : "));
    Serial.println(sim800l->getDataReceived());

  } else {
    // Failed...
    Serial.print(F("HTTP GET error "));
    Serial.println(rc);
    sim800l->reset();
    setupModule();
  }

  // Close GPRS connectivity (5 trials)
  bool disconnected = sim800l->disconnectGPRS();
  for(uint8_t i = 0; i < 5 && !connected; i++) {
    delay(100);
    disconnected = sim800l->disconnectGPRS();
  }
  
  if(disconnected) {
    Serial.println(F("GPRS disconnected !"));
  } else {
    Serial.println(F("GPRS still connected !"));
  }
  
}

float voltage(){
  sensor_tensao = analogRead(pinTrafo);
  tensao_a = map(sensor_tensao,0,1024,0, 5000);   //map para a tensao de referencia do arduino
  tensao_a = ((tensao_a - 2500)/1000)*FATOR;      //conversao da tensao para Volts com fator de multiplicação
  return tensao_a;
  }
  
float current(){
  sensor_corrente = analogRead(pinSCT);          
  corrente_a = map(sensor_corrente, 0, 1024, 0, 5000);    
  corrente_a = (5*(corrente_a-2500))/1000;                    //conversao para corrente em A 
  return corrente_a;
  }


class TotalPower{
  public:
  
  float potencia_media;
 
  float active_power = potencia_media/AMOSTRAS;
  float apparent_power = (sqrt(sum_tensao*sum_corrente))/AMOSTRAS; 
  
  float calc(){ 
    potencia_media = 0;       // GARANTIR QUE O VALOR MEDIO SEJA CALCULADO DENcaTRO DO PERIODO ESCOLHIDO
    sum_tensao = 0;
    sum_corrente = 0; 
    
    for(int i=0; i<AMOSTRAS;i++)  // O NUMERO DE AMOSTRAS FOI DENIFINIDO PARA COLETAR CORRENTE E TENSAO DURANTE 4 CICLOS DA ONDA DA REDE 
    {
      tensao = voltage();
      corrente = current();
      potencia_inst = tensao*corrente;
      //DADO[i] = potencia_inst; 
      potencia_media = potencia_media + potencia_inst;  // Somatorio da potencia instatanea 
      
      corrente_quad = corrente*corrente;
      tensao_quad = tensao*tensao;
  
      sum_tensao = sum_tensao + tensao_quad;
      sum_corrente = sum_corrente + corrente_quad;
  
    }
  }
    
};

void setup() {  
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);
  while(!Serial);

  // Initialize DS18B20
  sensorTemp.begin();
  Serial.print(sensorTemp.getDeviceCount(), DEC);
  Serial.println(" temperature sensors found.");
  // Initialize a SoftwareSerial
  SoftwareSerial* serial = new SoftwareSerial(SIM800_RX_PIN, SIM800_TX_PIN);
  serial->begin(9600);
  delay(1000);
   
  // Initialize SIM800L driver with an internal buffer of 200 bytes and a reception buffer of 512 bytes, debug disabled
  sim800l = new SIM800L((Stream *)serial, SIM800_RST_PIN, 200, 512);

  // Equivalent line with the debug enabled on the Serial
  //sim800l = new SIM800L((Stream *)serial, SIM800_RST_PIN, 200, 512, (Stream *)&Serial);

  // Setup module for GPRS communication
  setupModule();

  lastSent = -1;
}

void loop() {


  TotalPower power; 
  now = millis();

  if (now >= lastSent + INTERVAL) {
    sensorTemp.requestTemperatures();
    temperature = sensorTemp.getTempCByIndex(0);
    power.calc();
    potencia_ativa = power.active_power;
    potencia_aparente = power.apparent_power;
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("ºC");
    Serial.print("Tensao: ");
    Serial.print(potencia_ativa);
    Serial.println("V");
    sendMeasures(temperature, potencia_ativa);

/*
    // Go into low power mode
    bool lowPowerMode = sim800l->setPowerMode(MINIMUM);           
    if(lowPowerMode) {
      Serial.println(F("Module in low power mode"));
    } else {
      Serial.println(F("Failed to switch module to low power mode"));
    }
*/
    lastSent = now;
    Serial.println("Waiting for next measurement...");
  }
}

void setupModule() {
    // Wait until the module is ready to accept AT commands
  while(!sim800l->isReady()) {
    Serial.println(F("Problem to initialize AT command, retry in 1 sec"));
    delay(1000);
  }
  Serial.println(F("Setup Complete!"));

  // Wait for the GSM signal
  uint8_t signal = sim800l->getSignal();
  while(signal <= 0) {
    delay(1000);
    signal = sim800l->getSignal();
  }
  Serial.print(F("Signal OK (strenght: "));
  Serial.print(signal);
  Serial.println(F(")"));
  delay(1000);

  // Wait for operator network registration (national or roaming network)
  NetworkRegistration network = sim800l->getRegistrationStatus();
  while(network != REGISTERED_HOME && network != REGISTERED_ROAMING) {
    delay(1000);
    network = sim800l->getRegistrationStatus();
  }
  Serial.println(F("Network registration OK"));
  delay(1000);

  // Setup APN for GPRS configuration
  bool success = sim800l->setupGPRS(APN);
  while(!success) {
    success = sim800l->setupGPRS(APN);
    delay(5000);
  }
  Serial.println(F("GPRS config OK"));
}
