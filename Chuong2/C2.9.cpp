#include <iostream>
#include <stack>
using namespace std;

class Stack{
    stack<int> stk;
public:

    friend istream& operator>>(istream& is, Stack& s);
    friend ostream& operator<<(ostream& os, const Stack& s);
};

istream& operator>>(istream& is, Stack& s){
    int size, x;
    is >> size;

    for(int i = 0; i < size;i++){
        is >> x;
        
    }
}

ostream& operator<<(ostream& os, const Stack& s){
    while(!s.stk.empty()){
        s.stk.top();
        s.stk.pop();
    }
    return os;
}

