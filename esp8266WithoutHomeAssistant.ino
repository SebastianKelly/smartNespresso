////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////// Skelectronics Coffee Machine ////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password ="YOUR_WIFI_PASSWORD";

int switchingPin = D8;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(switchingPin, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.begin();
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  delay(3000);

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request


  if (request.indexOf("/coffeeMachine") > 0)  {
     digitalWrite(switchingPin, 1);
     delay(500);
     digitalWrite(switchingPin, 0);
     delay(500);
     digitalWrite(switchingPin, 1);
     delay(500);
     digitalWrite(switchingPin, 0);
  }
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
  client.println("</head>");
  client.println("<body bgcolor = \"#ff6666\">");
  client.println("<hr/><hr>");
  client.println("<h4 style='font-size:250%'><center> Coffee Machine Controlling Website Ay </center></h4>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("Nespresso");
  client.println("<a href=\"/coffeeMachine\"\"><button>Turn On </button></a>");
  client.println("</center>");
  client.println("</body>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
