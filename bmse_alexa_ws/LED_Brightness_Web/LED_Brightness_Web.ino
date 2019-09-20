#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "Skete";  // Enter SSID here
const char* password = "asdfghjkl";  //Enter Password here

ESP8266WebServer server(80);

// LED 
uint8_t LEDPin = D4;              

String value = "0";
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  //pinMode(LEDPin, OUTPUT);

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
  if(server.arg(0) != ""){ 
    int brightness = map(server.arg(0).toInt(), 0, 100, 0, 1023);
    analogWrite(LEDPin, (1023-brightness));
    value = server.arg(0);
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
  ptr +="<title>ESP8266 LED Brightness Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<a href=\"http://www.modelicon.in\"><img src=\"http://www.modelicon.in/wp-content/uploads/2017/07/biglogo4.png\" width=\"350\" height=\"125\" title=\"modelicon\" alt=\"logo\"></a>";
  ptr +="<h1>ESP8266 LED Brightness Control</h1>\n";
  
  ptr += "<div class=\"slidecontainer\">\n";
  ptr += "<input type=\"range\" min=\"0\" max=\"100\" value=\"";
  ptr += val;
  ptr += "\" class=\"slider\" id=\"myRange\" value=\"document.getElementById('demo').innerHTML = this.value\" oninput=\"document.getElementById('demo').innerHTML = this.value\">\n";
  ptr += "<p>Brightness%: <span id=\"demo\"></span></p>\n";
  ptr += "<p><input type=\"submit\" value=\"Set_Brightness\" onclick=\"myfunc()\" /></p>";
  ptr += "</div>";

  ptr += "<script>\n";
  ptr += "function myfunc() {\n";
  ptr += "var fp = document.getElementById('demo').innerHTML\n";
  ptr += "window.location.replace('?a=' + fp)\n"; //window.location.href + 
  ptr += "}</script>";
  
  ptr +="<p>Status: LED is ";
  ptr +=val;
  ptr +="% bright</p>";
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
