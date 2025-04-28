#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class Nguoi{
    string hoten, quequan;
    int namsinh;
public:
    string getHoTen(){  return hoten; }
    string getQueQuan(){ return quequan;}
    int getNamSinh(){ return namsinh;}
    Nguoi(string h="hoten", int ns=2000, string qq="quequan"){
        hoten=h; namsinh = ns; quequan = qq;
    }
    Nguoi(const Nguoi &n){
        hoten = n.hoten; namsinh= n.namsinh; quequan = n.quequan;
    }
    friend istream  &operator >>(istream &is, Nguoi &n){
        getline( is, n.hoten);
        is >> n.namsinh; cin.ignore(); //nhap so xong nhap chuoi
        getline( is, n.quequan);
        return is;
    }
    friend ostream &operator << (ostream &os, Nguoi n){
        os<< "Ho Ten: " << n.hoten <<endl;
        os<< "Nam Sinh: " << n.namsinh<<endl;
        os<< "Que quan: " << n.quequan<<endl;
        return os;
    }
};

class SV: public Nguoi{
    string khoa;
    float diem[10];
    int ndiem;
public:    
    //get
    SV(string h="hoten", int ns=2000, string qq="quequan",
        string k="khoa", int _ndiem=1, float _diem[]= new float[1]{1})
        :Nguoi ( h, ns, qq){
            khoa = k; ndiem = _ndiem;
            for(int i=0; i<ndiem; i++) diem[i] = _diem[i];
        }
    SV(const SV & s): Nguoi(s) {
        khoa = s.khoa; ndiem = s.ndiem;
        for(int i=0; i<ndiem; i++) diem[i] = s.diem[i];
    }
    friend istream  &operator >>(istream &is, SV &s){
        //getline(is, s.hoten);
        string h, qq, k; 
        int ns, ndiem=0;
        float diem[10];
        getline( is, h);
        is >> ns; cin.ignore(); //nhap so xong nhap chuoi
        getline( is, qq);     getline( is, k);
        while(is>> diem[ndiem]) ndiem++;
        
        s = SV( h, ns, qq, k, ndiem, diem); //khoi tao!!
        return is;
    }
    friend ostream &operator << (ostream &os, SV s){
        os<< "Ho Ten: " << s.getHoTen() <<endl;
        os<< "Nam Sinh: " << s.getNamSinh()<<endl;
        os<< "Que quan: " << s.getQueQuan()<<endl;
        os<< "Khoa: "<< s.khoa << endl;
        os<< "Diem cac mon: ";
        for(int i=0; i<s.ndiem; i++) os << s.diem[i]<<" ";
        os<< "\nDiem trung binh: "<< fixed << setprecision(2)<< s.DTB() <<endl;    
        return os;
    }
    float DTB(){
        float kq=0;
        for(int i=0; i< ndiem; i++) kq += diem[i];
        return kq / ndiem;
    }

};
int main(){
    SV n; cin >> n; cout<<n;
    return 0;
}