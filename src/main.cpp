#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 33     // Digital pin connected to the DHT sensor 
#define DHTTYPE DHT11 // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }


  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  // Mettre l'ESP32 en mode Deep Sleep pendant 5 secondes
  esp_sleep_enable_timer_wakeup(5000000); // 5 secondes en microsecondes
  esp_deep_sleep_start();
}

void loop() {
  // Cette fonction est maintenant vide car l'ESP32 se réveillera et recommencera à partir de setup()
}