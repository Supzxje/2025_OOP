#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Account{
    string username, password;

public:
    Account(string u = "",string p = "");

    Bool checkPassword(string u, string p);

    string getUsername();

    void showMenu() = 0;
}

Account::Account(string u = "",string p = ""){
    username = u;
    password = p;
}

Account::checkPassword(string u, string p){
    return(username == u && password == p);
}
