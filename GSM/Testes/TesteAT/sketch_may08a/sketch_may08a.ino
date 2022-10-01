#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 10); // RX, TX
void setup() {
  Serial.begin(9600);  //Скорость порта для связи Arduino с компьютером
  Serial.println("Goodnight moon!");
  mySerial.begin(9600);  //Скорость порта для связи Arduino с GSM модулем
  mySerial.println("AT");
}

void loop() {
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}
