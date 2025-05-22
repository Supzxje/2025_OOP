#include <iostream>
#include <string>
#include <vector>
using namespace std;

// =================== TIỆN ÍCH HIỂN THỊ ===================
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void slowPrint(const string& text, int delayMs = 50) {
    for (char c : text) {
        cout << c << flush;
        Sleep(delayMs);
    }
    Sleep(2000);
    setColor(0);
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
                setColor(32);
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
            if (ch == 72) selected = (selected - 1 + options.size()) % options.size();
            if (ch == 80) selected = (selected + 1) % options.size();
        }
        else if (ch == 13) {
            return selected;
        }
    }
}

// =================== CLASS CƠ SỞ ===================
class Account{
    string username, password;
public:
    Account(string& Username, string& Password);
    ~Account(){};

    string getUsername();
    string getPassword();
    void setUsername(string user);
    void setPassword(string pass);

    
}