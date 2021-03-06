#include <ESP8266WiFi.h>
#include <PubSubClient.h> // Connect and publish to the MQTT broker
#include "secrets.h"
#include "globals.h"


// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(MQTT_SERVER, 1883, wifiClient);

// Custom function to connet to the MQTT broker via WiFi
void connect_MQTT() {
  Serial.print("Connecting to ");
  Serial.println(SECRET_SSID);

  // Connect to the WiFi
  WiFi.begin(SECRET_SSID, SECRET_PASS);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  if (client.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }

}

void publishData() {
  // PUBLISH to the MQTT Broker (topic = Temperature, defined at the beginning)
    if (client.publish(MQTT_TEMPERATURE_TOPIC, String(temperature).c_str())) {
      Serial.println("Temperature sent!");
    }
    // Again, client.publish will return a boolean value depending on whether it succeeded or not.
    // If the message failed to send, we will try again, as the connection may have broken.
    else {
      Serial.println("Temperature failed to send. Reconnecting to MQTT Broker and trying again");
      client.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);
      delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
      client.publish(MQTT_TEMPERATURE_TOPIC, String(temperature).c_str());
    }

    // PUBLISH to the MQTT Broker (topic = Humidity, defined at the beginning)
    if (client.publish(MQTT_HUMIDITY_TOPIC, String(humidity).c_str())) {
      Serial.println("Humidity sent!");
    }
    // Again, client.publish will return a boolean value depending on whether it succeeded or not.
    // If the message failed to send, we will try again, as the connection may have broken.
    else {
      Serial.println("Humidity failed to send. Reconnecting to MQTT Broker and trying again");
      client.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);
      delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
      client.publish(MQTT_HUMIDITY_TOPIC, String(humidity).c_str());
    }

    // PUBLISH to the MQTT Broker (topic = Pressure, defined at the beginning)
    if (client.publish(MQTT_PRESSURE_TOPIC, String(pressure).c_str())) {
      Serial.println("Pressure sent!");
    }
    // Again, client.publish will return a boolean value depending on whether it succeeded or not.
    // If the message failed to send, we will try again, as the connection may have broken.
    else {
      Serial.println("Pressure failed to send. Reconnecting to MQTT Broker and trying again");
      client.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);
      delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
      client.publish(MQTT_PRESSURE_TOPIC, String(pressure).c_str());
    }

    Serial.println("Closing MQTT connection...");
    client.disconnect();
}
