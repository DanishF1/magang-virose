#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>
using namespace std;

void tell(int number){
cout<<number<<endl;
}
void tell(double number){
cout<<0<<endl;
}
int main(){
    int p;
    int q;
    cin>>p;
    cin>>q;
    auto hasil = (p*p+q*q+9+11)/4.0;
    if(hasil == floor(hasil)){
        tell(static_cast<int>(hasil));
    }else{
        tell(hasil);
    }
    
}