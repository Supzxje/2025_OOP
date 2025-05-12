
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

    friend istream& operator>>(istream& is, TamGiac& tg){
        is  >> tg.a >> tg.b >> tg.c;
        return is;
    }

    friend ostream& operator<<(ostream& os, TamGiac tg){
        os << "(" << tg.a << tg.b << tg.c << ")";
        return os;
    }
};

class TamGiacDeu : public TamGiac {
    private: 
    int canh;
public:
    TamGiacDeu(float canh = 1) : TamGiac(canh, canh, canh) {}

    friend istream& operator>>(istream& is, TamGiacDeu& tgd){
        is >> tgd.canh;
    }

    friend ostream& operator<<(ostream& os, TamGiacDeu tg){
        os << "(" << tg.canh << tg.canh << tg.canh << ")";
        return os;
    }    
};

int main() {
    TamGiacDeu tg;
    cin >> tg;
    cout << tg;

    // cout << "Chu vi: " << tg.tinhChuVi() << endl;
    // cout << "Dien tich: " << tg.tinhDienTich() << endl;
    return 0;
}