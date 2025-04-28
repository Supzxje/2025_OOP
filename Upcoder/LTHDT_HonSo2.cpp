#include<bits/stdc++.h>
using namespace std;

class phanso{
    protected:
    int t,m;
    public:
    phanso(int _t = 0,int _m = 1){
        t = _t;
        m = _m;
    }
    phanso( const phanso &s){
        t=s.t;
        m=s.m;
    }
    friend istream& operator >> ( istream &is, phanso &s){
        is>>s.t>>s.m;
        return is;
    }
    friend ostream& operator << ( ostream &os, phanso s){
        if(s.m<0) s.m=-s.m, s.t=-s.t;
        os<<s.t<<"/"<<s.m;
        return os;
    }
    int getTu(){ return t;}
    int getMau(){ return m;}
};
class honso: public phanso{
    int n;
    public:
    honso( int _n=0 , int _t=0, int _m=1){
        n=_n;
        t=_t;
        m=_m;
    }
    honso( const honso &x){
        n=x.n;
        t=x.t;
        m=x.m;
    }
    friend istream& operator >>( istream &is, honso &p){
        is >> p.n >> p.t>>p.m;
        return is;
    }
    friend ostream& operator <<( ostream &os, honso p){
        if( p.m<0) p.m=-p.m, p.t=-p.t;
        os << p.n <<" "<<p.t<<"/"<<p.m;
        return os;
    }
    honso operator +( honso h){
        honso k;
        if(h.n <0 && n<0){
            k.n= n + h.n;
            k.t= t*h.m + h.t*m;
            k.m= m* h.m;
            k.t=-k.t;
        }
        else if( h.n <0){
            h.t=-h.t;
            k.n= n + h.n;
            k.t= t*h.m + h.t*m;
            k.m= m* h.m;
        }
        else if( n <0){
            t=-t;
            k.n= n + h.n;
            k.t= t*h.m + h.t*m;
            k.m= m* h.m;
        }
        else {
            k.n= n + h.n;
            k.t= t*h.m + h.t*m;
            k.m= m* h.m;
        }
        int e=__gcd(k.t,k.m);
        k.t/=e;
        k.m/=e;
        return k;
    }
    
};

int main(){
    honso s,x;
    cin>>s>>x;
    cout<<s+x;
}