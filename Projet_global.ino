#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define DELAI 15000
 
#define PIN_BRIGHTNESS 36
#define PIN_LED 4
#define PIN_BOUTON 15

#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883 // use 8883 for SSL
#define AIO_USERNAME  "Raphael_IoT"
#define AIO_KEY       "aio_Kjfo66aC1wfVB2s99gSWqE6eUSs2"

float temp, humid, lumi = 0;
float seuilTemp=27.0;
float seuilhumid=57.0;
float seuilLumi=4000.0; 

const char *ssid = "Moimoimoimoimoimoi";
const char *password = "wifideraphael";

Adafruit_BME680 bme; // I2C

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Projet_IoT_temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Projet_IoT_humidity");
Adafruit_MQTT_Publish brightness = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Projet_IoT_brightness");

void MQTT_connect();
void MQTT_publish(float temp, float humid, float bright);
void LED_Blink();
void sendTelegramMessage(char *message);

void setup() {
  pinMode(PIN_BRIGHTNESS,INPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BOUTON, INPUT_PULLDOWN);
  Serial.begin(9600);
  while (!Serial);

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  Serial.println("En attente de l'appui du bouton");
  while(!digitalRead(PIN_BOUTON));
  Serial.println("Bouton appuye, debut du programme"); 
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  int time=0;
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
}

/*------------------loop------------------*/
void loop() {
    if (! bme.performReading()) {
        Serial.println("Failed to perform reading :(");
        return;
    }
    //Récupération des données des capteurs 
    temp=bme.temperature;
    humid=bme.humidity;
    lumi=analogRead(PIN_BRIGHTNESS); //faire le calcul pour déterminer la valeur en lux

    MQTT_publish(temp,humid,lumi);
    LED_Blink();
    
    //Test des seuils
    if (temp>seuilTemp)
        sendTelegramMessage("ALERTE : La température est trop élevée.");
    if (humid>seuilhumid)
        sendTelegramMessage("ALERTE : L'humidité est trop élevée.");
    if (lumi>seuilLumi)
        sendTelegramMessage("ALERTE : La luminosité est trop élevée.");
    
    delay(DELAI);
}



/*---------------functions----------------*/

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

void MQTT_publish(float temp, float humid, float bright) {
  
    MQTT_connect();
    // Now we can publish stuff!
    Serial.println(F("\nSending payload"));
    temperature.publish(temp);
    humidity.publish(humid);
    brightness.publish(bright);
}

void LED_Blink() {
  digitalWrite(PIN_LED,HIGH);
  delay(50);
  digitalWrite(PIN_LED,LOW);
}

void sendTelegramMessage(char *message) {
    if ((WiFi.status() == WL_CONNECTED)) {
        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        char *url = "https://api.telegram.org/bot5647128476:AAHgpPJ625ZpgXkIayld5_qF4XiXBvTZVtM/sendMessage?chat_id=5288792176&text=";
        char urlcomplete[strlen(url)+strlen(message)];
        strcpy(urlcomplete, url);
        strcat(urlcomplete,message);
        http.begin(urlcomplete);

        // start connection and send HTTP header
        int httpCode = http.GET();
        // httpCode will be negative on error
        if (httpCode == HTTP_CODE_OK) {
            Serial.println("Request succesfull");
        }
        else {
            Serial.printf("Failed : %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    }
}