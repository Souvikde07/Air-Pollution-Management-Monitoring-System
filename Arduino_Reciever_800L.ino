#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
String number1 = "+919635964495";
String number2 = "+919449031621";
String number3 = "+919638705414";
String number4 = "+918884315522";
String number5 = "+918200998423";

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  _buffer.reserve(50);
  sim.begin(9600);
}
void loop() {
  delay(10000);
}
void receiveEvent(int howMany) {
  int l = Wire.read();
  int m = Wire.read();
  int t = Wire.read();
  Serial.println(l);
  Serial.println(m);
  Serial.println(t);
  if (Serial.available() > 0)
  {
    if (t >= 80)
    {
      Serial.println("Danger");
      Message();
    }
  }
  if (sim.available() > 0)
    Serial.write(sim.read());
}
void Message() {
  SendMessage1();
  SendMessage2();
  SendMessage3();
  SendMessage4();
  SendMessage5();
}
void SendMessage1()
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number1 + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "Hey Man... Wassup!!!";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
}
void SendMessage2()
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number2 + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "Hey Man... Wassup!!!";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
}

void SendMessage3()
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number3 + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "Hey Man... Wassup!!!";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
}
void SendMessage4()
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number4 + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "Hey Man... Wassup!!!";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
}
void SendMessage5()
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number5 + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "Hey Man... Wassup!!!";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
}
String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000)
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}
