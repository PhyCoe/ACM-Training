/*************************************************************************
     File Name: 732D.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年10月18日 星期二 10时19分22秒
 ************************************************************************/
#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+5;
int d[MAX],a[MAX],p[MAX],s[MAX],n,m;
struct Node{
  int x,y,z;
  Node(int xx,int yy,int zz): x(xx),y(yy),z(zz){}
  bool operator <(const Node &a) const {
    return z>a.z;
  }
};
bool check(int x){
  priority_queue<Node>pq;
  memset(p,0,sizeof p);
  memset(s,0,sizeof s);
  for (int i=x; i>=1; --i){
    if (d[i]&&!p[d[i]]){
      p[d[i]]=i;
      pq.push(Node(a[d[i]],d[i],p[d[i]]));
    }
  }
  int sub=pq.size();
  if (sub<m)return 1;
  for (int i=1; i<=x; ++i){
    int c=pq.top().y;
    if (d[i]&&p[d[i]]==i){
      if (s[d[i]]<a[d[i]]){
        return 1;
      }
    }
    else{
      s[c]++;
      if (s[c]==a[c])pq.pop();
    }
  }
  sub=pq.size();
  if (sub==0)return 0;
}
int main(){
  int l,r,mid;
  scanf("%d%d",&n,&m);
  for (int i=1; i<=n; ++i){
    scanf("%d",d+i);
  }
  l=m,r=n;
  for (int i=1; i<=m; ++i){
    scanf("%d",a+i);
    l+=a[i];
  }
  while (l<r+1){
    mid=(l+r)/2;
    if (check(mid)) l=mid+1;
    else r=mid-1;
  }
  if (l>=n+1)printf("-1\n");
  else printf("%d\n",l);
}
