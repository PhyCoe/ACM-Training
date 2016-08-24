/*************************************************************************
     File Name: UVALive6909.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年08月24日 星期三 20时11分43秒
 ************************************************************************/
#include<bits/stdc++.h>
using namespace std;
const int MAX=505;
const int MOD=1e9+7;
typedef long long LL;
LL C[MAX][MAX],A[MAX];
void Init(){
  for (int i=0; i<MAX; ++i) C[i][0]=1;//RE
  for (int i=1; i<MAX; ++i){
    for (int j=1; j<=i; ++j){
      C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
    }
  }
  A[0]=1;
  for (int i=1; i<MAX; ++i){
    A[i]=A[i-1]*i%MOD;
  }
}
int main(){
  int t,n,k,p,q;
  scanf("%d",&t);
  Init();
  for (int q=1; q<=t; ++q){
    LL ans=0;
    scanf("%d%d%d",&n,&k,&p);
    if (n-p<k)ans=C[k-1][n-p]*A[n-p]%MOD*C[p-1][k-1-(n-p)]%MOD*A[k-1-(n-p)]%MOD;
    for (int l=1; l<=n-k; ++l){
      for (int j=1; j<=min(n-p,l); ++j){
        ans+=C[n-p][j]*C[p-1][l-j]%MOD*A[n-l-1]%MOD; 
        ans%=MOD;
      }
    }
    printf("Case #%d: %lld\n",q,ans);
  }
}
