#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    int x, y;
public:
    Point(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }

    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() const { return x; }
    int getY() const { return y; }

    void print() const {
        cout << "(" << x << ", " << y << ")";
    }
};

class Line {
private:
    Point A, B;

public:
    Line() {}
    ~Line() {}

    void set(int x1, int y1, int x2, int y2) {
        A.set(x1, y1);
        B.set(x2, y2);
    }

    float tinhDoDai() const {
        int dx = B.getX() - A.getX();
        int dy = B.getY() - A.getY();
        return sqrt(dx * dx + dy * dy); // sqrt((x2 - x1)^2 + (y2 - y1)^2)
    }
    
    void print(){
        cout << "Diem A: "; A.print();
        cout << ", Diem B: "; B.print();
        cout << ", Do dai: " << tinhDoDai() << endl;
    }

    void xuatPhuongTrinh() const {
        int x1 = A.getX(), y1 = A.getY();
        int x2 = B.getX(), y2 = B.getY();

        if (x1 == x2) {
            cout << "Phuong trinh duong thang: x = " << x1 << endl;
        } else {
            float a = float(y2 - y1) / (x2 - x1);
            float b = y1 - a * x1;
            cout << "Phuong trinh duong thang: y = " << a << "x + " << b << endl;
        }
    }
};

int main() {
    Line l;
    l.set(1, 2, 4, 6);
    l.print();
    l.xuatPhuongTrinh();

    return 0;
}
