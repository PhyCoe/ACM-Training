#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+5;

struct Node{
  int first_max,second_max;
}tree[MAX<<2];

int a[MAX],f_max,s_max;

void Build(int v,int l,int r){
  if (l==r){
    tree[v].first_max = a[l-1];
    tree[v].second_max = 0;
    return ;
  }
  int mid = (l+r)>>1;
  Build(v<<1,l,mid);
  Build(v<<1|1,mid+1,r);
  tree[v].first_max = max(tree[v<<1].first_max,tree[v<<1|1].first_max);
  int tmp = max({min(tree[v<<1].first_max,tree[v<<1|1].first_max),tree[v<<1].second_max,tree[v<<1|1].second_max});
  tree[v].second_max=tmp;
  
}
  
void Update(int v,int L,int R,int x,int m){
  if (L==x&&R==x){
    tree[v].first_max = m;
    tree[v].second_max = 0;
    return ;
  }
  int mid = (L+R)>>1;
  if (x<=mid)Update(v<<1,L,mid,x,m);
  if (x>mid)Update(v<<1|1,mid+1,R,x,m);
  tree[v].first_max = max(tree[v<<1].first_max,tree[v<<1|1].first_max);
  int tmp = max({min(tree[v<<1].first_max,tree[v<<1|1].first_max),tree[v<<1].second_max,tree[v<<1|1].second_max});
  tree[v].second_max=tmp;
};


void Query(int v,int L,int R,int l,int r){
  if (L>=l&&R<=r){
    //printf("%d %d\n",L,R);
    int tmp = max({min(f_max,tree[v].first_max),s_max,tree[v].second_max});
    f_max = max(f_max,tree[v].first_max);
    s_max = tmp;
    return ;
  }
  int mid = (L+R)>>1;
 // printf("%d %d %d\n",L,R,mid);
  if (l<=mid) Query(v<<1,L,mid,l,r);
  if (r>mid) Query(v<<1|1,mid+1,R,l,r);
}

int main(){
  int n,q,x,m,l,r;
  char s[5];
  scanf("%d",&n);
  for (int i=0; i<n; ++i)scanf("%d",&a[i]);
  scanf("%d",&q);
  Build(1,1,n);
  /*
  for (int i=1; i<10; ++i){
    printf("%d %d\n",tree[i].first_max,tree[i].second_max);
  }
  */
  while (q--){
    scanf("%s%d%d",s,&l,&r);
    if (s[0]=='Q'){
      f_max = s_max = 0;
      //printf("%d %d\n",l,r);
      Query(1,1,n,l,r);
      //printf("%d %d\n",f_max,s_max);
      printf("%d\n",f_max+s_max);
    }
    else{
      Update(1,1,n,l,r);
    }
  }

}
