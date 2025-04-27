#include <iostream>
#include <string>
using namespace std;

class number {
private:
    int a, b;

public:
    number();
    number(int a_val, int b_val);
    
    void input();
    void output() const;
    
    number operator+(const number& other) const;
    number operator-(const number& other) const;
    number operator-() const;
    number operator*(const number& other) const;
    
    int getA() const;
    int getB() const;
};

number::number() : a(0), b(0) {}
number::number(int a_val, int b_val) : a(a_val), b(b_val) {}

void number::input() {
    std::cout << "Nhập phần nguyên a: ";
    std::cin >> a;
    std::cout << "Nhập hệ số của √7 (b): ";
    std::cin >> b;
}

void number::output() const {
    if (b == 0) {
        std::cout << a;
    } else {
        if (a != 0) {
            std::cout << a;
            if (b > 0) std::cout << "+";
        }
        if (b != 1 && b != -1) {
            std::cout << b;
        } else if (b == -1) {
            std::cout << "-";
        }
        std::cout << "√7";
    }
}

number number::operator+(const number& other) const {
    return number(a + other.a, b + other.b);
}

number number::operator-(const number& other) const {
    return number(a - other.a, b - other.b);
}

number number::operator-() const {
    return number(-a, -b);
}

number number::operator*(const number& other) const {
    return number(a * other.a + 7 * b * other.b, a * other.b + b * other.a);
}

int number::getA() const { return a; }
int number::getB() const { return b; }