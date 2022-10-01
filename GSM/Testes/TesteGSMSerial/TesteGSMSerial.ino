#include <SoftwareSerial.h>
 
//Porta do Arduino onde o pino TX do Módulo GSM esta conectado
#define TX_PIN 10
//Porta do Arduino onde o pino RX do Módulo GSM esta conectado
#define RX_PIN 11
#define baud 9600

#define TIME_OUT_READ_SERIAL 5000

//Cria comunicacao serial via software nas portas digitais definidas acima
SoftwareSerial serialGSM(TX_PIN, RX_PIN);

class SIM800L
{
public:
  //getRequest("api.thingspeak.com", 80, "update?api_key=2SI6SD2L6GLGILN3&field1=18")
  String getRequest(String host, int port, String uri)
  {
    this->serialWrite("AT+CIPSTART=\"TCP\",\"" + host + "\",\"" + port + "\"\r\n");
    String content = "GET /" + uri + " HTTP/1.1\r\n" + "Host:"+host+"\r\n\r\n";

    String cmdLength = String("AT+CIPSEND=") + content.length() + "\r\n";
    this->serialWrite(cmdLength);
    this->serialWrite(content);
    //this->serialWrite("AT+CIPCLOSE=0\r\n");
  }

  //connectAPN("zap.vivo.com.br", "vivo", "vivo")
  bool connectAPN(String apn, String user, String password)
  {
    this->serialWrite("AT+CIPMODE=0\r\n");
    this->serialWrite("AT+CIPMUX=0\r\n");
    this->serialWrite("AT+CGATT=1\r\n");
    this->serialWrite("AT+CSTT=\""+ apn +"\",\""+ user +"\",\""+ password +"\"\r\n");
    this->serialWrite("AT+CIICR\r\n");
    this->serialWrite("AT+CIFSR\r\n");

    return true;
  }

private:
  void serialWrite(String command)
  {
   serialGSM.print(command);

   long wtimer = millis();
   while (wtimer + 3000 > millis()) {
    while (serialGSM.available()) {
      char aux = serialGSM.read();
      Serial.write(aux);
    }
   }


  }

};

  
SIM800L meuModulo;

void sendTemperature(float temp)
{
  meuModulo.getRequest("api.thingspeak.com", 80, String("update?api_key=2SI6SD2L6GLGILN3&field1=") + temp);
}

void setup()
{
  randomSeed(analogRead(0));
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(baud);
  while(!Serial);

  Serial.println("Vamo dale");
  
  //Inicia comunicacao serial com o GSM
  serialGSM.listen();
  serialGSM.begin(baud);
  delay(1000);

  Serial.println("Trying to connect to APN...");
  meuModulo.connectAPN("zap.vivo.com.br", "vivo", "vivo");
  
  Serial.println("Sending first measure...");
  sendTemperature(random(2700, 3000) / 100.0);
  Serial.println("Sending second...");
  sendTemperature(random(2700, 3000) / 100.0);
  //Serial.println("Setup Completo!");
}
 
void loop() {
  //Serial.println("Oin");
  float temp = random(2700, 3000) / 100.0;
  //Serial.println(String("Sending ") + temp);
  //sendTemperature(temp);
  delay(200);
}
