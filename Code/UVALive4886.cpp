#include<bits/stdc++.h>
using namespace std;
const int MAX = 1e3 + 5;
char str[MAX];
int v[MAX];
int main() {
  int n;
  while (~scanf("%d",&n),n) {
    memset(v,0,sizeof v);
    scanf("%s",str);
    int l = strlen(str),num1 = 0,num2 = 0,f = 1;
    str[l++] = ',';
    for (int i = 0; i < l; ++i) {
      if (str[i] >= '0' && str[i] <= '9') {
        if (f == 1) {
          num1 = num1 * 10 + str[i] - '0';
        }
        if (f == 2) {
          num2 = num2 * 10 + str[i] - '0';
        }
      }
      else if (str[i] == '-') {
        if (num1) f = 2;
      }
      else {
        if(num1 >= 1000)num1 = 1000;
        if(num2 >= 1000)num2 = 1000;
        if (f == 1 || num2 == 0) v[num1] = 1;
        else {
          for (int i = num1; i <= num2; ++i) {
            v[i] = 1;
          }
        }
        num1 = num2 = 0;
        f = 1;
      }
    }
    int ans = 0;
    for (int i = 1; i <= n && i <= 1000; ++i) {
      if(v[i]) ans++;
    }
    printf("%d\n",ans);
  }
}
