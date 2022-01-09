#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

String SerialMessage; // for incoming serial data
int max_string_size = 50000;

const char *ssid = "status_relee";
const char *password = "homita2022";

ESP8266WebServer server(80);

/* Go to http://192.168.4.1 in a web browser connected to this access point to see it.*/
void handleRoot() {
  server.send(200, "text/html", "<a href=\"http://192.168.4.1\">HOME</a></br><a href=\"http://192.168.4.1\\sendSerial?message=START_R1\">START_R1</a></br><a href=\"http://192.168.4.1\\sendSerial?message=START_R2\">START_R2</a></br>"
                                + SerialMessage);
}

void sendSerial() {
  Serial.print(server.arg("message"));
  server.send(200, "text/html", "<a href=\"http://192.168.4.1\">HOME</a></br><a href=\"http://192.168.4.1\\sendSerial?message=START_R1\">START_R1</a></br><a href=\"http://192.168.4.1\\sendSerial?message=START_R2\">START_R2</a></br>MESSAGE SENT </br>"
                                + server.arg("message") + "</br>" + SerialMessage);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/sendSerial", sendSerial);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming string:
    SerialMessage += "</br>";
    SerialMessage += Serial.readString();
    if (SerialMessage.length() > max_string_size) {
      SerialMessage.remove(0, SerialMessage.length()-max_string_size);
      }
//    Serial.println(SerialMessage);
  }
}