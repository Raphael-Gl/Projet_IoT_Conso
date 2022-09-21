#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#define BME_SCK 14  // Connect "SCL" pin on the BME680 with GPIO 14 on the ESP32
#define BME_MISO 12 // Connect "SDO" pin on the BME680 with GPIO 12 on the ESP32
#define BME_MOSI 13 // Connect "SDA" pin on the BME680 with GPIO 13 on the ESP32
#define BME_CS 15   // Connect "CS"  pin on the BME680 with GPIO 15 on the ESP32
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);



const int sensorPin = 36;
int lum = 0;
// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 4095;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value




void setup() {

  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("BME680 test"));
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }
  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);

  Serial.begin(115200);
  delay(1000);

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  while (millis() < 10000) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }
  
  digitalWrite(2, LOW);


}

void loop() {
  // put your main code here, to run repeatedly:
 if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");

  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  sensorValue = analogRead(sensorPin);

  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, sensorMin, sensorMax);

  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

  // put your main code here, to run repeatedly:
  //lum = analogRead(sensorPin);
  Serial.println("Luminosity = ");
  Serial.print(sensorValue);
  
  delay(1000);


}
