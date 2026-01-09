#include "WifiManager.h"


bool connectToWifi(const char* ssid, const char* password, Adafruit_SH110X &display){
    Serial.print("Connecting to wifi network");
    
    WiFi.begin(ssid, password);
    unsigned long startTimestamp = millis();

    while(WiFi.status() != WL_CONNECTED && millis() - startTimestamp < 5000){
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED){
        Serial.println("\n Wifi Connected");
        return true;
    } else {
        Serial.println("\n WiFi Connection Failed");
        return false;
    }
}


bool isWiFiConnected() {
    return WiFi.status() == WL_CONNECTED;
}