/*
c_(x,y) = a[x]*b[y]

L : l1 <= x <= r1: 让c大
Q : l2 <= y <= r2：让c小

最终目标:l1到r2每行中的最小值，的最大值
暴力：q*n*m

当a[x]确定:65分
a[x]>=0: min(b[l2:r2])一个ST
a[x]<0: max(b[l2:r2]) 一个ST

Q:每次选择min(a[x]*min(b), a[x]*max(b)),和L的选择无关

确定x:
b[]>0: max(a[l1:r1]) 一个ST
b[]<0: min(a[l1:r1]) 一个ST
其他：选择距离0最近的点，正数的最小值和负数的最大值

L:max(min(a,b))
a的4个和b的2个的组合

6个ST表：
b的2个
a的2个
a的绝对值（正数一个 负数一个）最小

*/

#include <bits/stdc++.h>
using namespace std;
const long long Inf = LONG_LONG_MAX - 5;
const int Maxn = 100039;
int n, m, q;
long long ans;
int L1, R1, L2, R2, k, ks, k2, ks2;
int log2s[Maxn] = {0, 0};
long long A[Maxn], B[Maxn];
long long As[5], Bs[3];
long long a[5][Maxn][18], b[3][Maxn][18];
long long min(long long a, long long b) { return a > b ? b : a; }
long long max(long long a, long long b) { return a > b ? a : b; }

int main() {
  scanf("%d%d%d", &n, &m, &q);

  int i, j;
  for (i = 2; i <= 100000; i++) log2s[i] = log2s[i / 2] + 1;
  for (i = 1; i <= n; i++) {
    scanf("%lld", &A[i]);
    // a的最大最小，正数的最小，负数的最大
    a[1][i][0] = a[2][i][0] = A[i];
    a[3][i][0] = (A[i] >= 0 ? A[i] : Inf);
    a[4][i][0] = (A[i] < 0 ? A[i] : -Inf);
  }

  for (i = 1; i <= m; i++) {
    scanf("%lld", &B[i]);
    b[1][i][0] = b[2][i][0] = B[i];  // b的2个
  }

  for (j = 1; j <= log2s[m]; j++) {
    for (i = 1; i + (1 << j) - 1 <= m; i++) {
      b[1][i][j] = max(b[1][i][j - 1], b[1][i + (1 << (j - 1))][j - 1]);
      b[2][i][j] = min(b[2][i][j - 1], b[2][i + (1 << (j - 1))][j - 1]);
    }
  }
  for (j = 1; j <= log2s[n]; j++) {
    for (i = 1; i + (1 << j) - 1 <= n; i++) {
      a[1][i][j] = max(a[1][i][j - 1], a[1][i + (1 << (j - 1))][j - 1]);
      a[2][i][j] = min(a[2][i][j - 1], a[2][i + (1 << (j - 1))][j - 1]);
      a[3][i][j] = min(a[3][i][j - 1], a[3][i + (1 << (j - 1))][j - 1]);
      a[4][i][j] = max(a[4][i][j - 1], a[4][i + (1 << (j - 1))][j - 1]);
    }
  }
  while (q--) {
    scanf("%d%d%d%d", &L1, &R1, &L2, &R2);
    k = log2s[R1 - L1 + 1], k2 = log2s[R2 - L2 + 1];
    ks = (1 << k), ks2 = (1 << k2);
    // a最大最小
    As[1] = max(a[1][L1][k], a[1][R1 - ks + 1][k]);
    As[2] = min(a[2][L1][k], a[2][R1 - ks + 1][k]);
    // a的绝对值的最小
    As[3] = min(a[3][L1][k], a[3][R1 - ks + 1][k]);  // 正数的绝对值
    As[4] = max(a[4][L1][k], a[4][R1 - ks + 1][k]);  // 负数的绝对值
    // b最大最小
    Bs[1] = max(b[1][L2][k2], b[1][R2 - ks2 + 1][k2]);
    Bs[2] = min(b[2][L2][k2], b[2][R2 - ks2 + 1][k2]);

    ans = -Inf;
    // Q的选择
    ans = max(min(As[1] * Bs[1], As[1] * Bs[2]),
              min(As[2] * Bs[1], As[2] * Bs[2]));

    if (As[3] != Inf)
      ans = max(ans, As[3] * (As[3] >= 0 ? Bs[2] : Bs[1]));  //正数的最小值
    if (As[4] != -Inf)
      ans = max(ans, As[4] * (As[4] >= 0 ? Bs[2] : Bs[1]));  //负数的最大值

    printf("%lld\n", ans);
  }
  return 0;
}
