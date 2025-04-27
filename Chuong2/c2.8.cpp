#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Mang{
    int size;
    vector<int> arr;

public:
    Mang();
    Mang(int size);

    friend istream& operator>>(istream& is, Mang& m);
    friend ostream& operator<<(ostream& os, const Mang& m);

    int getSize();
    int getValueAtI(int i);

    void themPhanTu(int k);
    void xoaPhanTu(int k);

    ~Mang(){}

    void sapXep();
    int timMin();
    int tinhTong();
};

Mang::Mang(int size){
    this->size = size;
}

Mang::Mang(){
    this->size = 0;
}

istream& operator>>(istream& is, Mang& m){
    is >> m.size;
    m.arr.resize(m.size);
    for(int i = 0; i < m.size;i++){
        is >> m.arr[i];
    }
    return is;
}
ostream& operator<<(ostream& os, const Mang& m){
    for(int i = 0; i < m.size;i++){
        os << m.arr[i] << " ";
    }
    return os;
}

int Mang::getSize(){
    return this->size;
}

int Mang::getValueAtI(int i){
    return this->arr[i];
}

void Mang::themPhanTu(int k){
    this->arr.push_back(k);
}

void Mang::xoaPhanTu(int k){
    arr.erase(arr.begin() + k);
}

void Mang::sapXep(){
    this->arr.sort(this->arr.begin(),this->arr.end());
}

int Mang::timMin(){
    int min = this->arr[0];
    for(auto x : this->arr){
        if(x < min)
        min = x;
    }
    return min;
}

int Mang::tinhTong(){
    int sum = 0;
    for(auto x : this->arr){
        sum += x;
    }
    return sum;
}