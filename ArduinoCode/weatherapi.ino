
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial mySerial(1, 3); // RX, TX
TinyGPS gps; // create gps object

long latm,lonm; // create variable for latitude and longitude object

const char* ssid     = "SENTI";      // SSID of local network
const char* password = "senti143";   // Password on network
String APIKEY = "374855c9b61490e6c7a641156d1c6e6e";
//String CityID = "253394"; //Sparta, Greece
//String CityID = "22592742"; 
//String CityID = "264371"; //Athens, Greece
//int Lat[20];
//int Lon [20];
String Lat = "22592742";
String Lon = "88412338";
String lat = "";
String lon = "";
void g();
WiFiClient client;
const char *host = "192.168.43.24";
char servername[]="api.openweathermap.org";  // remote server we will connect to
String result;
int port=8081;
int  counter = 60;

String weatherDescription ="";
String weatherLocation = "";
String Country;
float Temperature;
float Humidity;
float Pressure;

void displayConditions(float Temperature,float Humidity, float Pressure);
void displayWeather(String location,String description);

void setup() {
  Serial.begin(115200);
    
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
  }
  
  Serial.println("Connected");
  delay(1000);

}

void loop() {
    getWeatherData();
    delay(1000*60*10);
}

void getWeatherData() //client function to send/receive GET request data.
{

  if (client.connect(servername, 80)) {  //starts client connection, checks for connection
  
      if (mySerial.available()) {

char c = mySerial.read();
Serial.write( c );
if (gps.encode( c ))
      { // encode gps data
      gps.get_position(&latm,&lonm); // get latitude and longitude
      // display position
      Serial.print("Position: ");
      Serial.print("lat: ");Serial.println(latm);Serial.print(" ");// print latitude
      Serial.print("lon: ");Serial.println(lonm); // print longitude
      Lat= latm;
      Lon= lonm;
    
      }

  }
   String lat=Lat.substring(0,2)+"."+Lat.substring(2);
String lon=Lon.substring(0,2)+"."+Lon.substring(2);

  client.println("GET /data/2.5/weather?lat="+lat+"&lon="+lon+"&units=metric&APPID="+APIKEY);
     //client.println("GET /data/2.5/weather?id="+CityID+"&units=metric&APPID="+APIKEY);
    //client.println("GET /data/2.5/weather?lat=22592742&lon=88412338&units=metric&APPID=374855c9b61490e6c7a641156d1c6e6e");
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  } 
  else {
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
  }

  while(client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
      result = result+c;
      
    }

  client.stop(); //stop client
  result.replace('[', ' ');
  result.replace(']', ' ');
  Serial.println(result);

char jsonArray [result.length()+1];
result.toCharArray(jsonArray,sizeof(jsonArray));
jsonArray[result.length() + 1] = '\0';

StaticJsonDocument<1024> doc;
DeserializationError error = deserializeJson(doc,jsonArray);
if (error)
{
  Serial.println("deserializeJson() failed with code");
  Serial.println(error.c_str());
}

String location = doc["name"];
String country = doc["sys"]["country"];
float temperature = doc["main"]["temp"];
float humidity = doc["main"]["humidity"];
String weather = doc["weather"]["main"];
String description = doc["weather"]["description"];
float pressure = doc["main"]["pressure"];

weatherDescription = description;
weatherLocation = location;
Country = country;
Temperature = temperature;
Humidity = humidity;
Pressure = pressure;
displayWeather(weatherLocation,weatherDescription);
}

void displayWeather(String location,String description)
{
  
  Serial.print("loca: ");
  Serial.println(location);
  
  Serial.print("con: ");
   Serial.println(Country);
  
  Serial.print("des: ");
  Serial.println(description);

  if(WiFi.status() == WL_CONNECTED) {
    
   /* HTTPClient http;
     String postData ="latitude="+Lat+"&longitude="+Lon+"&Location="+location+"&Weather="+description;
    //http.begin("http://192.168.1.3/smart1/write2.php");              //change the ip to your computer ip address
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

   String url="192.168.1.3:80/smart1/write2.php?latitude="+Lat+"&longitude="+Lon+"&Location="+location+"&Weather="+description;
    
    Serial.print("URL : ");
    Serial.println(url);
   // http.begin(url);
    int httpCode = http.POST(url);
    String response = "";
    Serial.println(httpCode);  
    if (httpCode > 0) {
      // start of fetching get process
      response = http.getString();
      Serial.print("Response #1 : ");
      Serial.println(response);
    }
    else{
      Serial.println(httpCode);
      http.end();
    // end of fetching get process

    delay(500);
}
}*/
HTTPClient http;
    displayConditions(Temperature,Humidity,Pressure);
    String url="http://192.168.43.24:8081/smart1/write1.php?temperature="+String(Temperature)+"&humidity="+String(Humidity)+"&Pressure="+String(Pressure);
    
    http.begin(url);

    http.addHeader("Content-Type","text/plain");

    int httpCode=http.GET();

    String payload=http.getString();
    Serial.println(payload);
}
}

void displayConditions(float Temperature,float Humidity, float Pressure)
{

 Serial.print(Temperature,1);
 Serial.print((char)223);
 Serial.print("C ");
 
 //Printing Humidity
 Serial.print(" H:");
 Serial.print(Humidity,0);
 Serial.print(" %");
 
 //Printing Pressure

 Serial.print(Pressure,1);
 Serial.print(" hPa");

}
