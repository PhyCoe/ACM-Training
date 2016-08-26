/*************************************************************************
     File Name: MoblusH.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年08月26日 星期五 21时14分20秒
 ************************************************************************/
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAX=1e7+5;
LL prim[MAX],mu[MAX],g[MAX];
int v[MAX],cnt;
void Init(){
  cnt=0;
  mu[1]=1;
  g[1]=0;
  for (int i=2; i<MAX; ++i){
    if (!v[i]){
      mu[i]=-1;
      prim[cnt++]=i;
      g[i]=1; //一个素数.
    }
    for (int j=0; j<cnt&&prim[j]*i<MAX; ++j){
      v[i*prim[j]]=1;
      if (i%prim[j]==0){
        mu[i*prim[j]]=0;
        g[i*prim[j]]=mu[i]; // k|x,prim[j]|i.
        break;
      }
      mu[i*prim[j]]=-mu[i];
      g[i*prim[j]]=mu[i]-g[i];
    }
    g[i]+=g[i-1];
  }
}
int main(){
  int t;
  Init();
  scanf("%d",&t);
  LL n,m;
  while (t--){
    scanf("%lld%lld",&n,&m);
    int j;
    LL ans=0;
    for (int i=1; i<=min(n,m); i=j+1){
      j=min(n/(n/i),m/(m/i));
      ans+=(g[j]-g[i-1])*(n/i)*(m/i);
    }
    printf("%lld\n",ans);
  }
}
