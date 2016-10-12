/*************************************************************************
     File Name: 724C.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年10月12日 星期三 21时42分39秒
 ************************************************************************/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF=1e18;
LL lcm,n,m;
LL ex_gcd(LL a,LL b, LL &x,LL &y){
  if (!b){
    x=1,y=0;
    return a;
  }
  LL ans=ex_gcd(b,a%b,x,y);
  LL temp=x;
  x=y,y=temp-a/b*y;
  return ans;
}

LL cal(LL x,LL y){
  LL X,Y,a,b;
  LL g=ex_gcd(2*n,2*m,X,Y);
  if ((y-x)%g)return INF;
  LL mod=4*m*n/g;
  X*=(y-x)/g;
  a=n*2*X+x;
  a=(a%mod+mod)%mod;
  if (!a)return mod;
  return a;
}

int main(){
  LL x,y,k;
  scanf("%lld%lld%lld",&n,&m,&k);
  lcm=n*m/__gcd(n,m);
  while (k--){
    scanf("%lld%lld",&x,&y);
    LL ans=min({cal(x,y),cal(x,2*m-y),cal(2*n-x,y),cal(2*n-x,2*m-y)});
    if (ans<=lcm)printf("%lld\n",ans);
    else printf("-1\n");
  }

}
