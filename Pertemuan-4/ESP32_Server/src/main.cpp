//INI ESP32 YANG LAMA
#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <esp_err.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <ArduinoJson.h>
#include "class.h"
#include "espnow.h"

void setup() {
Serial.begin(115200);
Serial.print("Transmitter Init...");
WiFi.mode(WIFI_STA);
esp_now_register_recv_cb(OnDataRecv);
esp_now_register_send_cb(OnDataSent);
memcpy(peerInfo.peer_addr, mac_addresses, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Gagal menambahkan Peer");
    return;
  }


pinMode(led, OUTPUT);
digitalWrite(led,LOW);
}

void loop() {
readSerial r;
r;
}
