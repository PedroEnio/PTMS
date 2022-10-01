#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "SIM800L.h"

#define pinTrafo A4        // Porta do sensor de tensão
#define pinSCT A0          // Porta do sensor de corrente
#define DS18B20_OneWire 9  // Porta do sensor de temperatura
#define SIM800_RX_PIN A1    // Porta RX do Modulo GSM
#define SIM800_TX_PIN A3    // Porta TX do Modulo GSM
#define SIM800_RST_PIN A2   // Porta RESET do Modulo GSM
#define INTERVAL 60000     // Intervalo entre envio de dados
#define AMOSTRAS 200       // Quantidade de amostras de tensão e corrente
#define aRef 4.66          // tensao de referencia do arduino

// Variaveis utilizadas
const char APN[] = "zap.vivo.com.br";
const String URL_BASE = "https://api.thingspeak.com/update?api_key=2SI6SD2L6GLGILN3";
float temperature1, temperature2;
long now, lastSent;
int sensor_tensao, sensor_corrente;
float tensao, tensao_a, corrente, corrente_a, tensao_quad, corrente_quad, tensao_rms, corrente_rms;
float potencia_inst = 0;
float potencia_media = 0;
float potencia_ativa = 0;
float potencia_aparente = 0;
float fator_de_potencia = 0;
float sum_tensao = 0;
float sum_corrente = 0;

SIM800L* sim800l;
OneWire oneWire(DS18B20_OneWire);
DallasTemperature sensorTemp(&oneWire);

// Funçao para envio dos dados
void sendMeasures(float temperature_1, float temperature_2, float power, float fator_pot)
{
  String url = URL_BASE + "&field1=" + temperature_1 + "&field2=" + power + "&field5=" + fator_pot + "&field6=" + temperature_2;  

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

// Funçao para tensao
float voltage(){
  sensor_tensao = analogRead(pinTrafo);
  tensao_a = ((sensor_tensao*aRef)/1024)-2.333;       // retirando o compensando de 2.5V
  tensao_a = (10.1*tensao_a);                       // relação entre a tensao na porta do arduino e a tensao no transformador de 9V (Divisor de tensão) 
  tensao_a = (25.9*tensao_a);                       // relação entre a tensao no transformador de 9V e a tensao medida (Relação de transformação)   
  return tensao_a;

  }
  
// Funçao para corrente 
float current(){
  sensor_corrente = analogRead(pinSCT);          
  corrente_a = ((sensor_corrente*aRef)/1024)-2.333;  
  return corrente_a;
  }

// Setup
void setup() {  
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);
  while(!Serial);

  // Initialize DS18B20
  //sensorTemp.begin();
  //Serial.print(sensorTemp.getDeviceCount(), DEC);
  //Serial.println(" temperature sensors found.");
  // Initialize a SoftwareSerial
  SoftwareSerial* serial = new SoftwareSerial(SIM800_TX_PIN, SIM800_RX_PIN);
  serial->begin(9600);
  Serial.println("Starting GPRS Module Serial");
  delay(1000);
  // Initialize SIM800L driver with an internal buffer of 200 bytes and a reception buffer of 512 bytes, debug disabled
  sim800l = new SIM800L((Stream *)serial, SIM800_RST_PIN, 200, 512, (Stream*)&Serial  );

  // Equivalent line with the debug enabled on the Serial
  //sim800l = new SIM800L((Stream *)serial, SIM800_RST_PIN, 200, 512, (Stream *)&Serial);

  // Setup module for GPRS communication
  setupModule();

  lastSent = -1;
}

// Loop
void loop() {
 
  now = millis();

  if (now >= lastSent + INTERVAL) {
    sensorTemp.requestTemperatures();
    temperature1 = sensorTemp.getTempCByIndex(0);
    temperature2 = sensorTemp.getTempCByIndex(1);
    
    potencia_media = 0;       // GARANTIR QUE O VALOR MEDIO SEJA CALCULADO DENTRO DO PERIODO ESCOLHIDO
    sum_tensao = 0;
    sum_corrente = 0; 
    
    for(int i=0; i<AMOSTRAS;i++)  // O NUMERO DE AMOSTRAS FOI DENIFINIDO PARA COLETAR CORRENTE E TENSAO DURANTE 9 CICLOS DA ONDA DA REDE 
    {
      tensao = voltage();
      corrente = current();
      
      corrente_quad = corrente*corrente;
      tensao_quad = tensao*tensao;

      sum_tensao = sum_tensao + tensao_quad;
      sum_corrente = sum_corrente + corrente_quad;
      
      potencia_inst = tensao*corrente;

      potencia_media = potencia_media + potencia_inst;  // Somatorio da potencia instatanea 
     
      delay(1);
  
    }

    tensao_rms = sqrt(sum_tensao/AMOSTRAS);
    corrente_rms = sqrt(sum_corrente/AMOSTRAS);

    potencia_ativa = (potencia_media/AMOSTRAS);
    potencia_aparente = ((sqrt(sum_tensao*sum_corrente))/AMOSTRAS); 
    
    // Tratamento de dados, considerando que ocorre interrupção de tensao quando o valor da tensao for menor ou igual a 10% do valor nominal 
    if (tensao_rms <= 40){    
        potencia_ativa = 0;
        potencia_aparente = 0;
    }

    fator_de_potencia = potencia_ativa/potencia_aparente; 

    if (fator_de_potencia > 1){
      fator_de_potencia = 1; 
    }
    
    Serial.print("Temperature: ");
    Serial.print(temperature1);
    Serial.println("ºC");
    Serial.print("Tensão: ");
    Serial.println(tensao_rms);
    Serial.print("Corrente: ");
    Serial.println(corrente);
    Serial.print("Potencia Ativa: ");
    Serial.print(potencia_ativa);
    Serial.println("W");
    sendMeasures(temperature1, temperature2, potencia_ativa, fator_de_potencia);
    lastSent = now;
    Serial.println("Waiting for next measurement...");
  }
}

// Funçao para configurar o Modulo GSM
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
