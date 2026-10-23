//INI ESP32 YANG LAMA
#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <esp_err.h>
#include <esp_now.h>
#include <esp_wifi.h>

class readSerial{
  public:
  String commandUser[13] = {
    "cek", "order", "help", "status", "token", "send", "quit", "exit", "daftar",
    "ajukan", "servis", "track", "ambil"
  };

  String hexToStringESP(String hexInput) {
  String output = "";
  for (int i = 0; i < hexInput.length(); i += 2) {
    String byteString = hexInput.substring(i, i + 2);
    char byteVal = (char) strtol(byteString.c_str(), NULL, 16);
    output += byteVal;
  }
  
  return output;
}

  readSerial(){
    if(!Serial.available()){
      return;
    }else{
      readCom();
    }
  }

  void readCom(){
    String inputSerial = Serial.readStringUntil('\n');
    String input = hexToStringESP(String(inputSerial));
    Serial.println(input);
  }

  ~readSerial(){
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
readSerial r;
r;
}
