//INI ESP32 YANG BARU
#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <esp_err.h>
#include <ArduinoJson.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "class.h"
#include "espnow.h"
#define EEPROM_SIZE 512

const char* ssid = "Dan";
const char* pass = "12345678";

WiFiUDP ntpUDP;
// GMT+7 (WIB) = 7 * 3600 = 25200 detik
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200);
String jamskr = "";
unsigned long ledOffAt = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Transmitter Init...");

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("Failed to initialize EEPROM");
    return;
  }

  // 1. WiFi dulu, tunggu terhubung agar channel sudah pasti
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  unsigned long t = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t < 10000) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi OK, channel: ");
    Serial.println(WiFi.channel());  
  } else {
    Serial.println("WiFi belum terhubung (akan dicoba lagi di loop)");
  }
  Serial.print("MAC ESP ini: ");
  Serial.println(WiFi.macAddress());

  timeClient.begin();

  // 2. ESP-NOW
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
    Serial.print("Gagal menambahkan Peer: ");
    Serial.println(esp_err_to_name(err));
    return;
  }
  Serial.println("Siap.");
}

void loop() {
  static unsigned long lastReconnect = 0;

  if (WiFi.status() == WL_CONNECTED) {
    timeClient.update();
    if (timeClient.isTimeSet()) {
      jamskr = timeClient.getFormattedTime();
    }
  } else if (millis() - lastReconnect > 10000) {   // jangan spam WiFi.begin
    lastReconnect = millis();
    WiFi.reconnect();
  }


  readSerial r;
}