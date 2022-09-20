#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>


const char *ssid = "Moimoimoimoimoimoi";
const char *password = "wifideraphael";

void sendTelegramMessage(char *message) {

    if ((WiFi.status() == WL_CONNECTED)) {
        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        char *url = "https://api.telegram.org/bot5647128476:AAHgpPJ625ZpgXkIayld5_qF4XiXBvTZVtM/sendMessage?chat_id=5288792176&text=";
        char buf[strlen(url)+strlen(message)];
        strcpy(buf,url);
        strcat(buf,message);
        http.begin(buf);

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

void loop() {
    sendTelegramMessage("Bien le bonsoir");
    Serial.println("Fini d'envoyer");
    delay(10000);
}