#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

const char *ssid = "Moimoimoimoimoimoi";
const char *password = "wifideraphael";

#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883 // use 8883 for SSL

#define AIO_USERNAME  "Raphael_IoT"
#define AIO_KEY       "aio_pOan511OPzui0b9ZYwfRFDmalnAU"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish topic = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Projet_IoT");

void MQTT_connect();
void MQTT_publish(float payload);

void setup() {
    Serial.begin(9600);
    delay(10);

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");

}


void loop()
{
  float a=3.14;
    MQTT_publish(a);
    delay(10000);
    
}
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
    int8_t ret;
    // Stop if already connected.
    if (mqtt.connected()) {
        return;
    }
    Serial.print("Connecting to MQTT... ");
    uint8_t retries = 3;
    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
        Serial.println(mqtt.connectErrorString(ret));
        Serial.println("Retrying MQTT connection in 5 seconds...");
        mqtt.disconnect();
        delay(5000); // wait 5 seconds
        retries--;
        if (retries == 0) {
            // basically die and wait for WDT to reset me
            while (1)
                ;
        }
    }
    Serial.println("MQTT Connected!");
}

void MQTT_publish(float payload) {
  
  MQTT_connect();
  // Now we can publish stuff!
  Serial.println(F("\nSending payload"));
  topic.publish(payload);

}