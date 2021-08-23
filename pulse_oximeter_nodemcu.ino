#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <MAX30100_PulseOximeter.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "n9oEI3NB9wYKHK5Vdk0SqLTqZcOYKS_t"; 
//Blynk Authentication Token 
 
/* WiFi credentials */
char ssid[] = "ciecie"; //Your WiFi SSID
char pass[] = "wikwikwik"; //Your WiFi Password
 
#define REPORTING_PERIOD_MS     3000

PulseOximeter pox;
uint32_t tsLastReport = 0;

void setup()
{
    Serial.begin(115200);
    Blynk.begin(auth, ssid, pass);
    Serial.print("Initializing pulse oximeter..");
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
        digitalWrite(1,HIGH);
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_24MA);
}
void loop()
{
  Blynk.run();
  pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        // to computer serial monitor
        Serial.print("BPM: ");
        Serial.print(pox.getHeartRate());
        Serial.print("    SpO2: ");
        Serial.print(pox.getSpO2());
        Serial.print("%");
        Serial.println("\n");
        Blynk.virtualWrite(V4,pox.getHeartRate() );
        Blynk.virtualWrite(V5,pox.getSpO2());
        tsLastReport = millis();
    }
}
