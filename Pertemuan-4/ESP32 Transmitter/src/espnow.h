#ifndef espnow_h
#define espnow_h
#include "class.h"
//ESPNOW
#define led 2

uint8_t mac_addresses[1][6] = {
    {0x20,0x9B,0xA9,0x97,0x79,0x90}  // ESP 32 SERVER
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
  
}

#endif