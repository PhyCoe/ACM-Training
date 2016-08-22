#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAX=1e4;
const double EPS=1e-10;
struct Point {
  double x,y;
}num[MAX],pre[MAX],f[MAX];
double a,b,c,a1,b1,c1;
int n,m;
void GetLine(Point x,Point y){
  a=y.y-x.y,b=x.x-y.x,c=y.x*x.y-y.y*x.x;
}
Point GetSegmentPoint(Point x,Point y){
  a1=y.y-x.y,b1=x.x-y.x,c1=y.x*x.y-y.y*x.x;
  Point pp;
  pp.x=(c1*b-c*b1)/(a*b1-b*a1),pp.y=(c*a1-a*c1)/(a*b1-a1*b);
  return pp;
}
void cut(){
  int cnt=0;
  for (int i=1; i<=m; ++i){
    if (a*f[i].x+b*f[i].y+c<=0.0){
      pre[cnt++]=f[i];
    }
    else {
      if (a*f[i-1].x+b*f[i-1].y+c<0.0){
        pre[cnt++]=GetSegmentPoint(f[i],f[i-1]);
      }
      if (a*f[i+1].x+b*f[i+1].y+c<0.0){
        pre[cnt++]=GetSegmentPoint(f[i],f[i+1]);
      }
    }
  }
  for (int i=0; i<cnt; ++i){
    f[i+1]=pre[i];
  }
  f[0]=pre[cnt-1];
  f[cnt+1]=pre[0];
  m=cnt;
}
bool judge(double mid){
  m=4;
  f[0].x=MAX,f[0].y=MAX;
  f[1].x=-MAX,f[1].y=MAX;
  f[2].x=-MAX,f[2].y=-MAX;
  f[3].x=MAX,f[3].y=-MAX;
  f[4].x=MAX,f[4].y=MAX;
  f[5].x=-MAX,f[5].y=MAX;
  for (int i=1; i<=n; ++i){
    GetLine(num[i],num[i+1]);
    c+=mid*sqrt(a*a+b*b);
    cut();
    if (!m)break ;
  }
  return m>0;
}
int main(){
  while (~scanf("%d",&n),n){
    memset(num,0,sizeof num);
    memset(pre,0,sizeof pre);
    memset(f,0,sizeof f);
    for (int i=1; i<=n; ++i){
      scanf("%lf%lf",&num[i].x,&num[i].y);
    }
    num[n+1]=num[1];
    double l=0,r=MAX,mid;
    while (r-l>=EPS){
      mid=(l+r)/2;
      if (judge(mid))l=mid;
      else r=mid;
    }
    printf("%f\n",l);
  }
}
