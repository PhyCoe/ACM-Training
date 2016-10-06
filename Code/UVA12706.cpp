/*************************************************************************
     File Name: UVA12706.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年10月05日 星期三 20时25分36秒
 ************************************************************************/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAX=2e4+5;
int s[MAX],p[MAX];
int main(){
  int t,n,m;
  scanf("%d",&t);
  while (t--){
    map<int,int>m1,m2,v;
    scanf("%d%d",&n,&m);
    memset(s,0,sizeof s);
    memset(p,0,sizeof p);
    for (int i=0; i<n; ++i)scanf("%d",s+i);
    for (int i=0; i<m; ++i){
      scanf("%d",p+i);
      m1[p[i]]++;
      if (!v[p[i]])v[p[i]]++;
    }
    int diff_m1=m1.size(),diff_m2=0;
    LL ans=0;
    for (int i=0; i<m; ++i){
      if (v[s[i]]){
        m1[s[i]]--;
        if (!m1[s[i]])diff_m1--;
      }
      else{
        m2[s[i]]++;
        if (m2[s[i]]==1)diff_m2++;
      }
    }
    if (!diff_m1&&!diff_m2)ans++;
    for (int i=1; i<n-m+1; ++i){
      if (v[s[i-1]]){
        m1[s[i-1]]++;
        m1[s[i-1]]==1?diff_m1++:0;
      }
      else{
        m2[s[i-1]]--,m2[s[i-1]]==0?diff_m2--:0;
      }
      if (v[s[i+m-1]]){
        m1[s[i+m-1]]--;
        m1[s[i+m-1]]==0?diff_m1--:0;
      }
      else{
        m2[s[i+m-1]]++,m2[s[i+m-1]]==1?diff_m2++:0;
      }
      if (!diff_m1&&!diff_m2){
        ans+=1ll*(i+1)*(i+1);
      }
    }
    printf("%lld\n",ans);
  }
}
