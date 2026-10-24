#ifndef class_h
#define class_h

extern uint8_t mac_addresses[1][6];
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

class sendToServer{
private:
JsonDocument j;
public:
sendToServer(String message){
  send(message);
}

void send(String message){
  int len = message.length();
  String leng;
  if(len>9 && len<100){
    leng = String(len);
  }else if(len>0 && len<10){
    leng = "0"+String(len);
  }else{
    leng = "00";
  }
  String payload = "FFFF02035352564C3031"+leng+message;
  uint8_t result = esp_now_send(mac_addresses[0], (uint8_t*)payload.c_str(), payload.length());

}
};

#endif