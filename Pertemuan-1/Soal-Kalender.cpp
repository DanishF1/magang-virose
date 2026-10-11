//this is heavily unfinished
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;
struct times{
int D;
int M;
int Y;
int N; //berapa banyak kalender (maks 12)
string currentM;
bool kabisat;

};
times t;

int main(){
    
    string namaM[12] = {"Januari","Februari","Maret","April","Mei","Juni","Juli","Agustus","September","Oktober","November","Desember"};
    string namaD[7] = {"Minggu","Selasa","Rabu","Kamis","Jumat","Sabtu","Senin"};
    int jumlahM[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    cin>>t.D;
    cin>>t.M;
    cin>>t.Y;
    cin>>t.N;
    int desiredDay = t.D;
    int desiredMonth = t.M;
    int desiredYear = t.Y;
    if (t.Y%4==0&&t.Y%100!=0||t.Y%400==0){
        t.kabisat = true;
        int jumlahM[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    }else{
        t.kabisat=false;
    }
    
    int tempY = t.Y;
    int tempM = t.M;
    int sakamoto[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if (tempM < 3) tempY -= 1;
    int dayOne = (tempY + tempY / 4 - tempY / 100 + tempY / 400 + sakamoto[tempM - 1] + 1) % 7;

    int prevM = (t.M == 1) ? 12 : t.M - 1;
    int prevY = (t.M == 1) ? t.Y - 1 : t.Y;
    int bulanlaluD = jumlahM[prevM];
    vector<string> output[7][6];
    for (int i=0;i<t.N;i++){
        cout<<namaM[t.M-1]<<" "<<t.Y<<endl;
        t.M++;
        for(int j=0;j<7;j++){
            cout<<namaD[j]<<" ";
            int cols = 1;
                for(int k=0;k<jumlahM[t.M];k++){
                    for (int i=0;i<8;i++){switch (dayOne)
                    {
                    case 0:
                        for (int d=0;d<jumlahM[t.M];d++){
                            switch(d){
                                case 7:
                                cols=2;
                                break;
                                case 14:
                                cols=3;
                                break;
                                case 21:
                                cols=4;
                                break;
                                case 28:
                                cols=5;
                                break;

                            }
                            if(desiredDay==d&&desiredMonth==t.M){
                                output[i][cols].push_back(to_string('*'+d+'*'));
                            }else if(d>jumlahM[t.M]){
                                
                            }else{
                                output[i][cols].push_back(to_string(d));
                            }
                            
                        }
                        break;
                    
                    default:
                        break;
                    }
                }
                    
                    }
                    
                    
                }
        }
        cout<<endl<<""<<endl<<endl;

        if(t.M>12){
            t.M=1;
            t.Y += 1;
        }
       return 0; 
    }
    
