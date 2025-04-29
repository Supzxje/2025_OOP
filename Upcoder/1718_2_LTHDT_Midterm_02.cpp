#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class Employee {
private:
    int id;
    string firstName;
    string lastname;
    double salary;
public:
    // Constructors
    Employee() {
        id = 0;
        firstName = "";
        lastname = "";
        salary = 0;
    }

    Employee(int a, string b, string c, double d) {
        id = a;
        firstName = b;
        lastname = c;
        salary = d;
    }

    // Methods
    void Nhap() {
        cin >> id;
        cin.ignore();
        getline(cin, firstName);
        getline(cin, lastname);
        cin >> salary;
    }

    void Xuat() const {
        cout << "Employee[id=" << id << ",name=" << firstName << " " << lastname 
             << ",salary=$" << fixed << setprecision(2) << salary << "]" << endl;
    }

    int getID() const {
        return id;
    }

    string getLastName() const {
        return lastname;
    }

    string getFirstName() const {
        return firstName;
    }

    double getSalary() const {
        return salary;
    }

    void setSalary(double a) {
        salary = a;
    }

    double getAnnualSalary() const {
        return 12 * salary;
    }

    double raiseSalary(double percent) {
        salary += salary * percent / 100.0;
        return salary;
    }

    // Nạp chồng toán tử ++ (prefix)
    Employee& operator++() {
        salary += salary * 0.1;
        return *this;
    }

    // Nạp chồng toán tử ++ (postfix)
    Employee operator++(int) {
        Employee temp = *this;
        salary += salary * 0.1;
        return temp;
    }

    // Nạp chồng toán tử -- (prefix)
    Employee& operator--() {
        salary -= salary * 0.1;
        return *this;
    }

    // Nạp chồng toán tử -- (postfix)
    Employee operator--(int) {
        Employee temp = *this;
        salary -= salary * 0.1;
        return temp;
    }
};

int main() {
    Employee* a = new Employee();
    Employee* b = new Employee();

    a->Nhap();
    b->Nhap();

    double m, n;
    cin >> m >> n;

    a->Xuat();
    b->Xuat();

    // So sánh theo lương năm
    if (a->getAnnualSalary() > b->getAnnualSalary()) {
        cout << "LON HON" << endl;
    } else if (a->getAnnualSalary() == b->getAnnualSalary()) {
        cout << "BANG NHAU" << endl;
    } else {
        cout << "NHO HON" << endl;
    }

    // (a++) - m
    Employee tempA = (*a)++;
    double luongA = tempA.getSalary() - m;
    cout << "$" << fixed << setprecision(2) << luongA << endl;

    // (--b) + n
    Employee tempB = --(*b);
    double luongB = tempB.getSalary() + n;
    cout << "$" << fixed << setprecision(2) << luongB << endl;

    delete a;
    delete b;

    return 0;
}