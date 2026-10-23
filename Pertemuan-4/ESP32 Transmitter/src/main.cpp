//INI ESP32 YANG LAMA
#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <esp_err.h>
#include <esp_now.h>
#include <esp_wifi.h>

class readSerial{
  public:
  String command[5] = {"cek", "order", "help", "status"};
  
  readSerial(){
    if(!Serial.available()){
      return;
    }else{
      readCom();
    }
  }

  void readCom(){
    Serial.println("Input keluhanmu");
    uint8_t inputSerial = Serial.read();

  }

  ~readSerial(){
    Serial.print("Sending request...");
  }

};
#define led 2
uint8_t mac_addresses[1][6] = {
    {0x20,0x9B,0xA9,0x97,0x79,0x90}  // ESP 32 SERVER
};

void setup() {
Serial.begin(115200);
Serial.print("Transmitter Init...");
pinMode(led, OUTPUT);
digitalWrite(led,LOW);
}

void loop() {

}
