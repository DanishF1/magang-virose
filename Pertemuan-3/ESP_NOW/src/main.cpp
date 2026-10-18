#include "main.h"

esp_now_peer_info_t peer_info;

uint8_t inputSerial[6];

uint8_t mac_addresses[MAC_ADDRESS_TOTAL][MAC_ADDRESS_LENGTH] = {
    {0x08,0xA6,0xF7,0xBD,0x45,0x60},  // ESP DOIT
    {0x20,0x9B,0xA9,0x97,0x79,0x90},  // ESP 38 PIN
    {0x00,0x00,0x00,0x00,0x00,0x00},  // 2
    {0x00,0x00,0x00,0x00,0x00,0x00},  // 3
    {0x00,0x00,0x00,0x00,0x00,0x00},  // 4
    {0x00,0x00,0x00,0x00,0x00,0x00},  // 5
    {0x00,0x00,0x00,0x00,0x00,0x00},  // 6
    {0x00,0x00,0x00,0x00,0x00,0x00},  // 7
    {0x00,0x00,0x00,0x00,0x00,0x00},  // 8
    {0x00,0x00,0x00,0x00,0x00,0x00}   // 9
};

const char *mac_names[MAC_ADDRESS_TOTAL] = {
    "FARUQ",                               // 0
    "Danish Fattah Azizi",                 // 1
    "RAFAINA",                             // 2
    "FAUZAN",                              // 3
    "Marsya Safira",                       // 4
    "Faqih Al Minanji",                    // 5
    "Farid Azzam Arrayyan",                // 6
    "Kenzi Attabany",                      // 7
    "Nabila Fathania Rizqi Romadlon",      // 8
    "Felicia Metta Tania",                 // 9
};

esp_err_t mulai_esp_now(int index_mac_address) {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    /* Init ESP-NOW */
    esp_err_t result = esp_now_init();
    if (result != ESP_OK)
        return result;

    /* Set callback function to handle received data */
    result = esp_now_register_recv_cb(callback_data_esp_now);
    if (result != ESP_OK)
        return result;

    result = esp_now_register_send_cb(callback_pengiriman_esp_now);
    //     if (result != ESP_OK)
    //         return result;

    /* Set MAC Address */
    uint8_t mac[MAC_ADDRESS_LENGTH];
    memcpy(mac, mac_addresses[index_mac_address], MAC_ADDRESS_LENGTH);
    result = esp_wifi_set_mac(WIFI_IF_STA, mac);
    if (result != ESP_OK)
        return result;

    /* Initialize peer_info and set fields*/
    memset(&peer_info, 0, sizeof(esp_now_peer_info_t));
    peer_info.channel = 0;
    peer_info.encrypt = false;

    /* Add All MAC to peer list  */
    for (int i = 0; i < MAC_ADDRESS_TOTAL; i++) {
        memcpy(peer_info.peer_addr, mac_addresses[i], MAC_ADDRESS_LENGTH);
        result = esp_now_add_peer(&peer_info);
        if (result != ESP_OK)
            return result;
    }

    return ESP_OK;
}

int cari_mac_index(const uint8_t *mac) {
    for (int i = 0; i < MAC_ADDRESS_TOTAL; i++) {
        // Compare the MAC address
        if (memcmp(mac, mac_addresses[i], MAC_ADDRESS_LENGTH) == 0)
            return i;
    }

    // if not found return -1
    return -1;
}

String mac_index_to_names(int mac_index) {
    if ((mac_index < 0 || mac_index >= MAC_ADDRESS_TOTAL) || (mac_index == -1)) {
        return "Unknown";
    }
    return mac_names[mac_index];
}

void callback_data_esp_now(const uint8_t *mac, const uint8_t *data, int len) {
    int index_mac_asal = cari_mac_index(mac);
    process_perintah(data, len, index_mac_asal);
}
void callback_pengiriman_esp_now(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.printf("\nStatus pengiriman ESP-NOW: %s\n", esp_err_to_name(status));
}
void callback_data_serial(const uint8_t *data, int len) {
    process_perintah(data, len);
}
void baca_serial(void (*callback)(const uint8_t *data, int len)) {
    // TODO 2: implementasi kode buat nerima perintah dari serial
    while(Serial.available()){
        if(Serial.available() >= 6){
            Serial.readBytes(inputSerial, 6);
            uint8_t b1 = inputSerial[0];
            uint8_t b2 = inputSerial[1];
            uint8_t b3 = inputSerial[2];
            uint8_t b4 = inputSerial[3];
            uint8_t b5 = inputSerial[4];
            uint8_t b6 = inputSerial[5];
            if(b1 == 0xFF && b2 ==0xFF && b3 == 0X00 && b4 == 0x02){
                uint8_t payload[2] = {b5,b6};
                callback(payload, b4);

            }
           
        }
        
        }
    }

void process_perintah(const uint8_t *data, int len, int index_mac_address_asal) {
    // TODO 3: implementasi kode buat processing perintah
    if(index_mac_address_asal == -1){
        //SERIAL
        COMMAND c;
        switch (data[0]){
        case HALO:{
        String tujuan, namaku, payloadESPNOW; 
                if(data[1] == 0x01){
                    tujuan = mac_index_to_names(1);
                    namaku = mac_index_to_names(0);
                    payloadESPNOW = "HALO" + String(HALO) + ", Halo " + tujuan +" aku "+namaku;
                    esp_err_t result = esp_now_send(mac_addresses[0], (uint8_t *) payloadESPNOW.c_str(), payloadESPNOW.length() + 1);
                }else if (data[1]==0x02){
                    tujuan = mac_index_to_names(0);
                    namaku = mac_index_to_names(1);
                    payloadESPNOW = "HALO" + String(HALO) + ", Halo " + tujuan +" aku "+namaku;
                    esp_err_t result = esp_now_send(mac_addresses[1], (uint8_t *) payloadESPNOW.c_str(), payloadESPNOW.length() + 1);
                }
            break;}
        case CEK:{
            c = CEK;
            int x=0;int y=0;
        String tujuan, namaku;
        String payloadESPNOW;
                if(data[1] == 0x01){
                    tujuan = mac_index_to_names(1);
                    namaku = mac_index_to_names(0);
                    payloadESPNOW = "CEK" + String(CEK) + "(enum), "+ tujuan + " ini " + namaku +" apakah kamu di sana?";
                    esp_err_t result = esp_now_send(mac_addresses[0], (uint8_t *) payloadESPNOW.c_str(), payloadESPNOW.length() + 1);
                }else if (data[1]==0x02){
                    tujuan = mac_index_to_names(0);
                    namaku = mac_index_to_names(1);
                    payloadESPNOW = "CEK" + String(CEK) + "(enum), "+ tujuan + " ini " + namaku +" apakah kamu di sana?";
                    esp_err_t result = esp_now_send(mac_addresses[1], (uint8_t *) payloadESPNOW.c_str(), payloadESPNOW.length() + 1);
                }
            break;}
        default:
            break;
        }
    }else{
        String namaku;
        if(index_mac_address_asal == 1){
            namaku = mac_index_to_names(0);
        }else{
            namaku = mac_index_to_names(1);
        }
        String rx_str = String((char*)data);
        String namaPengirim = mac_index_to_names(index_mac_address_asal);
        String reply = "";
        if(rx_str.startsWith("H")){
            reply = "JAWAB(2), Halo juga " + namaPengirim + " Aku " + namaku;
            esp_err_t result = esp_now_send(mac_addresses[index_mac_address_asal], (uint8_t *) reply.c_str(), reply.length() + 1);
        }else if(rx_str.startsWith("J")){
            Serial.println(rx_str);
        }else if(rx_str.startsWith("C")){
            reply = "JAWAB(2), Iya aku " + namaPengirim + " Aku di sini " + namaku;
            esp_err_t result = esp_now_send(mac_addresses[index_mac_address_asal], (uint8_t *) reply.c_str(), reply.length() + 1);
        }else{
            Serial.println("Err, input unknown");
        }
        
        
    }
        



}