#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL c;
// 矩阵求迭代公式 f(n)=2*f(n-1)+f(n-2);
// g(n)=f(n)*f(n+1)/2;
struct Matrix{
  LL x11,x12,x21,x22;
}; 

Matrix Multi_Matrix(Matrix a,Matrix b){
  Matrix z;
  z.x11=(a.x11*b.x11+a.x12*b.x21)%(2*c);
  z.x12=(a.x11*b.x12+a.x12*b.x22)%(2*c);
  z.x21=(a.x21*b.x11+a.x22*b.x21)%(2*c);
  z.x22=(a.x21*b.x12+a.x22*b.x22)%(2*c);
  return z;
}

LL Matrix_Pow(LL x){
  x-=3;
  Matrix A,B;
  A.x11=B.x11=2,A.x12=A.x21=B.x12=B.x21=1,A.x22=B.x22=0;
  while (x){
    if (x&1)A=Multi_Matrix(A,B);
    B=Multi_Matrix(B,B);
    x>>=1;
  }
  return (A.x11*2+A.x21)%(2*c);
}

LL F(LL x){
  if (!x)return 0;
  else if (x==1)return 1;
  else if (x==2)return 2;
  else return Matrix_Pow(x);
}

// A^B%C ,A^(B%phi(C)+phi(C))%C;
// (a/b)%c , 若b|a,(a/b)%c == a%(b*c)/b; 恰好此题满足,若不满足只能求逆元了.
LL Euler(int n){
  LL ans=n;
  int a=n;
  for (int i=2; i*i<=a; ++i){
    if (a%i==0){
      ans=ans/i*(i-1);
      while (a%i==0)a/=i;
    }
  }
  if (a>1)ans=ans/a*(a-1);
  return ans;
}

LL Multi_Mod(LL x,LL y,LL MOD){
  LL ans=1;
  while (y){
    if (y&1) ans=(ans*x)%MOD;
    x=(x*x)%MOD;
    y>>=1;
  }
  return ans;
}
int main(){
  int t;
  LL n,y,x,s,b;
  scanf("%d",&t);
  while (t--){
    scanf("%lld%lld%lld%lld",&n,&y,&x,&s);
    c=Euler(s+1);
    //cout<<F(5)<<endl;
    b=F(n*y)*F(n*y+1)/2+c;
    printf("%lld\n",Multi_Mod(x,b,s+1));
  }
}
