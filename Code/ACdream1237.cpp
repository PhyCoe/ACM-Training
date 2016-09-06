/*************************************************************************
     File Name: ACdream1237.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年09月05日 星期一 10时40分51秒
 ************************************************************************/
#include<bits/stdc++.h>
using namespace std;
const int MAX=1e4;
const double EPS=1e-5;//1e-8不给过?
int boss[MAX],v[MAX];
struct Point{
  double x,y;
  Point(double xx=0,double yy=0): x(xx),y(yy) {}
  bool operator==(Point a)const{
    return fabs(a.x-x)<EPS&&fabs(a.y-y)<EPS;
  }
  bool operator<(Point a)const{
    return y<a.y-EPS||y<a.y+EPS&&x<a.x-EPS;
  }
  void input(){
    scanf("%lf%lf",&x,&y);
  }
};
struct Circle{
  Point o;
  double r;
  bool operator<(const Circle c)const{
    return o<c.o||o==c.o&&r<c.r;
  }
  bool operator==(const Circle c)const{
    return o==c.o&&fabs(r-c.r)<EPS;
  }
}c;
set<Point>sp;
vector<Circle>vc;
set<Point>::iterator it;
double Dis(Circle a,Circle b){
  return (a.o.x-b.o.x)*(a.o.x-b.o.x)+(a.o.y-b.o.y)*(a.o.y-b.o.y);
}
int Judge(Circle a,Circle b){
  if (fabs(a.o.x-b.o.x)<EPS&&fabs(a.o.y-b.o.y)<EPS)return 0;
  if (fabs((a.r+b.r)*(a.r+b.r)-Dis(a,b))<EPS||fabs((a.r-b.r)*(a.r-b.r)-Dis(a,b))<EPS)return 1;
  if ((Dis(a,b)+EPS<(a.r+b.r)*(a.r+b.r))&&Dis(a,b)>EPS+(a.r-b.r)*(a.r-b.r))return 2;
  return 0;
}
bool OnCircle(Point p,Circle a){
  return fabs((p.x-a.o.x)*(p.x-a.o.x)+(p.y-a.o.y)*(p.y-a.o.y)-a.r*a.r)<EPS;
}
//求两圆交点.
int SegmentPoint(Circle a,Circle b){
  int flag=Judge(a,b);
  double A,B,C,p,q,r,cosa,cosb,sina,sinb,x1,x2,y1,y2;
  A=2*a.r*(a.o.x-b.o.x),B=2*a.r*(a.o.y-b.o.y),C=b.r*b.r-a.r*a.r-(a.o.x-b.o.x)*(a.o.x-b.o.x)-(a.o.y-b.o.y)*(a.o.y-b.o.y);
  p=A*A+B*B,q=-2*A*C,r=C*C-B*B;
  if (flag==1){
    cosa=-q/p/2.0;
    sina=sqrt(1-cosa*cosa);
    x1=a.o.x+a.r*cosa,y1=a.o.y+a.r*sina;
    if (!OnCircle(Point(x1,y1),b)){
      y1=a.o.y-a.r*sina;
    }
    sp.insert(Point(x1,y1));
    return 1;
  }
  double delta=sqrt(q*q-4.0*p*r);
  if (flag==2){
    cosa=(-q+delta)/p/2.0;
    cosb=(-q-delta)/p/2.0;
    sina=sqrt(1-cosa*cosa);
    sinb=sqrt(1-cosb*cosb);
    x1=a.o.x+a.r*cosa,y1=a.o.y+a.r*sina;
    x2=a.o.x+a.r*cosb,y2=a.o.y+a.r*sinb;
    if (!OnCircle(Point(x1,y1),b)) y1=a.o.y-a.r*sina;
    if (!OnCircle(Point(x2,y2),b)) y2=a.o.y-a.r*sinb;
    if (Point(x1,y1)==Point(x2,y2)) y1=a.o.y-a.r*sina;
    sp.insert(Point(x1,y1));
    sp.insert(Point(x2,y2));
    return 2;
  }
}
int find(int x){
  return boss[x]==x?x:boss[x]=find(boss[x]);
}
void Union(int x,int y){
  int fx=find(x),fy=find(y);
  if (fx!=fy)boss[fx]=fy;
  return ;
}
int main(){
  int n,X=0,E=0,V=0,sum=0,num=0;
  scanf("%d",&n);
  sp.clear();
  vc.clear();
  for (int i=0; i<n; ++i){
    c.o.input();
    scanf("%lf",&c.r);
    vc.push_back(c);
  }
  sort(vc.begin(),vc.end());
  vc.erase(unique(vc.begin(),vc.end()),vc.end());
  for (int i=0; i<vc.size(); ++i){
  boss[i]=i;
  }
  n=vc.size();
  Point x1,x2;
  for (int i=0; i<n; ++i){
    for (int j=i+1; j<n; ++j){
      if (Judge(vc[i],vc[j])>0){
        SegmentPoint(vc[i],vc[j]);
      }
    }
  }
  V=sp.size();
  for (int i=0; i<n; ++i){
    for (int j=0; j<n; ++j){
      if (Judge(vc[i],vc[j])>0){
        Union(j,i);
      }
    }
  }
  memset(v,0,sizeof v);
  for (int i=0; i<n; ++i){
    //先找清楚父节点,
    if (!v[find(boss[i])]){
      v[find(boss[i])]=1;
      X++; 
    }
  }
    sum=0;
   for (it=sp.begin(); it!=sp.end(); it++){
     Point p=*it;
      for (int i=0; i<n; ++i){
       if (fabs((vc[i].o.x-p.x)*(vc[i].o.x-p.x)+(vc[i].o.y-p.y)*(vc[i].o.y-p.y)-vc[i].r*vc[i].r)<EPS){
         E++;
       }
     }
   }
  //printf("点%d 联通%d 边%d\n",V,X,E);
  printf("%d\n",E-V+X+1);
}


