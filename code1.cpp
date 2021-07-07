#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,k=0;      //n为要输入的数，k为n的二进制位数
    int a[100]={0};     //数组a[100]用来储存n的逆二进制数
    cin>>n;
    while(n){
        a[k++]=n%2;
        n/=2;
    }
    for(int i=0;i<k;i++){
        if(a[i]==0)
            cout<<'^';
        if(a[i]==1){
            if (a[i+1]==0&&i!=(k-1)){
                a[i]=0;
                cout<<'-'<<'^';
            }
            if(a[i+1]==1){
                int j = i;
                if(a[j]==1&&a[j+1]==1&&j==k-2){
                    cout<<'-'<<'^';
                }
                else{
                    cout<<'+'<<'^';
                    while(a[j]){
                        a[j] = 0;
                        j++;
                    }
                }
                a[j]=1;
            }
        }
    }
    return 0;
}

