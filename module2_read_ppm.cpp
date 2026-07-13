#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
struct Pixel{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
struct Image{
    int height;
    int width;
    vector<Pixel>pixels;
};
Image readppm(string filename){
    ifstream in;
    string str;
    int h,w,max_value;
    in.open(filename);
    if(!in.is_open()){
        cout<<"file not found!";
    }
    in>>str>>w>>h>>max_value;
    cout<<"reading values!!"<<endl;
    cout<<str<<" "<<w<<" "<<h<<" "<<max_value<<endl;
    Image img;
    img.height=h;
    img.width=w;
    int r,g,b;
    Pixel p;
    for(int i=0;i<img.height*img.width;i++){
        in>>r>>g>>b;
        p={(unsigned char)r,(unsigned char)g,(unsigned char)b};
        img.pixels.push_back(p);
        
    }cout<<img.pixels.size()<<endl;
    in.close();
    return img;
}
int main(){
    Pixel p1,p2,p3,p4;
     p1={255,0,0};
   p2={0,255,0};
   p3={0,0,255};
   p4={255,0,255};
   Image img;
   img.pixels.push_back(p1);
   img.pixels.push_back(p2);
   img.pixels.push_back(p3);
   img.pixels.push_back(p4);
   for(auto &p:img.pixels){
    cout<<"R:"<<(int)p.r<<" "<<"G:"<<(int)p.g<<" "<<"B:"<<(int)p.b<<endl;}
   Image loaded=readppm("test.ppm");
   cout<<loaded.height<<" "<<loaded.width;
   
}