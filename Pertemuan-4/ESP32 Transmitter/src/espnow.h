#ifndef espnow_h
#define espnow_h
//ESPNOW
#define led 2

uint8_t mac_addresses[1][6] = {

};

struct data{

};

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {

}


void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  
}

#endif espnow_h