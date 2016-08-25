/*************************************************************************
     File Name: MobiusF.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年08月25日 星期四 20时48分32秒
 ************************************************************************/
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAX=1e5+5;
LL f[MAX];
int main(){
  LL n,m;
  scanf("%lld%lld",&n,&m);
  if (n>m)swap(n,m);
  LL ans=0;
  for (int i=n; i>=1; --i){
    f[i]=(n/i)*(m/i);
    for (int j=2*i; j<=n; j+=i){
      f[i]-=f[j];
    }
   // printf(" %d %lld\n",i,f[i]);
    ans+=f[i]*((i-1)*2+1);
  }
  printf("%lld\n",ans);
}
