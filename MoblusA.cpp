/*************************************************************************
     File Name: MoblusA.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年08月26日 星期五 12时25分57秒
 ************************************************************************/
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAX=1e6+5;
LL mu[MAX],prim[MAX];
int v[MAX],cnt;
void Init(){
  cnt=0;
  mu[1]=1;
  for (int i=2; i<MAX; ++i){
    if (!v[i]){
      prim[cnt++]=i;
      mu[i]=-1;
    }
    for (int j=0; j<cnt&&prim[j]*i<MAX; ++j){
      v[i*prim[j]]=1;
      if (i%prim[j]==0){
        mu[i*prim[j]]=0;
        break;
      }
      mu[i*prim[j]]=-mu[i];
    }
  }
}
int main(){
  int t;
  LL n;
  scanf("%d",&t);
  Init();
  while (t--){
    scanf("%lld",&n);
    LL ans=3;// C(3,2);
    for (int i=1; i<=n; ++i){
      ans+=mu[i]*(n/i)*(n/i)*((n/i)+3);//C(3,1);
    }
    printf("%lld\n",ans);
  }
}
