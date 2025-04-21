#include <iostream>
using namespace std;

class DaThuc{
    int N;
    int data[];
public:
    DaThuc(int n);
    ~DaThuc(){}

    void input();
    void print();

    friend istream& operator>>(istream& is, DaThuc& dt);
    friend ostream& operator<<(ostream& os, DaThuc dt);

    int tinhGiaTri(int x);

    DaThuc daoHam();
    DaThuc tichPhan();

    DaThuc operator+(const DaThuc& other);
    DaThuc operator-(const DaThuc& other);
    DaThuc operator*(const DaThuc* other);

    double& operator[](int i);
    
    DaThuc operator++();
    DaThuc operator--();
};

DaThuc::DaThuc(int n){
    N = n;
}

