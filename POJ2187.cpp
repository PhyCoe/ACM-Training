/*************************************************************************
     File Name: POJ2187.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年08月23日 星期二 21时50分22秒
 ************************************************************************/
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;
const int MAX=5e4+5;
struct Point{
  int x,y;
}num[MAX],ch[MAX];
int n,m;
int Cross(Point x,Point y,Point z){
  return (x.x-y.x)*(z.y-y.y)-(x.y-y.y)*(z.x-y.x);
}
int Dis(Point x,Point y){
  return (x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y);
}
bool cmp(Point x,Point y){
  if (x.x==y.x)return x.y<y.y;
  else return x.x<y.x;
}
void ConvexHull(){
  sort(num,num+n,cmp);
  int cnt=0;
  for (int i=0; i<n; ++i){
    while (cnt>1&&Cross(ch[cnt-1],ch[cnt-2],num[i])<=0)cnt--;
    ch[cnt++]=num[i];
  }
  int k=cnt;
  for (int i=n-2; i>=0; --i){
    while (cnt>k&&Cross(ch[cnt-1],ch[cnt-2],num[i])<=0)cnt--;
    ch[cnt++]=num[i];
  }
  if (n>1)cnt--;
  m=cnt;
}
int Rotating_Calipers(){
  int ans=0,q=1;
  ch[m]=ch[0];
  for (int i=0; i<m; ++i){
    while (Cross(ch[i+1],ch[i],ch[q+1])>Cross(ch[i+1],ch[i],ch[q]))q=(q+1)%m;
    ans=max(ans,max(Dis(ch[i],ch[q]),Dis(ch[i+1],ch[q+1])));
  }
  return ans;
}
int main(){
  scanf("%d",&n);
  for (int i=0; i<n; ++i){
    scanf("%d%d",&num[i].x,&num[i].y);
  }
  ConvexHull();
  printf("%d\n",Rotating_Calipers());
}


