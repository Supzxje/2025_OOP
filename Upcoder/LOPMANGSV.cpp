#include<bits/stdc++.h>
using namespace std;
int i=0,n;
class sv{
  double a[100],kq;
  string ten,msv;
  public:
  friend istream& operator>>(istream& is,sv &s){
    i=0;
    //is.ignore();
    getline(is,s.ten);
    getline(is,s.msv);
    while(is>>s.a[i]) i++;
    is.clear();
    return is;
  }
  friend ostream& operator<<(ostream& os,sv &s){
    os<<"Ho Ten: "<<s.ten<<endl;
    os<<"Ma Sinh Vien: "<<s.msv<<endl;
    os<<"DTB: "<<setprecision(1)<<fixed<<s.kq;
    return os;
  }
  friend int dtb(sv &s){
      s.kq=0;
      for(int j=0;j<i;j++){
          s.kq+=s.a[j];
      }
      s.kq/=i;
  }
  friend bool operator<( sv s,sv x ){
      return s.kq<x.kq;
  }
};
sv m[100];
int main(){
    cin>>n;
    cin.ignore();
    cin>>m[0];
    dtb(m[0]);
    sv maxx =m[0];
    for(int j=1;j<n;j++){
        cin>>m[j];
        dtb(m[j]);
        if( maxx < m[j] ) maxx=m[j];
    }
    cout<<maxx;
}