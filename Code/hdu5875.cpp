#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAX=1e5+5;
int a[MAX],dp_min[MAX][20],n;
void RMQ(){
  for (int j=1; (1<<j)<=n; ++j){
    for (int i=1; i+(1<<j)-1<=n; ++i){
      dp_min[i][j]=min(dp_min[i][j-1],dp_min[i+(1<<(j-1))][j-1]);
    }
  }
  return ;
}
int Query(int l,int r){
  //int k=log(r-l+1.0)/log(2.0);
  int k=0;
  while ((1<<(k+1))<=r-l+1)k++;
  return min(dp_min[l][k],dp_min[r-(1<<k)+1][k]);
}
int Binary_Search(int l,int r){
  int ans=a[l];
  if (!ans)return ans;
  int ll,rr;
  while (l<r){
    ll=l+1,rr=r;
    while (ll<rr){
      int mm=(ll+rr)/2;
      if (Query(ll,mm)<=ans)rr=mm;
      else if (Query(mm+1,rr)<=ans)ll=mm+1;
      else return ans;
    }
    ans%=a[ll];
    l=ll;
  }
  return ans;
}
int main(){
  int t,q,l,r;
  scanf("%d",&t);
  while (t--){
    scanf("%d",&n);
    for (int i=1; i<=n; ++i){
      scanf("%d",&a[i]);
      dp_min[i][0]=a[i];
    }
    RMQ();
    scanf("%d",&q);
    while (q--){
      scanf("%d%d",&l,&r);
      printf("%d\n",Binary_Search(l,r));
    }
  }
}
