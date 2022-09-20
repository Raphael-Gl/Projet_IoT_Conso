#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "Moimoimoimoimoimoi";
const char *password = "wifideraphael";

void sendTelegramMessage(char *message) {

    if ((WiFi.status() == WL_CONNECTED)) {
        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        char *url = "https://api.telegram.org/bot5647128476:AAHgpPJ625ZpgXkIayld5_qF4XiXBvTZVtM/sendMessage?chat_id=5288792176&text=";
        char *result;   // array to hold the result.
        strcpy(result,url); // copy string one into the result.
        strcat(result,message); // append string two to the result.
        http.begin(result);

        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode == HTTP_CODE_OK) {
            Serial.println("Request succesful");
        }
        else {
            Serial.printf("Failed : %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    }
}

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
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    sendTelegramMessage("Coucou");
    delay(10000);
}