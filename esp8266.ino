


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////// Skelectronics Coffee Machine ////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
const char* ssid = "YOUR_WIFI_NAME";
const char* password ="YOUR_WIFI_PASSWORD";

#define mqtt_topic "dev/coffeeMachine"
#define mqtt_server "YOUR_MQTT_SERVER_IP_ADDRESS"
#define mqtt_user "YOUR_MQTT_USERNAME"
#define mqtt_password "YOUR_MQTT_PASSWORD"


WiFiClient espClient;
PubSubClient client(espClient);


String strTopic;
String strPayload;
int switchingPin = D8;



void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); 
  }
  Serial.println("WiFi connected");
  delay(500);
}

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  strTopic = String((char*)topic);
  if(strTopic == mqtt_topic)
    {
    strPayload = String((char*)payload);
    if(strPayload == "onn")
      {
        Serial.println(strPayload);
        digitalWrite(switchingPin, 1);
        delay(500);
        digitalWrite(switchingPin, 0);
        delay(500);
        digitalWrite(switchingPin, 1);
        delay(500);
        digitalWrite(switchingPin, 0);
        client.publish(mqtt_topic, String("done").c_str(), true);
      }
    }
}
 
 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("CoffeeClient", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
 
void setup()
{
  pinMode(D8, OUTPUT);
  Serial.begin(9600);
  setup_wifi(); 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
 
void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
