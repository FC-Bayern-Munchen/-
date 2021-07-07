#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    int d1,d2,r,R;
    d1=b-a;
    d2=c-b;
    r=d1-d2;
    R=2*d2-d1;
    if(r<=0||R<=0){
        cout<<"-1";
        return 0;
    }
    else{
        cout<<2*r<<' '<<'1'<<' ';
        cout<<R<<' '<<'1'<<' ';
        cout<<r<<' '<<'1';
    }
    return 0;
}
