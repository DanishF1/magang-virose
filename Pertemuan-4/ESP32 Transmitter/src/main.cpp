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

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init gagal");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);

  memset(&peerInfo, 0, sizeof(peerInfo));   // bersihkan struct dulu
  memcpy(peerInfo.peer_addr, mac_addresses[0], 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  esp_err_t err = esp_now_add_peer(&peerInfo);
  if (err != ESP_OK) {
    Serial.print("Gagal menambahkan Peer, kode: ");
    Serial.println(esp_err_to_name(err));
    return;
  }

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
readSerial r;
r;
}
