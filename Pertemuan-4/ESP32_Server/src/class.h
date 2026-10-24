#ifndef class_h
#define class_h
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>
#include <esp_err.h>
extern int nomorAntrean;
extern uint8_t mac_addresses[1][6];
extern int address;
extern int addressTime;
extern String jamskr;
JsonDocument j;
extern String payloadEN;

class readSerial{
  public:
  readSerial(){
    if(!Serial.available()){
      return;
    }else{
      readCom();
    }
  }

  static String hexToStringESP(String hexInput) {
  String output = "";
  for (int i = 0; i < hexInput.length(); i += 2) {
    String byteString = hexInput.substring(i, i + 2);
    char byteVal = (char) strtol(byteString.c_str(), NULL, 16);
    output += byteVal;
  }
  
  return output;
}

  void readCom(){
    String inputSerial = Serial.readStringUntil('\n');
    String input = hexToStringESP(String(inputSerial));
    Serial.println(inputSerial);

  }

  ~readSerial(){
  }

};

class sendToBridge{
public:
JsonDocument j;
sendToBridge(){}

String stringToHex(const String &input) {
    String hexOutput = "";
    hexOutput.reserve(input.length() * 2); 

    char buf[3];
    for (size_t i = 0; i < input.length(); i++) {
        snprintf(buf, sizeof(buf), "%02X", (unsigned char)input[i]);
        hexOutput += buf;
    }
    return hexOutput;
}

void antrean(){
  EEPROM.write(address, nomorAntrean);
  EEPROM.writeString(addressTime, jamskr);
  EEPROM.commit();

}

void cekAntrean(int nomorAntrean){
String jsonOutput;
int bufferAntre;
EEPROM.get(nomorAntrean, bufferAntre);
if(bufferAntre == -1){
  j["action"] = "cek";
  j["bisa_diambil"] = false;
  serializeJson(j, jsonOutput);
  jsonOutput = stringToHex(jsonOutput);
  payloading(stringToHex(jsonOutput));
}else{
  j["action"] = "cek";
  j["bisa_diambil"] = true;
  serializeJson(j, jsonOutput);
  jsonOutput = stringToHex(jsonOutput);
  payloading(stringToHex(jsonOutput));
}
}


void ambilAntrean(int nomerAntrean){
String jsonOutput;
String bufferJam;
int bufferAntrean;
EEPROM.get(nomorAntrean, bufferAntrean);
EEPROM.get(nomorAntrean + 1, bufferJam);
int Jam0 = bufferJam.substring(0,2).toInt();
int Menit0 = bufferJam.substring(3,5).toInt();
int Detik0 = bufferJam.substring(6,8).toInt();
Menit0 += Jam0*60;

int Jam1 = jamskr.substring(0,2).toInt();
int Menit1 = jamskr.substring(3,5).toInt();
int Detik1 = jamskr.substring(6,8).toInt();
Menit1 += Jam1*60;

if(Menit1 - Menit0 > 2 && bufferAntrean != -1){
  EEPROM.write(nomorAntrean, -1);
  EEPROM.commit();
  j["action"] = "track";
  j["bisa_diambil"] = true;
  serializeJson(j, jsonOutput);
  jsonOutput = stringToHex(jsonOutput);
  payloading(stringToHex(jsonOutput));
  EEPROM.write(nomorAntrean, -1);
  EEPROM.commit();
}else{
  j["action"] = "track";
  j["bisa_diambil"] = false;
  serializeJson(j, jsonOutput);
  jsonOutput = stringToHex(jsonOutput);
  payloading(stringToHex(jsonOutput));
}
}
//HH:MM:SS
void trackjam(int nomorJam){
String jsonOutput;
String bufferJam;
int bufferAntrean;
EEPROM.get(nomorJam-1, bufferAntrean);
EEPROM.get(nomorJam, bufferJam);
int Jam0 = bufferJam.substring(0,2).toInt();
int Menit0 = bufferJam.substring(3,5).toInt();
int Detik0 = bufferJam.substring(6,8).toInt();
Menit0 += Jam0*60;

int Jam1 = jamskr.substring(0,2).toInt();
int Menit1 = jamskr.substring(3,5).toInt();
int Detik1 = jamskr.substring(6,8).toInt();
Menit1 += Jam1*60;

if(Menit1 - Menit0 > 2 && bufferAntrean != -1){
  j["action"] = "track";
  j["bisa_diambil"] = true;
  serializeJson(j, jsonOutput);
  jsonOutput = stringToHex(jsonOutput);
  payloading(stringToHex(jsonOutput));
}else{
    j["action"] = "track";
  j["bisa_diambil"] = false;
  serializeJson(j, jsonOutput);
  jsonOutput = stringToHex(jsonOutput);
  payloading(stringToHex(jsonOutput));
}
}

void payloading(String message){
  String finalPayload;
  int len = message.length();
  String leng;
  if(len>9 && len<100){
    leng = String(len);
  }else if(len>0 && len<10){
    leng = "0"+String(len);
  }else{
    leng = "00";
  }
  String payload = "FFFF03025352564C3031"+leng+message;
String bawaan = "";
send(finalPayload);

}

void payloading(String message, int nomorAntrean, bool bisaDiambil=false){
  String finalPayload;
  int len = message.length();
  String leng;
  if(len>9 && len<100){
    leng = String(len);
  }else if(len>0 && len<10){
    leng = "0"+String(len);
  }else{
    leng = "00";
  }
  String payload = "FFFF03025352564C3031"+leng+message;
String bawaan = "";
send(finalPayload);

}

void send(String message){

  uint8_t result = esp_now_send(mac_addresses[0], (uint8_t*)message.c_str(), message.length());

}

~sendToBridge(){}
};



#endif