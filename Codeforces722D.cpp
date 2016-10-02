/*************************************************************************
     File Name: Codeforces722D.cpp
     ID: PhyCode
     PROG: 
     LANG: C++ 
     Mail: 763315163@qq.com 
     Created Time: 2016年10月03日 星期一 07时56分02秒
 ************************************************************************/
#include<bits/stdc++.h>
using namespace std;
int main(){
  int n;
  int y;
  priority_queue<int,vector<int>,less<int> >pq;
  set<int>S;
  set<int>::iterator it;
  scanf("%d",&n);
  for (int i=0; i<n; ++i){
    scanf("%d",&y);
    pq.push(y);
    S.insert(y);
  }
  while (1){
    int b=pq.top()/2;
    //printf("b==%lld \n",b);
    int B=pq.top();
    while (S.find(b)!=S.end()&&b!=0){
      //printf("%lld\n",b/2);
      b/=2;
    }
    if (!b)break;
    S.insert(b);
    pq.push(b);
    pq.pop();
    S.erase(B);
  }
  for (it=S.begin(); it!=S.end(); ++it){
    printf("%d ",*it);
  }
}

