#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct harga{
    int A;
    int B;
    int C;
};
struct truk{
    int Ax;
    int Ay;
    int Bx;
    int By;
    int Cx;
    int Cy;
};
int x = 0;
int y = 0;
int hargaAkhir;
int main(){
    harga h;
    truk t;

  cin>>h.A;
  cin>>h.B;
  cin>>h.C;
  
  cin>>t.Ax;
  cin>>t.Ay;
  
  cin>>t.Bx;
  cin>>t.By;
  
  cin>>t.Cx;
  cin>>t.Cy;
  
  vector<int> x = {t.Ax, t.Bx, t.Cx};
  sort(x.begin(), x.end());
  vector<int> y = {t.Ay, t.By, t.Cy};
  sort(y.begin(), y.end());

  vector<int> trukA;
  vector<int> trukB;
  vector<int> trukC;
  
  for (int i = t.Ax; i < t.Ay; i++){
    trukA.push_back(i);
  }
  for (int i = t.Bx; i < t.By; i++){
    trukB.push_back(i);
  }
  for (int i = t.Cx; i < t.Cy; i++){
    trukC.push_back(i);
  }
  sort(trukA.begin(), trukA.end());
  sort(trukB.begin(), trukB.end());
  sort(trukC.begin(), trukC.end());
  vector<int> hasilAB;
  vector<int> hasilAC;
  vector<int> hasilBC;
  vector<int> hasilABC;
  set_intersection(
    trukA.begin(), trukA.end(),
    trukB.begin(), trukB.end(),
    back_inserter(hasilAB)
  );
  set_intersection(
    trukA.begin(), trukA.end(),
    trukC.begin(), trukC.end(),
    back_inserter(hasilAC)
  );
  set_intersection(
    trukC.begin(), trukC.end(),
    trukB.begin(), trukB.end(),
    back_inserter(hasilBC)
  );
  set_intersection(
    hasilAC.begin(), hasilAC.end(),
    trukB.begin(), trukB.end(),
    back_inserter(hasilABC)
  );
    hargaAkhir = h.A*(trukA.size()+trukB.size()+trukC.size()-2*(hasilAB.size()+hasilAC.size()+hasilBC.size())+3*hasilABC.size())+h.B*2*(hasilAB.size()+hasilAC.size()+hasilBC.size()-3*hasilABC.size())+h.C*3*(hasilABC.size());

    cout << hargaAkhir << endl;

}