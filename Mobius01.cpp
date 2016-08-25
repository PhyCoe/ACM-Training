/*************************************************************************
     File Name: Mobius01.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年08月25日 星期四 15时42分53秒
 ************************************************************************/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;
typedef long long LL;
const int MAX=1e5+5;
LL prim[MAX],mu[MAX];
int v[MAX],cnt;
void Init(){
  mu[1]=1;
  cnt=0;
  for (int i=2; i<MAX; ++i){
    if (!v[i]){
      prim[cnt++]=i;
      mu[i]=-1; //一个素数.
    }
    for (int j=0; j<cnt&&prim[j]*i<MAX; ++j){
        v[i*prim[j]]=1;
        if (i%prim[j]==0){
        mu[i*prim[j]]=0; //有相同素因子.
        break;
        }
        mu[i*prim[j]]=-mu[i]; //
    }
    mu[i]+=mu[i-1];
  }
}
int main(){
  int t;
  LL a,b,c,d,k;
  scanf("%d",&t);
  Init();
  for (int q=1; q<=t; ++q){
    scanf("%lld%lld%lld%lld%lld",&a,&b,&c,&d,&k);
    if (b>d)swap(b,d);
    if (!k){
      printf("Case %d: 0\n",q);
      continue;
    }
    b/=k,d/=k;
    LL ans=0,ans1=0;
    int j;
    for (int i=1; i<=b; i=j+1){
      j=min(b/(b/i),d/(d/i));//分块加速根号的复杂度??
      ans+=(mu[j]-mu[i-1])*(b/i)*(d/i);
    }
    for (int i=1; i<=b; i=j+1){
      j=b/(b/i);
      ans1+=(mu[j]-mu[i-1])*(b/i)*(b/i);
    }
    printf("Case %d: %lld\n",q,ans-ans1/2);
  }
}
