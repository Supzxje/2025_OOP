#include <iostream>
#include <vector>
#include <string>
#include <memory> // dùng cho shared_ptr 
#include <windows.h> // dùng để tương tác với console để chỉnh màu, hiệu ứng, dùng sleep 
#include <conio.h>

using namespace std;

// =================== TIỆN ÍCH HIỂN THỊ ===================
// hàm tạo màu chữ và màu nền
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// hàm in dòng chữ chậm lại sau mỗi chức năng 
void slowPrint(const string& text, int delayMs = 50) {
    // in từng chữ 
    for (char c : text) {
        cout << c << flush;
        Sleep(delayMs);
    }
    Sleep(2000); // thời gian chờ chạy lại bảng user, admin với 1000 = 1 giây 
    setColor(0);
    cout << endl;
}
// hàm có chức năng tạo các dòng chức năng để lựa (options) và loại menu user hoặc admin ( title)
int interactiveMenu(const vector<string>& options, const string& title) {
    int selected = 0;
    while (true) {
        system("cls");
        setColor(11);
        cout << title << "\n\n";
        setColor(7);
        for (size_t i = 0; i < options.size(); ++i) {
            if ((int)i == selected) {
                setColor(32);
                cout << " > " << options[i] << "\n";
                setColor(7);
            }
            else {
                cout << "   " << options[i] << "\n";
            }
        }
        // chức năng di chuyển bằng mũi tên 
        int ch = _getch();
        if (ch == 224) {
            ch = _getch();
            // công thức tính toán vị trí dòng chức năng để tránh lỗi nhảy dòng 
            if (ch == 72) selected = (selected - 1 + options.size()) % options.size();
            if (ch == 80) selected = (selected + 1) % options.size();
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
    Account(const string& user = "", const string& pass = "")
        : username(user), password(pass) {}
    virtual ~Account() {};

    string getUsername() const;
    string getPassword() const;
    bool checkPassword(const string& pass) const;
    virtual void displayMenu() = 0;
};
// lấy tên admin
string Account::getUsername() const {
    return username;
}
// lấy mật khẩu admin
string Account::getPassword() const {
    return password;
}
// kiểm tra mật khẩu admin thứ i và mật khẩu nhập có giống nhau không
bool Account::checkPassword(const string& pass) const {
    return password == pass;
}

// =================== NGƯỜI DÙNG ===================
class BankUser : public Account {
private:
    double balance;
    // vector dùng con trỏ thông minh để truy cập và chỉnh sửa trực tiếp vector gốc mà không tạo bản sao
    vector<shared_ptr<BankUser>>& allUsers;
public:
    BankUser(const string& user, const string& pass, vector<shared_ptr<BankUser>>& usersRef, double bal = 0)
        : Account(user, pass), balance(bal), allUsers(usersRef) {}

    void checkBalance() const;
    void displayMenu() override;
    ~BankUser() override {};

    BankUser& operator+=(double amount);
    BankUser& operator-=(double amount);
    friend BankUser& operator>>(BankUser& from, BankUser& to);
    friend istream& operator>>(istream& in, BankUser& user);
};
// dùng để người dùng nhập thông tin để đăng nhập 
istream& operator>>(istream& in, BankUser& user) {
    setColor(8);
    cout << "Ten dang nhap (nguoi dung): ";
    setColor(7);
    in >> user.username;
    setColor(8);
    cout << "Mat khau: ";
    setColor(7);
    in >> user.password;
    return in;
}
// dùng để tính tiền khi nạp tiền vào
BankUser& BankUser::operator+=(double amount) {
    if (amount > 0) {
        balance += amount;
        setColor(10);
        slowPrint("Nap tien thanh cong.\n");
    }
    else {
        setColor(12);
        cout << "So tien khong hop le.\n";
    }
    setColor(7);
    return *this;
}
// dùng để tính tiền khi chuyển tiền 
BankUser& BankUser::operator-=(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        setColor(10);
        slowPrint("Rut tien thanh cong.\n");
    }
    else {
        setColor(12);
        cout << "So tien khong hop le hoac khong du.\n";
    }
    setColor(7);
    return *this;
}
// dùng để tính tiền sau khi chuyển cả user chuyển tiền và user nhận tiền 
BankUser& operator>>(BankUser& from, BankUser& to) {
    double amount;
    setColor(8);
    cout << "Nhap so tien muon chuyen: ";
    setColor(7);
    cin >> amount;
    if (amount > 0 && from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
        setColor(10);
        slowPrint("Chuyen tien thanh cong.\n");
    }
    else {
        setColor(12);
        cout << "Chuyen tien that bai.\n";
    }
    setColor(7);
    return from;
}
// dùng để kiểm tra số dư
void BankUser::checkBalance() const {
    setColor(8);
    cout << "So du hien tai: ";
    setColor(3);
    cout << balance << " VND\n";
    Sleep(3000);
}
// dùng để hiển thị bảng menu các chức năng người dùng 
void BankUser::displayMenu() {
    vector<string> menu = {
        "Nap tien",
        "Rut tien",
        "Kiem tra so du",
        "Chuyen tien",
        "Dang xuat"
    };
    int choice;
    do {
        choice = interactiveMenu(menu, "--- MENU NGUOI DUNG ---");
        switch (choice) {
        case 0: {
            double amount;
            setColor(8);
            cout << "Nhap so tien nap: ";
            setColor(7);
            cin >> amount;
            *this += amount;
            break;
        }
        case 1: {
            double amount;
            setColor(8);
            cout << "Nhap so tien rut: ";
            setColor(7);
            cin >> amount;
            *this -= amount;
            break;
        }
        case 2:
            checkBalance();
            break;
        case 3: {
            string target;
            setColor(8);
            cout << "Nhap ten nguoi nhan: ";
            setColor(7);
            cin >> target;
            bool found = false;
            for (auto& u : allUsers) {
                if (u->getUsername() == target) {
                    *this >> *u;
                    found = true;
                    break;
                }
            }
            setColor(12);
            if (!found) slowPrint("Khong tim thay nguoi nhan.\n");
            setColor(7);
            break;
        }
        }
    } while (choice != 4);
    slowPrint("Dang xuat...");
}

// =================== ADMIN ===================
class Admin : public Account {
private:
    // vector dùng con trỏ thông minh để truy cập và chỉnh sửa trực tiếp vector gốc mà không tạo bản sao
    vector<shared_ptr<BankUser>>& users;
public:
    Admin(const string& user, const string& pass, vector<shared_ptr<BankUser>>& userList)
        : Account(user, pass), users(userList) {}
    ~Admin() override {};

    void addUser();
    void removeUser();
    void listUsers() const;
    void displayMenu() override;
    friend istream& operator>>(istream& in, Admin& admin);
};
// dùng để admin nhập thông tin để đăng nhập 
istream& operator>>(istream& in, Admin& admin) {
    setColor(8);
    cout << "Ten dang nhap (admin): ";
    setColor(7);
    in >> admin.username;
    setColor(8);
    cout << "Mat khau: ";
    setColor(7);
    in >> admin.password;
    return in;
}
// dùng để thêm user mới 
void Admin::addUser() {
    string uname, pword;
    setColor(8);
    cout << "Nhap ten dang nhap moi: ";
    setColor(7);
    cin >> uname;
    setColor(8);
    cout << "Nhap mat khau: ";
    setColor(7);
    cin >> pword;
    // sau khi thêm sẽ đưa vô vector users
    users.push_back(make_shared<BankUser>(uname, pword, users));
    setColor(10);
    slowPrint("Them nguoi dung thanh cong.\n");
}
// dùng để xóa user 
void Admin::removeUser() {
    string uname;
    setColor(8);
    cout << "Nhap ten nguoi dung can xoa: ";
    setColor(7);
    cin >> uname;
    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getUsername() == uname) {
            // sau khi tìm ra được user cần xóa thì sẽ xóa
            users.erase(it);
            setColor(10);
            slowPrint("Xoa nguoi dung thanh cong.\n");
            return;
        }
    }
    setColor(12);
    slowPrint("Khong tim thay nguoi dung.\n");
    setColor(7);
}
// dùng để xem danh sách các user
void Admin::listUsers() const {
    setColor(8);
    cout << "--- DANH SACH NGUOI DUNG ---\n";
    setColor(15);
    for (const auto& u : users) {
        cout << " - " << u->getUsername() << '\n';
    }
    Sleep(5000);
}
// dùng để hiển thị bảng menu chức năng admin
void Admin::displayMenu() {
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
    } while (choice != 3);
    slowPrint("Dang xuat...");
}

// =================== HỆ THỐNG CHÍNH ===================
class BankSystem {
private:
    // vector dùng con trỏ thông minh để tự động quản lý bộ nhớ
    vector<shared_ptr<BankUser>> users;
    vector<shared_ptr<Admin>> admins;
public:
    BankSystem();
    ~BankSystem() {
        users.clear();
        admins.clear();
    }

    void login();
    void run();
};
// tạo các tài khoản admin, user sẵn 
BankSystem::BankSystem() {
    admins.push_back(make_shared<Admin>("admin1", "123", users));
    admins.push_back(make_shared<Admin>("admin2", "123", users));
    users.push_back(make_shared<BankUser>("user1", "123", users, 100000));
    users.push_back(make_shared<BankUser>("user2", "123", users, 100000));
    users.push_back(make_shared<BankUser>("user3", "123", users, 100000));
}
// dùng để đăng nhập admin và user 
void BankSystem::login() {
    vector<string> loginTypes = { "Dang nhap Admin", "Dang nhap Nguoi dung", "Quay lai" };
    int role = interactiveMenu(loginTypes, "--- CHON VAI TRO DANG NHAP ---");

    if (role == 0) { // Admin
        Admin adminInput("", "", users);
        cin >> adminInput;
        for (auto& admin : admins) {
            if (adminInput.getUsername() == admin->getUsername() && admin->checkPassword(adminInput.getPassword())) {
                setColor(10);
                slowPrint("Dang nhap thanh cong (admin).\n");
                setColor(7);
                admin->displayMenu();
                return;
            }
        }
    }
    else if (role == 1) { // User
        BankUser userInput("", "", users);
        cin >> userInput;
        for (auto& user : users) {
            if (userInput.getUsername() == user->getUsername() && user->checkPassword(userInput.getPassword())) {
                setColor(10);
                slowPrint("Dang nhap thanh cong (nguoi dung).\n");
                setColor(7);
                user->displayMenu();
                return;
            }
        }
    }
    if (role != 2) {
        setColor(12);
        slowPrint("Sai ten dang nhap hoac mat khau.\n");
        setColor(7);
    }
}
// dùng để vào giao diện khi vừa chạy code 
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
int main() {
    BankSystem system;
    system.run();
    return 0;
}
