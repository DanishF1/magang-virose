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
// GMT+7 (WIB) = 7 * 3600 = 25200 detik offset
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200);
String jamskr = "";

void setup() {
Serial.begin(115200);
Serial.print("Transmitter Init...");
WiFi.begin(ssid, pass);
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
  
    if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("Failed to initialize EEPROM");
    return;
    }
pinMode(led, OUTPUT);
digitalWrite(led,LOW);
timeClient.begin();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid,pass);
  }
  timeClient.update();
  jamskr = timeClient.getFormattedTime();

readSerial r;
r;
}
