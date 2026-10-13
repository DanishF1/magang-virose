#include<iostream>
#include<vector>
#include<algorithm>
#include "parsingMachine.h" //MY HEADER
using namespace std;

int main(){
    bool valid = false;
    int fileInput = 0;
    int namaMov[] = {36,38,39,40,41,43,44,45,46,48,49,50,51,53,54,55,56,58,59,60,61};
    cout<<"masukkan input movie"<<endl;
    cin>>fileInput;
    for (int i=0;i<sizeof(namaMov);i++){
        if(fileInput == namaMov[i]){
            valid = true;
            break;
        }
    }
    valid == true ? cout<<"memproses untuk parsing"<<endl : cout<<"angka tidak valid";
    parsing p;
    p.startParsing(fileInput);


    return 0;
}