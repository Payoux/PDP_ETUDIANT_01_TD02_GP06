// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

// Define the pins that we will use
#define DHTPIN 33
#define LED 26
#define DHTTYPE DHT11

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG,0);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  dht.begin();
}

void loop() {
  // Attendre 5 secondes entre les mesures


  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();


  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Afficher l'humidité et la température
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  esp_sleep_enable_timer_wakeup(5000000);
  Serial.flush();
  delay(20);
  esp_deep_sleep_start();
}