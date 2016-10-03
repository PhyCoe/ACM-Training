/*************************************************************************
     File Name: Codeforces722C.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年10月03日 星期一 07时58分25秒
 ************************************************************************/
#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+5;
typedef long long LL;

LL a[MAX],sum[MAX],ans[MAX];
int boss[MAX],p[MAX],v[MAX];

int  Find(int x){
  return boss[x]==x?x:boss[x]=Find(boss[x]);
}
void Union(int x,int y){
  int fx=Find(x),fy=Find(y);
  if (fx!=fy)boss[fx]=fy,sum[fy]+=sum[fx];
}
int main(){
  int n;
  scanf("%d",&n);
  for (int i=1; i<=n; ++i){
    scanf("%lld",a+i);
    sum[i]=a[i];
    boss[i]=i;
  }
  for (int i=1; i<=n; ++i){
    scanf("%d",p+i);
  }
  LL tmp=0;
  memset(v,0,sizeof v);
  for (int i=n; i>=1; --i){
    v[p[i]]=1;
    if (v[p[i]-1])Union(p[i]-1,p[i]);
    if (v[p[i]+1])Union(p[i]+1,p[i]);
    tmp=max(sum[Find(p[i])],tmp);
   // printf("%lld\n",tmp);
    ans[i-1]=tmp;
  }
  for (int i=1; i<n; i++)printf("%lld\n",ans[i]);
  printf("0\n");
}
