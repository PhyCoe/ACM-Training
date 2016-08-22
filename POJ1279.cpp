#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAX=2005;
struct Point{
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
  pp.x=(-c*b1+c1*b)/(a*b1-b*a1),pp.y=(-a*c1+a1*c)/(a*b1-a1*b);
  return pp;
}
void cut(){
  int cnt=0;
  for (int i=1; i<=m; ++i){
    if (a*f[i].x+b*f[i].y+c>=0){
      pre[cnt++]=f[i];
    }
    else {
      if (a*f[i-1].x+b*f[i-1].y+c>0){
        pre[cnt++]=GetSegmentPoint(f[i],f[i-1]);
      }
      if (a*f[i+1].x+b*f[i+1].y+c>0){
        pre[cnt++]=GetSegmentPoint(f[i],f[i+1]);
      }
    }
  }
  m=cnt;
  for (int i=0; i<cnt; ++i){
    f[i+1]=pre[i];
  }
  f[cnt+1]=pre[0];
  f[0]=pre[cnt-1];
}
double Cross(Point x,Point y,Point z){
  return (x.x-y.x)*(z.y-y.y)-(x.y-y.y)*(z.x-y.x);
}
double GetArea(Point *p){
  double area=0;
  for (int i=2; i<m; ++i){
    area+=Cross(p[i],p[1],p[i+1]);
  }
  return fabs(area/2.0);
}
int main(){
  int t;
  scanf("%d",&t);
  while (t--){
    scanf("%d",&n);
    for (int i=1; i<=n; ++i){
      scanf("%lf%lf",&num[i].x,&num[i].y);
      f[i]=num[i];
    }
    m=n;
    num[n+1]=num[1];
    f[0]=num[n],f[n+1]=num[1];
    for (int i=1; i<=n; ++i){
      GetLine(num[i],num[i+1]);
      cut();
    }
   /* printf("%d\n",m);
    for (int i=1; i<=m; ++i){
      printf("%f %f\n",f[i].x,f[i].y);;
    }*/
    printf("%.2f\n",GetArea(f));
  }
}
