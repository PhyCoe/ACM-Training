/*************************************************************************
     File Name: POJ2451.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年08月23日 星期二 20时22分35秒
 ************************************************************************/
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int MAX=4e4+5;
const int INF=1e4;
struct Point {
  double x,y;
}num[MAX],f[MAX],pre[MAX];
double a,b,c,a1,b1,c1;
int m;
void GetLine(Point x,Point y){
  a=y.y-x.y,b=x.x-y.x,c=x.y*y.x-y.y*x.x;
}
Point GetSegmentPoint(Point x,Point y){
  a1=y.y-x.y,b1=x.x-y.x,c1=y.x*x.y-y.y*x.x;
  Point pp;
  pp.x=(c1*b-c*b1)/(a*b1-b*a1),pp.y=(c*a1-a*c1)/(a*b1-a1*b);
  return pp;
}
void cut(Point x,Point y){
  int cnt=0;
  for (int i=1; i<=m; ++i){
    if ((f[i].x-x.x)*(f[i].y-y.y)-(f[i].x-y.x)*(f[i].y-x.y)>=0){
      pre[cnt++]=f[i];
    }
    else {
      if ((f[i-1].x-x.x)*(f[i-1].y-y.y)-(f[i-1].x-y.x)*(f[i-1].y-x.y)>0){
        pre[cnt++]=GetSegmentPoint(f[i],f[i-1]);
      }
      if ((f[i+1].x-x.x)*(f[i+1].y-y.y)-(f[i+1].x-y.x)*(f[i+1].y-x.y)>0){
        pre[cnt++]=GetSegmentPoint(f[i],f[i+1]);
      }
    }
  }
  for (int i=0; i<cnt; ++i){
    f[i+1]=pre[i];
  }
  f[cnt+1]=pre[0];
  f[0]=pre[cnt-1];
  m=cnt;
}
double Cross(Point x,Point y,Point z){
  return (x.x-y.x)*(z.y-y.y)-(x.y-y.y)*(z.x-y.x);
}
double GetArea(){
  double ans=0;
  for (int i=2; i<=m; ++i){
    ans+=Cross(f[i],f[1],f[i+1]);
  }
  return fabs(ans/2);
}
int main(){
  int n;
  scanf("%d",&n);
  for (int i=1; i<=n*2; i+=2){
    scanf("%lf%lf%lf%lf",&num[i].x,&num[i].y,&num[i+1].x,&num[i+1].y);
  }
  f[0].x=0,f[0].y=INF;
  f[1].x=f[1].y=0;
  f[2].x=INF,f[2].y=0;
  f[3].x=INF,f[3].y=INF;
  f[4].x=0,f[4].y=INF;
  f[5].x=f[5].y=0;
  m=4;
  for (int i=1; i<=n*2; i+=2){
    GetLine(num[i],num[i+1]);
    cut(num[i],num[i+1]);
  }
  printf("%.1f\n",GetArea());
}
