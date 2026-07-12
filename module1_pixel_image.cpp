#include<iostream>
#include<vector>
using namespace std;
struct Pixel{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
struct Image{
int height=2;
int width=2;
vector<Pixel>v;
};
int main(){
    Pixel p1,p2,p3,p4;
   p1={255,0,0};
   p2={0,255,0};
   p3={0,0,255};
   p4={255,0,255};
   Image img;
   img.v.push_back(p1);
   img.v.push_back(p2);
   img.v.push_back(p3);
   img.v.push_back(p4);
   for(auto &p:img.v){
    cout<<"R:"<<(int)p.r<<" "<<"G:"<<(int)p.g<<" "<<"B:"<<(int)p.b<<endl;
   }
}
