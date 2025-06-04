#define BLYNK_TEMPLATE_ID "TMPL3JjUH_RNl"

#define BLYNK_TEMPLATE_NAME "Plant Monitor"

#define BLYNK_AUTH_TOKEN "dv-K90HRpARYaqL_4EFNg8ovxKQbcZyT"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "IoTSpark";         // Replace with your WiFi SSID
char pass[] = "12345678";     // Replace with your WiFi Password  

#define SOIL_MOISTURE_PIN 34   
#define DRY_VALUE 3000         
#define WET_VALUE 1200         

BlynkTimer timer;

void sendSoilMoisture() {
    int sensorValue = analogRead(SOIL_MOISTURE_PIN);
    int moisturePercent = map(sensorValue, DRY_VALUE, WET_VALUE, 0, 100);
    moisturePercent = constrain(moisturePercent, 0, 100);  

    


   // Determine soil status
    String soilStatus;
    if (moisturePercent < 30) {
        soilStatus = "Dry";
    } else if (moisturePercent >= 30 && moisturePercent <= 60) {
        soilStatus = "Moist";
    } else {
        soilStatus = "Wet";
    }

    Serial.print("Soil Moisture: ");
    Serial.print(moisturePercent);
    Serial.print("% - Status: ");
    Serial.println(soilStatus);

    Blynk.virtualWrite(V0, moisturePercent);  // Send moisture value
    Blynk.virtualWrite(V4, soilStatus);       // Send soil status message
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    timer.setInterval(2000L, sendSoilMoisture);
}

void loop() {
    Blynk.run();
    timer.run();
}
