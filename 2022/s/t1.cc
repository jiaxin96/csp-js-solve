/*
走5段路程回到原点每段终点的值和最大，每段路程长度小于等于K+1

每段路程都BFS一个最优的，最终可能不是最优的。

暴力：O(nm+n^4) 40分

重新定义可达点：路径小于等于k+1,BFS一次O(nm)
1-a-b-c-d-1, 当abc确定的时候，d的值是唯一的，同理a的值也是唯一的 (70分)
重点在于如何找到bc


折半查找：
定义f(u),表示u可达，且在家附近的权值最大的景点。
f(b) -> a
f(c) -> d
ans = min(ans, a+b+c+d)
复杂度O(nm+n^2)

//去重，保证f(b) f(c) a d不同
f(b,1)=c: a=f(b,2)
f(c,1)=b: d=f(c,2)
a==d? a=f(b,3)或者d=f(c,3)

直接组合9种情况，然后去重
f(b,1,2,3)
f(c,1,2,3)
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2505;

vector<long long> G[maxn];

long long w[maxn];
bool ok[maxn][maxn];  // u, v 是否可达
vector<int> f[maxn];  // bfs的时候计算f[u] 可达u且可达1的前三大v

long long n, m, k;

long long dis[maxn];
bool cmp(int a, int b) { return w[a] > w[b]; }
void bfs(int x) {
  memset(dis, -1, sizeof(dis));
  queue<int> q;
  q.push(x);
  dis[x] = 0;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    if (u != x) {
      ok[x][u] = true;
      if (x != 1 && ok[1][u]) {
        f[x].push_back(u);
        sort(f[x].begin(), f[x].end(), cmp);
        if (f[x].size() > 3) f[x].pop_back();
      }
    }

    if (dis[u] >= k + 1) continue;

    for (int i = 0; i < G[u].size(); i++) {
      int v = G[u][i];
      if (dis[v] == -1) {
        dis[v] = dis[u] + 1;
        q.push(v);
      }
    }
  }
}

int main() {
  cin >> n >> m >> k;
  for (int i = 2; i <= n; ++i) cin >> w[i];
  int u, v;
  while (m--) {
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  for (int i = 1; i <= n; ++i) bfs(i);

  long long ans = 0;

  for (int b = 2; b <= n; ++b)
    for (int c = 2; c <= n; ++c)
      if (ok[b][c])
        for (int i = 0; i < f[b].size(); ++i)
          for (int j = 0; j < f[c].size(); ++j) {
            int a = f[b][i];
            int d = f[c][j];
            if (a != c && b != d && a != d) {
              ans = max(ans, w[a] + w[b] + w[c] + w[d]);
            }
          }

  printf("%lld\n", ans);
  return 0;
}