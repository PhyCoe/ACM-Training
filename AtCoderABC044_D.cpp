/*************************************************************************
     File Name: AtCoderABC044_D.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年08月29日 星期一 07时49分14秒
 ************************************************************************/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL f(LL n,LL b){
  LL ans=0;
  while (n){
    ans+=n%b;
    n/=b;
  }
  return ans;
}
int main(){
  LL n,s;
  scanf("%lld%lld",&n,&s);
  if (n<s){
    printf("-1\n");
    return 0;
  }
  if (s==n) {
    printf("%lld\n",n+1);
    return 0;
  }
  for (LL b=2; b*b<=n; ++b){
    if (f(n,b)==s){
      printf("%lld\n",b);
      return 0;
    }
  }
  for (LL p=(LL)sqrt(n); p>=1; --p){
    LL b=(n-s)/p+1;
    if (b==1)continue;
    if (f(n,b)==s){
      printf("%lld\n",b);
      return 0;
    }
  }
  printf("-1\n");
}
