#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// A single pixel - just data, no behavior, so it stays a struct.
struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

// The image - has both data AND behavior (filters), so it's a class.
class Image {
private:
    int height = 0;
    int width = 0;

public:
    vector<Pixel> pixels;

    // Loads a PPM (P3) file into this object.
    // Returns true on success, false on failure - lets main() react properly.
    bool loadppm(const string &filename) {
        ifstream in(filename);
        if (!in.is_open()) {
            cout << "Error: could not open file '" << filename << "'\n";
            return false;
        }

        string tag;
        int maxval;
        in >> tag ;
        in>>ws;
        if(in.peek()=='#'){
            string comment;
            getline(in,comment);
            in>>ws;

        }
        in>>width>>height>>maxval;
        if (tag != "P3") {
            cout << "Error: unsupported format '" << tag << "' (only P3 supported)\n";
            return false;
        }

        pixels.clear(); // in case this object was already holding an older image
        int r, g, b;
        for (int i = 0; i < width * height; i++) {
            in >> r >> g >> b;
            pixels.push_back({(unsigned char)r, (unsigned char)g, (unsigned char)b});
        }

        in.close();
        cout << "Loaded '" << filename << "' (" << width << "x" << height
             << ", " << pixels.size() << " pixels)\n";
        return true;
    }

    // Saves this object's current pixel data to a new PPM file.
    bool saveppm(const string &filename) {
        ofstream out(filename);
        if (!out.is_open()) {
            cout << "Error: could not create file '" << filename << "'\n";
            return false;
        }

        out << "P3\n" << width << " " << height << "\n255\n";
        for (const auto &p : pixels) {
            out << (int)p.r << " " << (int)p.g << " " << (int)p.b << "\n";
        }

        out.close();
        cout << "Saved -> " << filename << "\n";
        return true;
    }

    void grayscale() {
        for (auto &p : pixels) {
            int gray = 0.3 * p.r + 0.59 * p.g + 0.11 * p.b;
            p.r = p.g = p.b = gray;
        }
    }

    void invert() {
        for (auto &p : pixels) {
            p.r = 255 - p.r;
            p.g = 255 - p.g;
            p.b = 255 - p.b;
        }
    }

    void brightness(int value) {
        for (auto &p : pixels) {
            p.r = clamp(p.r + value);
            p.g = clamp(p.g + value);
            p.b = clamp(p.b + value);
        }
    }

    void flipHorizontal() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width / 2; x++) {
                int left = y * width + x;
                int right = y * width + (width - 1 - x);
                swap(pixels[left], pixels[right]);
            }
        }
    }

private:
    // Keeps a color value inside the valid 0-255 range.
    static int clamp(int v) {
        if (v < 0) return 0;
        if (v > 255) return 255;
        return v;
    }
};

// Shows the menu and returns the user's choice.
int showMenu() {
    cout << "\n--- Raw Image Editor ---\n";
    cout << "1. Grayscale\n";
    cout << "2. Invert\n";
    cout << "3. Brightness\n";
    cout << "4. Flip Horizontal\n";
    cout << "5. Save and Exit\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;
    return choice;
}

int main() {
    string filename;
    cout << "Enter input PPM filename: ";
    cin >> filename;

    Image img;
    if (!img.loadppm(filename)) {
        cout << "Exiting - could not load image.\n";
        return 1;
    }

    // Loop so the user can apply MULTIPLE filters in one run,
    // instead of restarting the program each time.
    bool running = true;
    while (running) {
        int choice = showMenu();

        switch (choice) {
            case 1:
                img.grayscale();
                cout << "Applied grayscale.\n";
                break;
            case 2:
                img.invert();
                cout << "Applied invert.\n";
                break;
            case 3: {
                cout << "Enter brightness value (e.g. 50 or -50): ";
                int value;
                cin >> value;
                img.brightness(value);
                cout << "Applied brightness.\n";
                break;
            }
            case 4:
                img.flipHorizontal();
                cout << "Applied flip.\n";
                break;
            case 5:
                running = false;
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }

    string outputFile;
    cout << "Enter output filename: ";
    cin >> outputFile;
    img.saveppm(outputFile);

    return 0;
}