
#include <iostream>
#include <cmath>
using namespace std;

class TamGiac {
protected:
    float a, b, c;

public:
    TamGiac(float x = 1, float y = 1, float z = 1) {
        a = x;
        b = y;
        c = z;
    }

    float tinhChuVi() {
        return a + b + c;
    }

    float tinhDienTich() {
        float p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

class TamGiacDeu : public TamGiac {
public:
    TamGiacDeu(float canh = 1) : TamGiac(canh, canh, canh) {}

};

int main() {
    TamGiacDeu tg(5);
    cout << "Chu vi: " << tg.tinhChuVi() << endl;
    cout << "Dien tich: " << tg.tinhDienTich() << endl;
    return 0;
}