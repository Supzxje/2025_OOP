#include <iostream>
using namespace std;

class MANGIC {
protected:
    int sopt;           
    int data[100];    

public:
    MANGIC() {
        sopt = -1;
    }

    ~MANGIC() {
    }

    void input() {
        cout << "Nhap so luong phan tu: ";
        cin >> sopt;
        for (int i = 0; i < sopt; i++) {
            cout << "Nhap phan tu thu " << i + 1 << ": ";
            cin >> data[i];
        }
    }

    void print() {
        cout << "Cac phan tu cua mang: ";
        for (int i = 0; i < sopt; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

class STACK : public MANGIC {
public:

    STACK() : MANGIC() {}

    ~STACK() {}
    int isEmpty() {
        return sopt == -1;
    }

    void push(int value) {
        if (sopt < 99) {
            data[++sopt] = value;
        } else {
            cout << "STACK day!" << endl;
        }
    }

    int pop() {
        if (!isEmpty()) {
            return data[sopt--];
        } else {
            cout << "STACK rong!" << endl;
            return -1;
        }
    }
};

class BINARY : public STACK {
public:
    BINARY() : STACK() {}

    ~BINARY() {}

    void doiNhiPhan(int n) {
        sopt = -1;

        while (n > 0) {
            push(n % 2); 
            n /= 2;
        }

        cout << "Dang nhi phan: ";
        while (!isEmpty()) {
            cout << pop();
        }
        cout << endl;
    }
};

int main() {
    BINARY b;
    int n;

    cout << "Nhap so nguyen can doi sang nhi phan: ";
    cin >> n;

    b.doiNhiPhan(n);

    return 0;
}
