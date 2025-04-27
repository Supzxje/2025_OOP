#include <iostream>
using namespace std;

class Ngay{
    int day, month, year;
public:
    // Ham tao
    Ngay();
    Ngay(int day, int month, int year);

    // Ham get
    int getDay();
    int getMonth();
    int getYear();

    // Ham set
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    // Toan tu nhap
    friend istream& operator>>(istream &is, Ngay &n);
    // Toan tu xuat
    friend ostream& operator<<(ostream &os, const Ngay& n);

};

Ngay::Ngay(){
    this->day = 1;
    this->month = 1;
    this->year = 2000;
}

Ngay::Ngay(int day, int month, int year){
    this->day = day;
    this->month = month;
    this->year = year;
}

int Ngay::getDay(){
    return this->day;
}

int Ngay::getMonth(){
    return this->month;
}

int Ngay::getYear(){
    return this->year;
}

void Ngay::setDay(int day){
    this->day = day;
}

void Ngay::setMonth(int month){
    this->month = month;
}

void Ngay::setYear(int year){
    this->year = year;
}

istream& operator>>(istream &is, Ngay &n){
    is >> n.day >> n.month >> n.year;
    return is;
}

ostream& operator<<(ostream &os, const Ngay& n){
    os << n.day << "/" << n.month << "/" << n.year;
    return os;
}

