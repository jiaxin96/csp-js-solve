/*
n个点m条边的有向图

失活某条边；
失活以某个点为终点的所有边；
激活某条边；
激活以某个点为终点的所有边

如果只考虑激活的边，是否满足：
所有的点出度均为 1；
所有的点都满足，从这个点出发，可以走到一个环中。(已经被上面的条件覆盖)

最终目标：判断所有的点的激活边出度均为 1

原图的bak[v]，当前的cur[v]
1:失活某条边: cur[v]--
2:失活以某个点为终点的所有边: cur[v]=0
3:激活某条边: cur[v]++
4:激活以某个点为终点的所有边: cur[v]=bak[v]

1：暴力qn，维护cur数组并统计（40分）


2：保证cur的和为n，但是不一定正确。
3：给每个点赋值随机值，保证cur的和为所有值的原始bak总和

1:失活某条边u->v: cur[v]-= w[u]
2:失活以某个点为终点的所有边: cur[v]=0
3:激活某条边u->v: cur[v] += w[v]
4:激活以某个点为终点的所有边: cur[v]=bak[v]

保证
k1*w1+k2*w2+k3*w3.....kn*wn = w1+w2+w3...+wn

此时k1=k2=k3====kn=1的概率最大

*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)5e5 + 5;

long long w[maxn], bak[maxn], cur[maxn];

int main() {
  long long n, m;
  cin >> n >> m;
  srand(time(nullptr));
  long long allsum = 0;
  for (int i = 1; i <= n; ++i) {
    w[i] = rand();
    allsum += w[i];
  }
  long long now = 0;
  long long u, v;
  while (m--) {
    cin >> u >> v;
    bak[v] += w[u];
    cur[v] = bak[v];
    now += w[u];
  }

  long long q;
  cin >> q;

  int t;
  while (q--) {
    cin >> t;
    if (t == 1) {
      cin >> u >> v;
      cur[v] -= w[u];
      now -= w[u];
    } else if (t == 2) {
      cin >> v;
      now -= cur[v];
      cur[v] = 0;
    } else if (t == 3) {
      cin >> u >> v;
      cur[v] += w[u];
      now += w[u];
    } else if (t == 4) {
      cin >> v;
      now += bak[v] - cur[v];
      cur[v] = bak[v];
    }
    puts(now == allsum ? "YES" : "NO");
  }

  return 0;
}