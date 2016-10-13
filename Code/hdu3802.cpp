/*************************************************************************
     File Name: hdu3802.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年10月13日 星期四 12时54分08秒
 ************************************************************************/
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL a,b,n,pp,MOD;

struct Matrix{
  LL x[2][2];
};

Matrix Multi_Matrix(Matrix a,Matrix b){
  Matrix c;
  memset(c.x,0,sizeof c.x);
  for (int i=0; i<2; ++i){
    for (int j=0; j<2; ++j){
      for (int k=0; k<2; ++k){
        c.x[i][j]+=(a.x[i][k]*b.x[k][j])%MOD;
      }
    }
  }
  return c;
}

LL Multi_mod(LL n){
  Matrix ans,a;
  for (int i=0; i<2; ++i){
    for (int j=0; j<2; ++j){
      ans.x[i][j]=a.x[i][j]=1;
    }
  }
  ans.x[1][1]=a.x[1][1]=0;
  while (n){
    if (n&1) ans=Multi_Matrix(ans,a);
    n>>=1;
    a=Multi_Matrix(a,a);
  }
  return (ans.x[0][0]+ans.x[0][1])*2%MOD;
}

LL euler(LL n){
  LL res=n,a=n;
  for (LL i=2; i*i<=a; ++i){
    if (a%i==0){
      res=res/i*(i-1);
      while (a%i==0)a/=i;
    }
  }
  if (a>1){
    res=res/a*(a-1);
  }
  return res;
}
LL F(LL n){
  if (n<2)return 2;
  else return Multi_mod(n-2);
}

LL pow_mod(LL a,LL n,LL p){
  LL ans=1;
  while (n){
    if (n&1)ans=ans*a%p;
    n>>=1;
    a=a*a%p;
  }
  return ans;
}
LL legendre(LL a,LL p){
  return pow_mod(a,(p-1)>>1,p);
}
LL mod(LL a,LL p){
  a%=p;
  return a<0?a+=p:a;
}
struct Node{
  static LL p,omega;
  LL a,b;
  Node(LL a,LL b): a(a%p),b(b%p){}
};
Node operator*(const Node &p,const Node &q){
  LL m=Node::p;
  return Node(p.a*q.a+p.b*q.b%m*Node::omega,p.a*q.b+q.a*p.b);
}
Node Node_pow_mod(Node a,LL n){
  Node res(1,0);
  while (n){
    if (n&1) res=res*a;
    a=a*a;
    n>>=1;
  }
  return res;
}
//求二次剩余.
LL Node::p,Node::omega;
LL modsqr(LL a,LL p){
  if (p==2)return 1;
  if (legendre(a,p)+1==p) return -1;
  if (((p+1)>>1)%2==0) return pow_mod(a,(p+1)>>2,p);
  LL a_0=-1;
  while (1){
    a_0=rand()%p;
    if (legendre(mod(a_0*a_0-a,p),p)+1==p)break;
  }
  Node::p=p;
  Node::omega=mod(a_0*a_0-a,p);
  Node ret=Node_pow_mod(Node(a_0,1),(p+1)/2);
  return ret.a;
}
int main(){
  int k;
  scanf("%d",&k);
  //printf("phi(13)=%lld\n",euler(13));
  while (k--){
    scanf("%lld%lld%lld%lld",&a,&b,&n,&pp);
    MOD=euler(pp);
    LL xa=modsqr(a,pp),xb=modsqr(b,pp);
    if (xa==-1||xb==-1)printf("0\n");
    else{
      if (xa*2>pp)xa=pp-xa;
      if (xb*2>pp)xb=pp-xb;
      //printf("%lld %lld\n",xa,xb);
      //printf("%lld %lld  %lld \n",F(n),pow_mod(xa+xb,F(n),pp),pow_mod(xa-xb,F(n),pp));
      printf("%lld\n",(4*(pow_mod(xa+xb,F(n),pp)+pow_mod(xa-xb,F(n),pp))%pp)%pp);
    }
  }
}
