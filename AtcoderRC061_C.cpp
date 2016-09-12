/*************************************************************************
     File Name: AtcoderRC061_C.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年09月11日 星期一 21时53分38秒
 ************************************************************************/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL pow(int a,int b){
  LL ans=1;
  while (b){
    if (b&1)ans*=a;
    a*=a;
    b/=2;
  }
  return ans;
}
bool flag[15];
char str[15];
int main(){
  scanf("%s",str);
  int l=strlen(str);
  LL ans=0;
  for (int i=0; i<pow(2,l-1); ++i){
    memset(flag,0,sizeof flag);
    for (int j=0; j<l-1; ++j){
      if (pow(2,j)&i)flag[j]=1;
    }
    LL sum=0;
    for (int j=0; j<l; ++j){
      if (flag[j]){
        ans+=sum*10+str[j]-'0';
        sum=0;
      }
      else{
        sum*=10;
        sum+=str[j]-'0';
      }
    }
    ans+=sum;
  }
  printf("%lld\n",ans);
}
