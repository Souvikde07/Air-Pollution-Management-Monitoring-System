#include <SoftwareSerial.h>
#include <dht.h>
#include <LiquidCrystal.h>
#include <Wire.h>
SoftwareSerial ArduinoUno(3,2);
int smoke = A0;
int sensorThres = 400;
dht DHT;
LiquidCrystal lcd(7,8,9,10,11,12);
#define DHT11_PIN 4
void setup()
{
	Serial.begin(9600);
	ArduinoUno.begin(4800);
  pinMode(3,INPUT);
  pinMode(2,OUTPUT);
  pinMode(smoke, INPUT);
  lcd.begin(20, 4);
  lcd.clear();
  Wire.begin();
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Date,Time,Temparature,Humidity,Air Quality");
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  int analogSensor = analogRead(smoke);
  int i = DHT.temperature;
  int j = DHT.humidity;
  lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
  lcd.print("Temparature: "); // Prints Sensor Val: to LCD
  lcd.print(i); // Prints value on Potpin1 to LCD
  lcd.setCursor(16,0);
  lcd.print("C");
  lcd.setCursor(0,1); // Sets the cursor to col 1 and row 0
  lcd.print("Humidity: "); // Prints Sensor Val: to LCD
  lcd.print(j); // Prints value on Potpin1 to LCD
  lcd.setCursor(13,1);
  lcd.print("%");
  lcd.setCursor(0,2);
  lcd.print("Air Quality: ");
  lcd.print(analogSensor);
  lcd.setCursor(17,2);
  lcd.print("PPM");
  if(analogSensor >= sensorThres)
  {
    lcd.setCursor(0,3);
    lcd.print("Danger!");
  }
  else
  {
    lcd.setCursor(0,3);
    lcd.print("Normal Air");
  }
  Wire.beginTransmission(8);
  Wire.write(i);
  Wire.write(j);
  Wire.write(analogSensor);
  Wire.endTransmission();
  ArduinoUno.print(i);
  ArduinoUno.println("\n");
  ArduinoUno.print(j);
  ArduinoUno.println("\n");
  ArduinoUno.print(analogSensor);
  ArduinoUno.println("\n");
  Serial.println( (String) "DATA,DATE,TIME," + i + "," + j +  "," + analogSensor);
  delay(10000);
}
