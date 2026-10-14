#include<iostream>
#include<vector>
#include<algorithm>
#include "parsingMachine.h" //MY HEADER
using namespace std;
int namaMov[21] = {36,38,39,40,41,43,44,45,46,48,49,50,51,53,54,55,56,58,59,60,61};
int cols = sizeof(namaMov)/sizeof(namaMov[0]);

void process(int fileInput){
    bool valid = false;
    for (int i=0;i<cols;i++){
        if(fileInput == namaMov[i]){
            valid = true;
            break;
        }else if(fileInput != namaMov[i]){
            valid = false;
        }
    }
    if(fileInput == 0){exit(EXIT_SUCCESS);}
    valid == true ? cout<<"Processing..."<<endl : cout<<"Err, input is not valid"<<endl;
    parsing p;
    if(valid){
        p.startParsing(fileInput);
}
}

int main(){
    while(true){
    int fileInput;
    cout<<"Input desired motion movie (input 0, enter letter(s), or Ctrl + c to quit )"<<endl;
    cin>>fileInput;
    process(fileInput);
    }
}

