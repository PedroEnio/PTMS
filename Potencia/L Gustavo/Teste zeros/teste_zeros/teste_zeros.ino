/*/*CANAL L GUSTAVO - ROBOTICA E PROGRAMAÇÃO
 * PROJETO: Monitorando Energia Eletrica com potência ativa
 * Projetos Arduino
 * PROF. ENG. LUIZ GUSTAVO
 * codigo:teste para identificar os zeros da tensão e corrente  
 * O valor do meio periodo deve ser 8ms pois a frequência da rede e 60 Hz. Para outras frequências fazer t = 1/f;
 * 

*/
unsigned long tempo_1;
unsigned long tempo_2;
unsigned long meio_periodo;
int sensorValue;
int a = 1;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  
  sensorValue = analogRead(A1);
  
  
  if(sensorValue>508 && sensorValue<512) {
  tempo_1 = millis();
  delay(1);
  sensorValue = analogRead(A1);
  //Serial.println(sensorValue);
  //delay(5000);
  while(sensorValue<508 || sensorValue>512){
    sensorValue = analogRead(A1);
  
  
    }
  tempo_2 = millis();
 
  meio_periodo = tempo_2 - tempo_1;
  Serial.print("meio periodo:");
  Serial.println(meio_periodo);
  }


  
}
