/*************************************************************************
     File Name: 723D.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年10月03日 星期一 22时44分48秒
 ************************************************************************/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int MAX=55;
struct node{
  int x,y;
  node(int xx,int yy):x(xx),y(yy) {};
};
struct lake{
  int num_node,v_num;
}nn[MAX*MAX];
char str[MAX][MAX];
int dir[4][2]={1,0,-1,0,0,1,0,-1},vis[MAX][MAX],n,m,cnt;
bool cmp(lake a,lake b){
  return a.num_node<b.num_node;
}
int bfs(node a){
  queue<node>Q;
  Q.push(a);
  vis[a.x][a.y]=cnt;
  int sum=1,flag=0;
  while (!Q.empty()){
    node now=Q.front();
    Q.pop();
    for (int i=0; i<4; ++i){
      int xx,yy;
      xx=now.x+dir[i][0];
      yy=now.y+dir[i][1];
      if (xx<0||xx>=n||yy<0||yy>=m||vis[xx][yy]||str[xx][yy]=='*')continue;
      vis[xx][yy]=cnt;
      Q.push(node(xx,yy));
      sum++;
    }
  }
  return sum;
}
void bfs2(node a){
  queue<node>Q;
  Q.push(a);
  vis[a.x][a.y]=-1;
  str[a.x][a.y]='*';
  while (!Q.empty()){
    node now= Q.front();
    Q.pop();
    int xx,yy;
    for (int i=0; i<4; ++i){
      xx=now.x+dir[i][0];
      yy=now.y+dir[i][1];
      if (xx<0||xx>=n||yy<0||yy>=m||vis[xx][yy]||str[xx][yy]=='*')continue;
      str[xx][yy]='*';
      Q.push(node(xx,yy));
      vis[xx][yy]=-1;
    }
  }
  return ;
}
int main(){
  int k;
  scanf("%d%d%d",&n,&m,&k);
  for (int i=0; i<n; ++i){
    scanf("%s",str[i]);
  }
  memset(vis,0,sizeof vis);
  cnt=0;
  int max_ans=0,ans=0;
  for (int i=0; i<n; ++i){
    if (str[i][0]=='.'){
      bfs2(node(i,0));
    }
    if (str[i][m-1]=='.')bfs2(node(i,m-1));
  }
  for (int i=0; i<m; ++i){
    if (str[0][i]=='.')bfs2(node(0,i));
    if (str[n-1][i]=='.')bfs2(node(n-1,i));
  }
  for (int i=0; i<n; ++i){
    for (int j=0; j<m; ++j){
      if (str[i][j]=='.'&&!vis[i][j]){
        nn[cnt++].num_node=bfs(node(i,j));
        nn[cnt-1].v_num=cnt;
      }
    }
  }
  sort(nn,nn+cnt,cmp);
  if (!k){
    for (int i=0; i<cnt; ++i)ans+=nn[i].num_node;
  }
  else{
  for (int i=0; i<cnt-k; ++i)ans+=nn[i].num_node;
  }
  printf("%d\n",ans);
  for (int i=0; i<n; ++i){
    for (int j=0; j<m; ++j)
      if (vis[i][j]<0)str[i][j]='.';
      else if (vis[i][j]>0){
        if (!k){
          str[i][j]='*';
        }
        for (int q=0; q<cnt-k; ++q){
          if (vis[i][j]==nn[q].v_num){
            str[i][j]='*';
            break;
          }
        }
      }
  }
  for (int i=0; i<n; ++i)printf("%s\n",str[i]);
}
