#include<bits/stdc++.h>
using namespace std;
class Hinh{
    public:
    virtual int ChuVi() = 0;
};
class HCN: public Hinh{
    int dai, rong;
    public:
    int getDai() { return dai;}
    int getRong() { return rong;}
    void setDai( int val ) { dai=val;}
    void setRong( int val ) { rong=val;}
    
    HCN( int d=1, int r=1){
        dai=d;
        rong=r;
    }
    HCN( const HCN &hcn){
        dai=hcn.dai;
        rong=hcn.rong;
    }
    friend istream& operator >>( istream& is, HCN &hcn){
        is>> hcn.dai>> hcn.rong;
        return is;
    }
    friend ostream& operator <<( ostream& os, HCN &hcn){
        os<< hcn.ChuVi();
        return os;
    }
    void Set( int d, int r) { dai=d, rong=r;}
    int ChuVi(){
        return (dai+rong)*2;
    }
};
class HV : public HCN{
    int canh;
    public:
    HV( int c=1) {
        canh=c;
        Set( canh, canh);
    }
    HV( const HV& hv){
        canh=hv.canh;
        Set( canh, canh);
    }
    friend istream& operator >> ( istream& is, HV &hv){
        int c;
        is>> c;
        hv=HV(c);
        return is;
    }
    friend ostream& operator <<( ostream& os, HV hv){
        os<< hv.ChuVi();
        return os;
    }
};

int main(){
    HCN hinh[100];
    char c;
    int i=0;
    while(cin>>c){
        if(c=='a'){
            HV hv;
            cin>>hv;
            hinh[i]= hv;
        }
        else {
            HCN hcn;
            cin>>hcn;
            hinh[i]= hcn;
        }
        cout<<hinh[i].ChuVi()<<endl;
        i++;
    }
}