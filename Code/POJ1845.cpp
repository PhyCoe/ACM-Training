#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
const int MAX = 1e6;
const int MOD = 9901;
int prime[MAX],cnt;
bool v[MAX];
void Prim() {
  cnt = 0;
  memset(v,0,sizeof v);
  for (int i = 2; i < MAX; ++i) {
    if (!v[i]) prime[cnt++] = i;
    for (int j = 0; j < cnt && prime[j]*i<MAX; ++j) {
      prime[i * prime[j]] = 1;
      if (i % prime[j] == 0)break;
    }
  }
}
LL multi_pow(LL a,LL b,LL c){
  LL ans = 0;
  while (b) {
    if (b&1) ans = ans + a % c;
    a <<= 1;
    a %= c;
    b >>= 1;
  }
  return ans;
}
LL quick_pow(LL a,LL b,LL c) {
  LL ans = 1;
  while (b) {
    if(b & 1) ans = multi_pow(ans,a,c);
    a = multi_pow(a,a,c);
    b >>= 1;
  }
  return ans;
}
LL Solve(LL a,LL b){
  LL A = a,ans = 1,M,B,num;
  for (int i = 0; prime[i] * prime[i] <= A; ++i) {
    if(a % prime[i] == 0) {
      num = 0;
      while (a % prime[i] == 0) {
        num++;
        a /= prime[i];
      }
      M = (prime[i] - 1) * MOD;
      B = num * b + 1;
      ans = ans * ((quick_pow(prime[i],B,M) - 1 + M) / (prime[i] - 1)) % MOD;
    }
  }
  if (a > 1) {
    M = (a - 1) * MOD;
    B = b + 1;
    ans = ans * ((quick_pow(a,B,M) - 1 + M) / (a - 1)) % MOD;
  }
  return ans ;
}
int main() {
  LL a,b;
  scanf("%lld%lld",&a,&b);
  Prim();
  printf("%lld\n",Solve(a,b));
}
