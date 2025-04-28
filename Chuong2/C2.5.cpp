#include <iostream>
#include <cmath>
using namespace std;

class Point2D {
private:
    int x, y;
public:
    Point2D(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }

    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() { return x; }
    int getY() { return y; }

    void print() {
        cout << "(" << x << ", " << y << ")";
    }
};

class TamGiac {
private:
    Point2D A, B, C; 
public:

    TamGiac() {}

    ~TamGiac() {}

    void set(int xA, int yA, int xB, int yB, int xC, int yC) {
        A.set(xA, yA);
        B.set(xB, yB);
        C.set(xC, yC);
    }

    float khoangCach(Point2D p1, Point2D p2) {
        int dx = p2.getX() - p1.getX();
        int dy = p2.getY() - p1.getY();
        return sqrt(dx * dx + dy * dy);
    }

    float tinhChuVi() {
        float AB = khoangCach(A, B);
        float BC = khoangCach(B, C);
        float CA = khoangCach(C, A);
        return AB + BC + CA;
    }

    float tinhDienTich() {
        float AB = khoangCach(A, B);
        float BC = khoangCach(B, C);
        float CA = khoangCach(C, A);
        float p = (AB + BC + CA) / 2; // n?a chu vi
        return sqrt(p * (p - AB) * (p - BC) * (p - CA));
    }

    void print() {
        cout << "Diem A: ";
        A.print();
        cout << ", Diem B: ";
        B.print();
        cout << ", Diem C: ";
        C.print();
        cout << endl;
    }
};

int main() {
    TamGiac tg;
    tg.set(0, 0, 3, 0, 0, 4);

    cout << "Thong tin tam giac:" << endl;
    tg.print();

    cout << "Chu vi tam giac: " << tg.tinhChuVi() << endl;
    cout << "Dien tich tam giac: " << tg.tinhDienTich() << endl;

    return 0;
}
