/*************************************************************************
     File Name: ACdream1215.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年08月31日 星期三 22时03分32秒
 ************************************************************************/
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAX=305;
const double EPS=1e-10;
int cnt,n,v[MAX],vis[MAX];
double dis[MAX];
struct Point{
  double x,y,r;
}c[MAX];
struct Node{
  int to;
  double ang;
  Node *next;
}edge[MAX*MAX],*head[MAX];
void AddEdge(int from,int to,double ang){
  Node *p=&edge[++cnt];
  p->to=to,p->ang=ang,p->next=head[from],head[from]=p;
}
double Cross(Point a,Point b){
  return a.x*b.y-a.y*b.x;
}
double Dot(Point a,Point b){
  return a.x*b.x+a.y*b.y;
}
double Dis(int x,int y){
  return sqrt((c[x].x-c[y].x)*(c[x].x-c[y].x)+(c[x].y-c[y].y)*(c[x].y-c[y].y));
}
bool spfa(){
  queue<int >Q;
  memset(v,0,sizeof v);
  memset(vis,0,sizeof vis);
  memset(dis,0,sizeof dis);
  for (int i=0; i<n; ++i){
    v[i]=1;
    Q.push(i);
  }
  while (!Q.empty()){
    int now=Q.front();
    Q.pop();
    v[now]=0;
    for (Node *p=head[now]; p; p=p->next){
      if (dis[p->to]>dis[now]+EPS+p->ang){
        dis[p->to]=dis[now]+p->ang;
        if (!v[p->to]){
          v[p->to]=1;
          Q.push(p->to);
          vis[p->to]++;
          if (vis[p->to]>=n)return 0;
        }
      }
    }
  }
  return 1;
}
int main(){
  while(~scanf("%d",&n)){
    memset(c,0,sizeof c);
    memset(edge,0,sizeof edge);
    memset(head,0,sizeof head);
    for (int i=0; i<n; ++i){
      scanf("%lf%lf%lf",&c[i].x,&c[i].y,&c[i].r);
    }
    scanf("%lf%lf%lf",&c[n].x,&c[n].y,&c[n].r);
    //预处理平移该几个圆,将需要逃脱的圆处于原点,便于计算.
    for (int i=0; i<n; ++i){
      c[i].x-=c[n].x,c[i].y-=c[n].y,c[i].r+=c[n].r;
    }
    c[n].x=c[n].y=0,cnt=0;
    for (int i=0; i<n; ++i){
      for (int j=i+1; j<n; ++j){
        if (c[i].r+c[j].r-EPS<Dis(i,j))continue; //相切或者相离的不考虑.
        bool flag=(Cross(c[i],c[j])>=0);
        double ang=acos(Dot(c[i],c[j])/Dis(n,i)/Dis(n,j));
        //若逃不出去,即某个圆与周围两个圆必定相交,根据角度作为权值必定存在负环.
        //若逃得出去,那么一定存在两个圆相离或者相切.那么这个双向边的图一定不存在负环.
       // printf("%d %d %lf\n",i,j,ang);
        AddEdge(i,j,flag?ang:-ang);
        AddEdge(j,i,flag?-ang:ang);
      }
    }
    if (spfa())printf("YES\n");
    else printf("NO\n");
    }
}
