/*************************************************************************
     File Name: hdu5868.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年09月12日 星期一 09时14分57秒
 ************************************************************************/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
struct Matrix{
  LL x11,x12,x21,x22;
  // A[3][3];
};
// 矩阵求递推式f(n)=f(n-1)+f(n-2);
Matrix Multi_Matrix(Matrix a,Matrix b){//O(n^3)
  Matrix c;
  c.x11=(a.x11*b.x11+a.x12*b.x21)%MOD;
  c.x12=(a.x11*b.x12+a.x12*b.x22)%MOD;
  c.x21=(a.x21*b.x11+a.x22*b.x21)%MOD;
  c.x22=(a.x21*b.x12+a.x22*b.x22)%MOD;
  /*for (int k=1; k<=2; ++k){
    for (int i=1; i<=2; ++i){
      for (int j=1; j<=2; ++j){
        c.A[i][j]=(c.A[i][j]+a.A[i][k]*b.A[k][j])%MOD;
      }
    }
  }*/
  return c;
}
LL Matrix_MultiMod(LL x){//O(log2)
  Matrix A,B;
  A.x11=A.x12=A.x21=B.x11=B.x12=B.x21=1;
  A.x22=B.x22=0;
  while (x){
    if (x&1)A=Multi_Matrix(A,B);
    B=Multi_Matrix(B,B);
    x>>=1;
  }
  return (A.x11*4+A.x21*3)%MOD;
}
// 设f为不考虑旋转同构下的染色方案.
LL f(LL x){
  if (x==1)return 1;
  else if (x==2)return 3;
  else if (x==3)return 4;
  else return Matrix_MultiMod(x-=4);
}
LL Euler(LL n){
  LL ans,a;
  ans=a=n;
  for (LL i=2; i*i<=a; ++i){
    if (a%i==0){
      ans=ans/i*(i-1);
      while (a%i==0)a/=i;
    }
  }
  if (a>1)ans=ans/a*(a-1);
  return ans;
}
LL Multi_Mod(LL a,LL b){
  LL ans=1;
  while (b){
    if (b&1)ans=ans*a%MOD;
    a=a*a%MOD;
    b>>=1;
  }
  return ans;
}
LL Solve(LL x){
  if (x==1)return 2;
  LL ans=0,i;
  for (i=1; i*i<x; ++i){
    if (x%i==0)
    ans=(ans+f(i)*Euler(x/i)+f(x/i)*Euler(i))%MOD;
  }
  if (i*i==x)ans=(ans+f(i)*Euler(i))%MOD;
  return ans*Multi_Mod(x,MOD-2)%MOD;
}
int main(){
  LL x;
  while (~scanf("%lld",&x)){
    printf("%lld\n",Solve(x));
  } 
}
