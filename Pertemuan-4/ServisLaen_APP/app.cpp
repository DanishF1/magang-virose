#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "json.hpp"
nlohmann::json j;
using namespace std;
string inputUser;
string token = "5352564C3031"; //put di .env
bool ketemu = false;
string stringToHex(const string& input) {
    stringstream ss;
    for (unsigned char c : input) {
        ss << hex << uppercase << setw(2) << setfill('0') << (int)c;
    }
    return ss.str();
}

void sendKebridge(string dataHex){
string port = "/dev/ttyUSB0";

    string configCmd = "stty -F " + port + " 115200 raw -echo";
    system(configCmd.c_str());

    fstream serial(port, ios::in | ios::out);
    if (!serial.is_open()) {
        cout << "[Error] ESP32 tidak terdeteksi di " << port << endl;
        return;
    }
    cout<<dataHex<<endl;
    cout<<stringToHex(dataHex)<<endl;
    serial << stringToHex(dataHex);
    serial.flush();

    string respon;
    if (getline(serial, respon)) {
        cout << "Respon ESP32: " << respon << endl;
    }
}
void tampilkanMenu(){
    cout << " 1. help / daftar   : Menampilkan daftar perintah ini" << endl; //DONE
    cout << " 2. status          : Memeriksa koneksi Serial ke ESP-Bridge" << endl; //DONE
    cout << " 3. token           : Mengecek / mengatur Token 6-byte" << endl; //DONE
    cout << " 4. ajukan          : Mengajukan perbaikan perangkat baru" << endl; //DONE
    cout << " 5. cek             : Memeriksa status pengerjaan tiket" << endl; //DONE
    cout << " 6. ambil           : Mengonfirmasi pengambilan perangkat" << endl;//DONE
    cout << " 7. send            : Mengirim perintah manual ke sistem" << endl; 
    cout << " 8. track           : Mengirim perintah pengecekan atau tracking pesanan" << endl; //DONE
    cout << " 9. exit / quit     : Keluar dari program" << endl; //DONE
}

void status(){
    string port = "/dev/ttyUSB0";

    string configCmd = "stty -F " + port + " 115200 raw -echo";
    system(configCmd.c_str());

    fstream serial(port, ios::in | ios::out);
    if (!serial.is_open()) {
        cout << "[Error] ESP32 tidak terdeteksi di " << port << endl;
        return;
    }
}
void ajukan(){
string perangkat;
string merk;
string keluhan;
cout<<"Apa perangkatmu?"<<endl;
cin>>perangkat;
cout<<"Apa merk perangkatmu?"<<endl;
cin>>merk;
cout<<"Apa keluhan perangkat ini?"<<endl;
cin>>keluhan;
j["action"] = "ajukan";
j["perangkat"] = perangkat;
j["merk"] = merk;
j["keluhan"] = keluhan;
string payload = j.dump();
sendKebridge(payload);
}

void cek(){
string nomorTiket;
cout<<"Masukkan nomor tiket/antreanmu"<<endl;
cin>>nomorTiket;
j["action"] = "cek";
j["id"] = nomorTiket;
string payload = j.dump();
sendKebridge(payload);
}

void ambil(){
string nomorTiket;
cout<<"Masukkan nomor tiket/antreanmu yang mau diambil"<<endl;
cin>>nomorTiket;
j["action"] = "ambil";
j["id"] = nomorTiket;
string payload = j.dump();
sendKebridge(payload);
}

void track(){
string nomorTiket;
cout<<"Masukkan nomor tiket/antreanmu yang mau dicek/track"<<endl;
cin>>nomorTiket;
j["action"] = "track";
j["id"] = nomorTiket;
string payload = j.dump();
sendKebridge(payload);
}
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return ""; // Jika string hanya berisi karakter kosong
    
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

string commandUser[13] = {
    "cek", "order", "help", "status", "token", "send", "quit", "exit", "daftar",
    "ajukan", "servis", "track", "ambil"
};

void bacaInput(string Input){
int com;
for(int i=0;i<Input.length();i++){
    Input[i] = tolower(Input[i]);
}
string input = trim(Input);

for (int i=0;i<sizeof(commandUser)/sizeof(commandUser[0]);i++){
    if(input==commandUser[i]){
        com = i;
        ketemu = true;
        break;
    }else if(input.substr(0, 4) == "send"){
        string perangkat;
        string merk;
        string keluhan;
        cin>>perangkat;
        cin>>merk;
        cin>>keluhan;
        j["action"] = "ajukan";
        j["perangkat"] = perangkat;
        j["merk"] = merk;
        j["keluhan"] = keluhan;
        string payload = j.dump();
        sendKebridge(payload);
        ketemu = true;
        break;
    }
}
if(!ketemu){
        cout<<"E06"<<endl;
    }

switch (com)
{
case 6:
case 7:
    exit(0);
    break;

case 0:
    cek();
    break;
case 1:
    ajukan();
    break;

case 2:
case 8:
    tampilkanMenu();
    break;

case 3:
    status();
    break;

case 4:
    cout<<token<<endl;
    break;

case 5:
    
    break;

case 9:
    ajukan();
    break;

case 10:
    ajukan();
    break;

case 11:
    track();
    break;

case 12:
    ambil();
    break;    

default:
    break;
}

}

int main(){
    while(true){
    ketemu = false;
    cout<<"Selamat datang di Servis Laen, apa yang bisa kami bantu hari ini? (ketik daftar/help untuk menu command)"<<endl;
    cin>>inputUser;
    bacaInput(inputUser);

    }
    return 0;
}