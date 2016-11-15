#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef struct TrieTag{
  TrieTag* next[2];
  int val ;
  TrieTag() {
    val = 0;
    for (int i = 0; i < 2; ++i) next[i] = NULL;
  }
}Trie;
Trie* root;
int k;
void Insert(int x) {
  Trie* p = root;
  for (int i = 30,k; i >= 0; --i) {
    k = (x >> i) & 1;
    if (p->next[k] == NULL)p->next[k] = new TrieTag();
    p = p->next[k];
    ++p->val;
  }
  return ;
}
LL Search(int x) {
  Trie* p = root;
  LL ans = 0;
  for (int i = 30,q,b; i >= 0; --i) {
    q = (x >> i) & 1;
    b = (k >> i) & 1;
    if (!b) {
      if (p->next[q ^ 1]) {
        ans += p->next[q ^ 1]->val;
      }
      if (p->next[q]) p = p->next[q];
      else return ans;
    }
    else {
      if (p->next[q ^ 1]) p = p->next[q ^ 1];
      else return ans;
    }
  }
  return ans + p->val;
}
int main() {
  int n,x,sum = 0;
  LL ans = 0;
  root = new TrieTag();
  scanf("%d%d",&n,&k);
  Insert(0);
  for (int i = 0; i < n; ++i) {
    scanf("%d",&x);
    sum ^= x;
    ans += Search(sum);
    Insert(sum);
  }
  printf("%lld\n",ans);
}
