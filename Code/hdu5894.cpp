#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL Quick_Pow(LL a,LL b){
  //printf("a=%db=%dc=%d\n",a,b,c);
  LL ans=1;
  while (b){
    if (b&1)ans=(ans*a)%MOD;
    a=(a*a)%MOD;
    b>>=1;
  }
  return ans;
}
LL C(LL n,LL m){
  LL ans=1;
  if (n<m)return 0;
  for (LL i=1; i<=m; ++i)
    ans=ans*(((n-m+i)*Quick_Pow(i,MOD-2))%MOD)%MOD; //注意*和%的优先级.
  return ans;
}
LL Lucas(LL n,LL m){
  if (!m)return 1;
  else return Lucas(n/MOD,m/MOD)*C(n%MOD,m%MOD)%MOD;
}
int main(){
  LL n,m,k;
  int t;
  scanf("%d",&t);
  while (t--){
    scanf("%lld%lld%lld",&n,&m,&k);
    //printf("%lld",C(n-1-k*m,m-1));
    if (m==1)printf("%lld\n",n); //特判一个人的情况.
    else
    printf("%lld\n",((n*C(n-1-k*m,m-1)%MOD)*Quick_Pow(m,MOD-2))%MOD);
  }
}
