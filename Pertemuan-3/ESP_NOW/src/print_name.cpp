#include "main.h"

int mik = -1; // Variabel global untuk menampung MAC Index

void readMacAddress() {
    uint8_t baseMac[6];
    esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
    
    if (ret == ESP_OK) {
        Serial.printf("MAC Hardware: %02X:%02X:%02X:%02X:%02X:%02X\n",
                      baseMac[0], baseMac[1], baseMac[2],
                      baseMac[3], baseMac[4], baseMac[5]);

        int hasil_cari = cari_mac_index(baseMac);

        if (hasil_cari != -1) {
            mik = hasil_cari; 
        } else {
            mik = 0; 
            Serial.println("MAC tidak terdaftar di array, default ke 0");
        }
    } else {
        Serial.println("Failed to read MAC address");
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Menyalakan ESP-NOW");
    WiFi.mode(WIFI_STA);
    
    readMacAddress();
    mulai_esp_now(mik);

    Serial.println("Halo, namaku " + mac_index_to_names(mik));
}

void loop() {
    baca_serial(callback_data_serial);
}