#include <iostream>
#include <fstream>
#include <vector>
#include<algorithm>
using namespace std;
// pixel struct
struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
// image struct
struct Image
{
    int height;
    int width;
    vector<Pixel> pixels;
};
// reading ppm file
Image readppm(string filename)
{
    ifstream in;
    Image img;
    string str;
    int h, w, max_value;
    in.open(filename);
    if (!in.is_open())
    {
        cout << "file not found!";
        return img;//stop here
    }
    in >> str >> w >> h >> max_value;
    cout << "reading values!!" << endl;
    cout << str << " " << w << " " << h << " " << max_value << endl;
    img.height = h;
    img.width = w;
    int r, g, b;
    Pixel p;
    for (int i = 0; i < img.height * img.width; i++)
    {
        in >> r >> g >> b;
        p = {(unsigned char)r, (unsigned char)g, (unsigned char)b};
        img.pixels.push_back(p);
    }
    cout << img.pixels.size() << endl;
    in.close();
    return img;
}
// writing ppm file
void writeppm(string filename, Image img)
{
    ofstream out;
    out.open(filename);
    out << "P3\n";
    out << img.width << " " << img.height << "\n";
    out << "255\n";
    for (auto &p : img.pixels)
    {
        out << (int)p.r << " " << (int)p.g << " " << (int)p.b << "\n";
    }
    out.close();
}
//grayscale filter
void grayscale(Image &img){
    int gray;
for(auto &p:img.pixels){
    gray = 0.3*p.r + 0.59*p.g + 0.11*p.b;
    p.r=p.g=p.b=gray;
}
}
//invert filter
void invertimage(Image &img){
    for(auto &p:img.pixels){
        p.r=255-(int)p.r;
        p.g=255-(int)p.g;
        p.b=255-(int)p.b;
    }
}
//clamp function
int clamp(int v){
    if(v>255){
        return 255;
    }
    else if(v<0){
        return 0;
    }
    else
    return v;
}
// brightness control
void brightness(Image &img,int value){
    for(auto &p:img.pixels){
        p.r = clamp(p.r + value);
        p.g=clamp(p.g + value);
        p.b=clamp(p.b + value);
    }
}
void horizentleflip(Image &img){
    for(int i=0;i<img.height;i++){
        for(int j=0;j<img.width/2;j++){
           int left= i * img.width + j;
           int right = i * img.width + (img.width - 1 - j);
               swap(img.pixels[left],img.pixels[right]);

        }
    }
}
int main()
{
    int choice;
    int value;
    string filename;
    string output_file;
    cout<<"enter file name:";
    cin>>filename;
    Image loaded = readppm(filename);
if (loaded.pixels.empty()) {
    cout << "Could not load image, exiting.\n";
    return 0;   // stop the whole program here
}
    cout << "1. Grayscale\n2. Invert\n3. Brightness\n4. Flip\nChoice: ";
    cout<<"enter your choice:";
    cin>>choice;
    if(choice==1){
        grayscale(loaded);
    }
    else if(choice==2){
        invertimage(loaded);
    }
    else if(choice==3){
        cout<<"enter value:";
        cin>>value;
        brightness(loaded,value);
    }
    else if(choice==4){
        horizentleflip(loaded);
    }
    else
    cout<<"invalid choice!!";
    cout<<"enter output file name:";
    cin>>output_file;
   writeppm(output_file,loaded);
   return 0;
}