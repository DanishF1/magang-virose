#ifndef espnow_h
#define espnow_h
#include "class.h"
//ESPNOW
#define led 2
#include <ArduinoJson.h>
int nomorAntrean = 0;
int address = 0;        
int addressTime = 1;    
String payloadEN;
uint8_t mac_addresses[1][6] = {
    {0x08,0xA6,0xF7,0xBD,0x45,0x60}  // ESP 32 SERVER
};
esp_now_peer_info_t peerInfo;
struct data{
  char pesan[250];
  int id;

};
data dataTerima;
data dataKirim;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  sendToBridge s;
  Serial.println("MENGIRIM");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "SEND OK" : "SEND FAIL");
}


void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  readSerial r;
  sendToBridge s;
  payloadEN = dataTerima.pesan;
  Serial.println("DATA DITERIMA");
  Serial.println(dataTerima.pesan);
  memset(&dataTerima, 0, sizeof(dataTerima));                                      
  memcpy(&dataTerima, incomingData, min(len, (int)sizeof(dataTerima.pesan) - 1));    
  String pesan = dataTerima.pesan;
  if(pesan.length() < 22) return;    
  String header = pesan.substring(0, 4);;
  String source = pesan.substring(4, 6);
  String destination = pesan.substring(6, 8);
  String token = pesan.substring(8, 20);
  String leng = pesan.substring(20, 22);
  int lenInt = leng.toInt();
  String payload = pesan.substring(22, pesan.length());
  String payloadHex = r.hexToStringESP(payload); 


  if(header == "FFFF" && token == "5352564C3031" && lenInt<100){
      Serial.println("INPUT VALID");
  Serial.print("payload hex  : "); Serial.println(payload);
  Serial.print("payload json : "); Serial.println(payloadHex);

  JsonDocument doc;   // lokal, jangan pakai j global
  DeserializationError e = deserializeJson(doc, payloadHex);
  if(e){
    Serial.print("E05"); Serial.println(e.c_str());
    s.send("E05");
    return;
  }
  String action = doc["action"] | "";
  if(action == ""){
    s.send("E07");
  }
  int antrian = doc["id"] | 0;
  Serial.print("action = "); Serial.println(action);

  if(action == "cek"){
    s.cekAntrean(antrian);
  }else if(action == "ajukan"){
    nomorAntrean += 1;
    address += 2;
    addressTime += 2;
    s.antrean();
  }else if(action == "track"){
    s.trackjam(antrian + 1);
  }else if(action == "ambil"){
    s.ambilAntrean(antrian);
  }else{
    Serial.println("E06");
  }
  }else if(token != "5352564C3031"){
    s.send("E01");
  }else if(header != "FFFF"){
    s.send("E02");
  }else if(lenInt>100){
    s.send("E03");
  }else{
    s.send("E06");
  }
  //7b22616374696f6e223a22747261636b22
}

#endif