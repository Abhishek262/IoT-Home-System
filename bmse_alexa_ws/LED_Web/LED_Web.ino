#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "PHASESHIFT2.4";  // Enter SSID here
const char* password = "phaseshift2019";  //Enter Password here

ESP8266WebServer server(80);

// LED 
uint8_t LEDPin = D4;              

String value = "";
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(LEDPin, OUTPUT);

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
  
  server.handleClient();
  
}

void handle_OnConnect() {
  if (server.arg(0)[0] == '0') {
    digitalWrite(LEDPin, HIGH);
    value = "<font color=\"red\" size=\"20\">OFF</font>";
    }

  else {
    digitalWrite(LEDPin, LOW);
    value = "<font color=\"lime\" size=\"20\">ON</font>";
    }
    
  server.send(200, "text/html", SendHTML(value)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(String val){
  String ptr = "";
  ptr += "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP8266 LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<a href=\"http://www.modelicon.in\"><img src=\"http://www.modelicon.in/wp-content/uploads/2017/07/biglogo4.png\" width=\"300\" height=\"125\" title=\"modelicon\" alt=\"logo\"></a>";
  ptr +="<h1>ESP8266 LED Control</h1>\n";

  ptr += "<h2><a href='?a=1'/><button style='margin-right:20px'>LED_ON</button></a><a href='?a=0'/><button>LED_OFF</button></a></h2>";
  
  ptr +="<p>Status: LED is ";
  ptr +=val;
  ptr +="</p>";
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
