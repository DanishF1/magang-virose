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
  digitalWrite(led, HIGH);
  delay(600);
  digitalWrite(led, LOW);
}


void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  readSerial r;
  sendToBridge s;
  payloadEN = dataTerima.pesan;
  memcpy(&dataTerima, incomingData, sizeof(dataTerima));
  String pesan = dataTerima.pesan;
  String header = pesan.substring(0, 4);;
  String source = pesan.substring(4, 6);
  String destination = pesan.substring(6, 8);
  String token = pesan.substring(8, 20);
  String leng = pesan.substring(20, 22);
  int lenInt = leng.toInt();
  String payload = pesan.substring(22, pesan.length());
  String payloadHex = r.hexToStringESP(dataTerima.pesan);
  String payloadToSerial = token + payloadHex;
  if(header == "FFFF" && token == "5352564C3031" && lenInt<100 && source.toInt() == 3){
    Serial.println(payloadToSerial);
  }
  
  
  if(payload.substring(0,31) == "7b22616374696f6e223a2263656b22"){
    //cek
    deserializeJson(j, payloadHex);
    int antrian = j["id"];
    s.cekAntrean(antrian);
  }else if(payload.substring(0,37) == "7b22616374696f6e223a22616a756b616e22"){
    //ajukan
    nomorAntrean += 1;
    address +=2;
    addressTime +=2;
    s.antrean();
  }else if(payload.substring(0,34) == "7b22616374696f6e223a22747261636b22"){
    //track
    deserializeJson(j, payloadHex);
    int antrian = j["id"];
    s.trackjam(antrian+1);
  }else if(payload.substring(0,34) == "7b22616374696f6e223a22616d62696c22"){
    //ambil
    deserializeJson(j, payloadHex);
    int antrian = j["id"];
    s.trackjam(antrian);
  }

  //7b22616374696f6e223a22747261636b22
}

#endif