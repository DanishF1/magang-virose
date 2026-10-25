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
const char* ssid = "Dan";
const char* pass = "12345678";

void setup() {
  Serial.begin(115200);
  Serial.println("Transmitter Init...");

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  // 1. WiFi dulu, tunggu sampai terhubung
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  unsigned long t = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t < 15000) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi OK, channel: ");
    Serial.println(WiFi.channel());
  } else {
    Serial.println("WiFi GAGAL terhubung");
  }
  Serial.print("MAC ESP lama: ");
  Serial.println(WiFi.macAddress());

  // 2. ESP-NOW setelah channel pasti
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init gagal");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);

  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, mac_addresses[0], 6);
  peerInfo.channel = 0;      // 0 = pakai channel saat ini
  peerInfo.encrypt = false;

  esp_err_t err = esp_now_add_peer(&peerInfo);
  if (err != ESP_OK) {
    Serial.print("Gagal add peer: ");
    Serial.println(esp_err_to_name(err));
    return;
  }
  Serial.println("Siap.");
}

void loop() {
readSerial r;
r;
}
