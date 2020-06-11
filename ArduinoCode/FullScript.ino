const int moisture_sensor_pin = A0;  /* Soil moisture sensor O/P pin */
//...............................................................

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 22  //...........d2
#define S1 23  //.........d3
#define S2 24  //.........d5
#define S3 25  //.........d6
#define sensorOut 15

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
//......................................................................


//................................IR SENSOR.................................
#define ir_pin_in 26  //............d7......

//............................................................................
//.....................................ldr analog.......................................
//const int ledPin = 13;
const int ldrPin = A1;
//.........................................................................................

//..........................................ph analog........................................
#define SensorPin A2  //pH meter Analog output to Arduino Analog Input 0
//#define ph_out 12
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[15],temp;
//..............................................................................................


//...........................bmp280(pressure sensor)...............................................
#include <Wire.h>
#include "SPI.h" //Why? Because library supports SPI and I2C connection
#include <Adafruit_Sensor.h>
#include "Adafruit_BME280.h"

//Setup connection of the sensor
Adafruit_BME280 bme;
//..................................................................................................


//............................................rain water............................................
int nRainDigitalIn = 26;   //pin number d3....................
int nRainVal;
boolean bIsRaining = false;
String strRaining;
//....................................................................................................


#include "SoftwareSerial.h"
String ssid ="SENTI";

String password="senti143";

SoftwareSerial esp(11, 10);// RX, TX

String data;

String server = "192.168.43.24"; // www.example.com

String uri = "/smart1/write.php?";// our example is /esppost.php

void setup() {

esp.begin(115200);

Serial.begin(115200);
Serial.println("testing");
//.............................moisture............
  pinMode(moisture_sensor_pin,INPUT);
  //...............................................................................
  //.....................................colour sensor.............................
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  //...............................................................
 

  //..............................ir sensor.................................
  pinMode(ir_pin_in,INPUT);
 // pinMode(ir_pin_out,OUTPUT);
  //..............................................................................
//...................................ldranalog................................................./
//pinMode(ledPin, OUTPUT);
pinMode(ldrPin, INPUT);
//..............................................................................................

//.......................................ph analog..............................................
//pinMode(ph_out,OUTPUT);
//...............................................................................................

//...........................bme280(pressure)...................................................
bme.begin(0x76);
//...............................................................................................

//.................................rain water...................................................
pinMode(2,INPUT);
//..............................................................................................
reset();
connectWifi();
}

//reset the esp8266 module

void reset() {

esp.println("AT+RST");

delay(1000);

if(esp.find("OK") ) Serial.println("Module Reset");
else
Serial.println("no response");

}

//connect to your wifi network

void connectWifi() {
esp.println("AT+CWMODE=1");
if(esp.find("OK"))
{
  Serial.println("IN CLIENT MODE");
}
delay(500);
String cmd = "AT+CWJAP=\"" +ssid+"\",\"" + password + "\"";

esp.println(cmd);

delay(4000);

if(esp.find("OK")) {

Serial.println("Connected!");

}

else {

Serial.println("Cannot connect to wifi"); 
connectWifi();
}

}


void loop () {
// convert the bit data to string form
//http://localhost:8081/smart1/write2.php?ph_value=174&rain=yes&temp=100&humid=15
/*  moisture sensor code..........................................................*/
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(moisture_sensor_pin);   /* moisture pin*/
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  //Serial.print("Moisture Percentage = ");
  //Serial.print(moisture_percentage);
  //Serial.print("%\n\n");
  delay(2000);

//.....................................................................................


//....................COLOUR SENSOR....................................................
 // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  
   // Printing the RED (R) value
  //Serial.print("R = ");
  //Serial.print(redFrequency);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  
  // Printing the GREEN (G) value  
  //Serial.print(" G = ");
  //Serial.print(greenFrequency);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  
  // Printing the BLUE (B) value 
  //Serial.print(" B = ");
  //Serial.println(blueFrequency);
  delay(100);
  //........................................................................................................ 

  
//..........................................IR_SENSOR.............................................................
delay(2000);
//Serial.print("IRSensorip  ");
int ir_sensor=digitalRead(ir_pin_in);
//if(digitalRead(ir_pin_in)==0)
//{
//  Serial.println("...........ALERT...............");
//  }
// else{
//      Serial.println("...........NO_________________ALERT...............");
//    }
//.......................................................................................................................
delay(2000);
//..........................ldr_analog...........................................................
int ldrStatus = analogRead(ldrPin);
/*if (ldrStatus <= 200) {
digitalWrite(ledPin, HIGH);
Serial.print("Its DARK, Turn on the LED : ");
Serial.println(ldrStatus);
} else {
digitalWrite(ledPin, LOW);
Serial.print("Its BRIGHT, Turn off the LED : ");
Serial.println(ldrStatus);*/
//....................................................................................................

//................................ph analog...........................................................
for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<15;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=3;i<12;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value
  delay(2000);
  //.......................................................................................................
  

//...................................................bme280(pressure)........................................
//Serial.print("Temperature = ");
 int pressure = bme.readPressure();
  int temp = bme.readTemperature();
  int humi = bme.readHumidity();
  delay(2000);
  //............................................................................................................

  
//.........................rain water............................................................................
 int bIsRaining = !(digitalRead(nRainDigitalIn)); //Cheks Digital Pin 2, Output D0 
  delay(2000);
//......................................................................................................................

data = "ph_value=" + String(phValue) + "&rain=" + String(bIsRaining) + "&temp=" + String(temp) + "&humidity=" +String(humi) +"&pressure=" + String(pressure) +"&moisture=" + String(moisture_percentage) + "&greeness=" +String(greenFrequency)
+"&ir="+String(ir_sensor)+"&ldr="+String(ldrStatus);// data sent must be under this form //name1=value1&name2=value2.

httppost();

delay(5000);

}

void httppost () {
  //Serial.println("IN HTTPPOST");
 //String dmc="AT+CIPSTART=\"TCP\",\"" + server + "\",8081";
// Serial.println(dmc);
esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",8081");//start a TCP connection.
  //esp.println(dmc);
if( esp.find("OK")) {

Serial.println("TCP connection ready");

delay(1000);
String postRequest ="GET " + uri + data+" HTTP/1.0\r\n";

//"Host: " + server ;//+ "\r\n" +

//"Content-Length: " + data.length() + "\r\n" +

//"Content-Type: application/x-www-form-urlencoded\r\n" +

//"\r\n" + data;
Serial.println(postRequest);
String sendCmd = "AT+CIPSEND="+String(postRequest.length()+10);//determine the number of caracters to be sent.
esp.println(sendCmd);

//esp.println(postRequest.length()+10 );

delay(500);
Serial.println("Sending..");
esp.println(postRequest);

//if(esp.find(">")) { Serial.println("Sending.."); esp.print(postRequest);

//if( esp.find("SEND OK")) { Serial.println("Packet sent");
String tmpResp;
while (esp.available()) {

 tmpResp+= esp.readString();

}
Serial.println(tmpResp);
// close the connection

esp.println("AT+CIPCLOSE");
delay(1000);
}
else
{
  Serial.println("NO TCP");
}
}
