#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <windows.h>
#include <conio.h>

using namespace std;

// =================== TIỆN ÍCH HIỂN THỊ ===================
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void slowPrint(const string& text, int delayMs = 20) {
    for (char c : text) {
        cout << c << flush;
        Sleep(delayMs);
    }
    cout << endl;
}

int interactiveMenu(const vector<string>& options, const string& title) {
    int selected = 0;
    while (true) {
        system("cls");
        setColor(11);
        cout << title << "\n\n";
        setColor(7);

        for (size_t i = 0; i < options.size(); ++i) {
            if ((int)i == selected) {
                setColor(112); // nền sáng
                cout << " > " << options[i] << "\n";
                setColor(7);
            }
            else {
                cout << "   " << options[i] << "\n";
            }
        }

        int ch = _getch();
        if (ch == 224) {
            ch = _getch();
            if (ch == 72) selected = (selected - 1 + options.size()) % options.size(); // lên
            if (ch == 80) selected = (selected + 1) % options.size(); // xuống
        }
        else if (ch == 13) {
            return selected;
        }
    }
}

// =================== CLASS CƠ SỞ ===================
class Account {
protected:
    string username;
    string password;
public:
    Account(const string& user, const string& pass)
        : username(user), password(pass) {
    }
    virtual ~Account() {}

    string getUsername() const;
    bool checkPassword(const string& pass) const;

    virtual void displayMenu() = 0;
};

string Account::getUsername() const{
    return username;
}

bool Account::checkPassword(const string& pass) const {
    return password == pass;
}

// =================== NGƯỜI DÙNG ===================
class BankUser : public Account {
private:
    double balance;
public:
    BankUser(const string& user, const string& pass, double bal = 0)
        : Account(user, pass), balance(bal) {
    }

    void deposit(double amount);
    void withdraw(double amount);
    void checkBalance() const;
    void displayMenu() override;
};

void BankUser::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << "Nap tien thanh cong.\n";
    }
    else {
        cout << "So tien khong hop le.\n";
    }
}

void BankUser::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        cout << "Rut tien thanh cong.\n";
    }
    else {
        cout << "So tien khong hop le hoac khong du.\n";
    }
}

void BankUser::checkBalance() const {
    cout << "So du hien tai: " << balance << " VND\n";
}

void BankUser::displayMenu() override {
    vector<string> menu = {
        "Nap tien",
        "Rut tien",
        "Kiem tra so du",
        "Dang xuat"
    };
    int choice;
    do {
        choice = interactiveMenu(menu, "--- MENU NGUOI DUNG ---");
        switch (choice) {
        case 0: {
            double amount;
            cout << "Nhap so tien nap: ";
            cin >> amount;
            deposit(amount);
            break;
        }
        case 1: {
            double amount;
            cout << "Nhap so tien rut: ";
            cin >> amount;
            withdraw(amount);
            break;
        }
        case 2:
            checkBalance();
            break;
        }
        system("pause");
    } while (choice != 3);
    slowPrint("Dang xuat...");
}

// =================== ADMIN ===================
class Admin : public Account {
private:
    vector<shared_ptr<BankUser>>& users;
public:
    Admin(const string& user, const string& pass, vector<shared_ptr<BankUser>>& userList)
        : Account(user, pass), users(userList) {
    }

    void addUser();

    void removeUser();

    void listUsers() const;

    void displayMenu() override;
};

void Admin::addUser() {
    string uname, pword;
    cout << "Nhap ten dang nhap moi: ";
    cin >> uname;
    cout << "Nhap mat khau: ";
    cin >> pword;
    users.push_back(make_shared<BankUser>(uname, pword));
    cout << "Them nguoi dung thanh cong.\n";
}

void Admin::removeUser() {
    string uname;
    cout << "Nhap ten nguoi dung can xoa: ";
    cin >> uname;
    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getUsername() == uname) {
            users.erase(it);
            cout << "Xoa nguoi dung thanh cong.\n";
            return;
        }
    }
    cout << "Khong tim thay nguoi dung.\n";
}

void Admin::listUsers() const {
    cout << "--- DANH SACH NGUOI DUNG ---\n";
    for (const auto& u : users) {
        cout << " - " << u->getUsername() << '\n';
    }
}

void Admin::displayMenu() override {
    vector<string> menu = {
        "Them nguoi dung",
        "Xoa nguoi dung",
        "Danh sach nguoi dung",
        "Dang xuat"
    };
    int choice;
    do {
        choice = interactiveMenu(menu, "--- MENU QUAN TRI VIEN ---");
        switch (choice) {
        case 0:
            addUser();
            break;
        case 1:
            removeUser();
            break;
        case 2:
            listUsers();
            break;
        }
        system("pause");
    } while (choice != 3);
    slowPrint("Dang xuat...");
}
// =================== HỆ THỐNG CHÍNH ===================
class BankSystem {
private:
    vector<shared_ptr<BankUser>> users;
    vector<shared_ptr<Admin>> admins;
public:
    BankSystem();

    void login();

    void run() {
        vector<string> menu = {
            "Dang nhap",
            "Thoat"
        };
        int choice;
        do {
            choice = interactiveMenu(menu, "=== HE THONG NGAN HANG ===");
            if (choice == 0) login();
        } while (choice != 1);
        slowPrint("Tam biet!");
    }
};

BankSystem::BankSystem() {
    admins.push_back(make_shared<Admin>("admin", "admin123", users));
    users.push_back(make_shared<BankUser>("user1", "123"));
}

void BankSystem::login() {
    string uname, pword;
    cout << "Ten dang nhap: ";
    cin >> uname;
    cout << "Mat khau: ";
    cin >> pword;

    for (auto& admin : admins) {
        if (admin->getUsername() == uname && admin->checkPassword(pword)) {
            slowPrint("Dang nhap thanh cong (admin).\n");
            admin->displayMenu();
            return;
        }
    }

    for (auto& user : users) {
        if (user->getUsername() == uname && user->checkPassword(pword)) {
            slowPrint("Dang nhap thanh cong (nguoi dung).\n");
            user->displayMenu();
            return;
        }
    }

    setColor(12);
    slowPrint("Sai ten dang nhap hoac mat khau.\n");
    setColor(7);
    system("pause");
}

void BankSystem::run() {
    vector<string> menu = {
        "Dang nhap",
        "Thoat"
    };
    int choice;
    do {
        choice = interactiveMenu(menu, "=== HE THONG NGAN HANG ===");
        if (choice == 0) login();
    } while (choice != 1);
    slowPrint("Tam biet!");
}

// =================== MAIN ===================
int main() {
    BankSystem system;
    system.run();
    return 0;
}