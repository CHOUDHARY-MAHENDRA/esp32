#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "vivo Y100A";
const char* password ="zxcvbnm12";

WebServer server(80);

const int ledPin = 2;

void setup(){
Serial.begin(115200);
pinMode(ledPin,OUTPUT);

digitalWrite(ledPin,LOW);

WiFi.begin(ssid, password);
while (WiFi.status()!=WL_CONNECTED){
  delay(1000);
  Serial.println("coonecting to wifi ....");
}
Serial.println("esp32 is connect to wifi ");
Serial.print("ip Address :");
Serial.println(WiFi.localIP());

server.on("/led/on", [](){
  digitalWrite(ledPin,HIGH);
  server.send(200,"text/plain","LED is ON");

});

server.on("/led/off",[]() {
  digitalWrite(ledPin,LOW);
  server.send(200,"text/plain","LED IS OFF");
});
  server.begin();
  Serial.printf("Server is started");
}
void loop(){
  server.handleClient();
}


