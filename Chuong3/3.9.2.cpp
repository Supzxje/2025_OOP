
#include <iostream>
using namespace std;

class ANIMAL {
protected:
    int age;
    float weight;
    int sex; // 0: đực, 1: cái

public:
    ANIMAL() {} 

    void set(int a, float w, int s) {
        age = a;
        weight = w;
        sex = s;
    }

    void print() {
        cout << "Tuoi: " << age << ", Can nang: " << weight;
        cout << ", Gioi tinh: " << (sex == 0 ? "Duc" : "Cai") << endl;
    }

    void an() {
        cout << "Con vat dang an" << endl;
    }
};

class ELEPHANT : public ANIMAL {
private:
    int root; // 0: chau A, 1: chau Phi

public:
    ELEPHANT() {} 

    void set(int a, float w, int s, int r) {
        ANIMAL::set(a, w, s); 
        root = r;
    }

    void print() {
        ANIMAL::print();
        cout << "Xuat xu: " << (root == 0 ? "Chau A" : "Chau Phi") << endl;
    }

    void an() {
        cout << "Voi dang an co." << endl;
    }
};

int main() {
    ELEPHANT voi;
    voi.set(10, 1500.5, 0, 1); //test
    voi.print(); 
    voi.an();    
    return 0;
}
