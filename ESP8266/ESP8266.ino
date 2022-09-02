
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "NewPing.h"      // include NewPing library
#define BUTTON 12 //pulsador en GPIO12 (D6)
int contador=0;
// Uncomment one of the lines below for whatever DHT sensor type you're using!
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

/*Put your SSID & Password*/
const char* ssid = "Familia BG";  // Enter SSID here
const char* password = "3458cmdp.";  //Enter Password here

ESP8266WebServer server(80);

String estado = "";

int Contador;              
int Tiempo;
int EA=1;
int Periodo;
float EB=2;

int trigPin = 4;      // trigger pin
int echoPin = 0;      // echo pin

NewPing sonar(trigPin, echoPin);
 
void setup() {
  Serial.begin(115200);
  delay(100);
  

  pinMode(BUTTON, INPUT_PULLUP);        

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {
  Contador++;

  delay(1000);
  
  
  server.handleClient();
  if (EA==6){
  EA=0;
  }
    if (EB==6){
  EB=0;
  }
  if (Contador==90){
  Tiempo=0;
  Contador=0;
  EA=0;
  EB=0;
  }

    if (Contador<45){
 Periodo=1;
 estado = "Encendido";
  }else{
    Periodo=2;
    estado = "Apagado";
  }

//pinMode()
  
  
  
}

void handle_OnConnect() {


 Tiempo = Contador; // Gets the values of the temperature
  //EA = 1; // Gets the values of the humidity 
  //EB = 2; // Gets the values of the humidity 
  
  server.send(200, "text/html", SendHTML(EA,EB,Tiempo,Periodo)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float EA,float EB,float tiempo,float periodo){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<meta http-equiv='refresh' content='0.005'>";

  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 30px;} h1 {color: #444444;margin: 30px auto 15px;}\n";
  ptr +="p {font-size: 20px;color: #444444;margin-bottom: 5px;}\n";
  
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<p><img src='data:image/png;base64,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'><br>";
 
  ptr +="</div>";

ptr +="<p>Tiempo: ";
ptr +=(int)Tiempo;

ptr +="<p>Periodo: ";
ptr +=(int)Periodo;
  
  ptr +="<p> EQUIPO A  ";
  ptr +="  - - - - - - - - - - - ";
  ptr +="  EQUIPO B  ";
  ptr +="<p>    ";
  
  ptr +=(int)EA;
  ptr +="  - - - - - - - - - - - - - - - - ";
  ptr +=(int)EB;
  
  if(estado == "Encendido") {
    
      ptr +="<p><img src='http://pngimg.com/uploads/football_player/football_player_PNG128.png'><br>";
     
  } else {
    ptr +="<p><img src='https://c.tenor.com/NVfOOmB8PfsAAAAC/goool-gol.gif'><br>";

   
  
  }
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
