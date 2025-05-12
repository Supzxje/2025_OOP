#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class DaThuc{
    int N;
    vector<double> data;
public:
    DaThuc(int n = 0){
        this->N = n;
    }

    ~DaThuc(){}

    void input() {
        cout << "Nhap bac cua da thuc: ";
        cin >> N;
        for (int i = 0; i <= N; ++i) {
            cout << "He so cua x^" << i << ": ";
            cin >> data[i];
        }
    }

    void print() {
        for (int i = N; i >= 0; --i) {
            if (data[i] != 0) {
                if (i != N && data[i] > 0) cout << " + ";
                else if (data[i] < 0) cout << " - ";
                cout << abs(data[i]);
                if (i > 0) cout << "x";
                if (i > 1) cout << "^" << i;
            }
        }
        cout << endl;
    }

    double tinhGiaTri(double x){
        double result = 0;
        for (int i = 0; i <= N; ++i) {
            result += data[i] * pow(x, i);
        }
        return result;
    }

    DaThuc daoHam() {
        if (N == 0) return DaThuc(0);
        DaThuc res(N - 1);
        for (int i = 1; i <= N; ++i) {
            res.data[i - 1] = data[i] * i;
        }
        return res;
    }

    DaThuc tichPhan(){
        DaThuc res(N + 1);
        for (int i = 0; i <= N; ++i) {
            res.data[i + 1] = data[i] / (i + 1);
        }
        return res;
    }

    DaThuc operator+(const DaThuc& other) {
        int bac = max(N, other.N);
        DaThuc res(bac);
        for (int i = 0; i <= bac; ++i) {
            double a = (i <= N ? data[i] : 0);
            double b = (i <= other.N ? other.data[i] : 0);
            res.data[i] = a + b;
        }
        return res;
    }

    DaThuc operator-(const DaThuc& other) {
        int bac = max(N, other.N);
        DaThuc res(bac);
        for (int i = 0; i <= bac; ++i) {
            double a = (i <= N ? data[i] : 0);
            double b = (i <= other.N ? other.data[i] : 0);
            res.data[i] = a - b;
        }
        return res;
    }

    DaThuc operator*(const DaThuc& other){
        DaThuc res(N + other.N);
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= other.N; ++j) {
                res.data[i + j] += data[i] * other.data[j];
            }
        }
        return res;
    }

    double& operator[](int i) {
        return data[i];
    }

    // const double& operator[](int i) const {
    //     return data[i];
    // }

    DaThuc& operator++() {
        for (double x : data) ++x;
        return *this;
    }

    DaThuc& operator--() {
        for (double x : data) --x;
        return *this;
    }

    friend istream& operator>>(istream& in, DaThuc& dt) {
        cout << "Nhap bac cua da thuc: ";
        in >> dt.N;
        dt.data.resize(dt.N + 1);
        for (int i = 0; i <= dt.N; ++i) {
            cout << "He so cua x^" << i << ": ";
            in >> dt.data[i];
        }
        return in;
    }

   
    friend ostream& operator<<(ostream& out, const DaThuc& dt) {
        for (int i = dt.N; i >= 0; --i) {
            if (dt.data[i] != 0) {
                if (i != dt.N && dt.data[i] > 0) out << " + ";
                else if (dt.data[i] < 0) out << " - ";
                out << abs(dt.data[i]);
                if (i > 0) out << "x";
                if (i > 1) out << "^" << i;
            }
        }
        return out;
    }

};

int main() {
    DaThuc p1, p2;
    cout << "Nhap da thuc thu nhat:\n";
    cin >> p1;
    cout << "Nhap da thuc thu hai:\n";
    cin >> p2;

    cout << "\nDa thuc 1: " << p1 << endl;
    cout << "Da thuc 2: " << p2 << endl;

    DaThuc sum = p1 + p2;
    cout << "\nTong: " << sum << endl;

    DaThuc hieu = p1 - p2;
    cout << "Hieu: " << hieu << endl;

    DaThuc tich = p1 * p2;
    cout << "Tich: " << tich << endl;

    DaThuc dao = p1.daoHam();
    cout << "Dao ham cua da thuc 1: " << dao << endl;

    DaThuc tichphan = p1.tichPhan();
    cout << "Tich phan cua da thuc 1: " << tichphan << endl;

    cout << "Gia tri da thuc 1 tai x = 2: " << p1.tinhGiaTri(2) << endl;

    ++p1;
    cout << "Da thuc 1 sau khi ++: " << p1 << endl;

    --p1;
    cout << "Da thuc 1 sau khi --: " << p1 << endl;

    return 0;
}
