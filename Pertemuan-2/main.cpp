#include<iostream>
#include<vector>
#include<algorithm>
#include "parsingMachine.h" //MY HEADER
using namespace std;

int main(){
    bool valid = false;
    int fileInput;
    int namaMov[21] = {36,38,39,40,41,43,44,45,46,48,49,50,51,53,54,55,56,58,59,60,61};
    cout<<"Input desired motion movie"<<endl;
    cin>>fileInput;
    int cols = sizeof(namaMov)/sizeof(namaMov[0]);
    for (int i=0;i<cols;i++){
        if(fileInput == namaMov[i]){
            valid = true;
            break;
        }else if(fileInput != namaMov[i]){
            valid = false;
        }
    }
    valid == true ? cout<<"Processing..."<<endl : cout<<"Err, input is not valid"<<endl;
    parsing p;
    if(valid){
        p.startParsing(fileInput);

    }
  

    return 0;
}