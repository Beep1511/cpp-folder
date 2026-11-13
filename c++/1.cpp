#include <bits/stdc++.h>

#define F(i, j, k) for (int i = (j), ENDD = (k); i <= ENDD; ++i)
#define R(i, j, k) for (int i = (j), ENDD = (k); i >= ENDD; --i)
#define int long long

using namespace std;

const int E = 5e6, INF = 1e18, N = 600;

struct edge {
    int v, w, c, nxt;
} e[E];

int head[N << 1], pre[N << 1], cur[N << 1], dis[N << 1], flow[N << 1], cost, cnt = 1, s, t;
bool vis[N << 1];

void init(int u, int v, int w, int c) {
    e[++cnt] = {v, w, c, head[u]}, head[u] = cnt;
    e[++cnt] = {u, 0, -c, head[v]}, head[v] = cnt;
}

bool spfa() {
    memset(dis, 0x3f, sizeof dis), memset(flow, 0, sizeof flow), memcpy(cur, head, sizeof head);
    queue<int> q;
    q.push(s), flow[s] = INF, dis[s] = 0;
    while (!q.empty()) {
        int u = q.front(), v;
        q.pop(), vis[u] = 0;
        for (int i = head[u]; i; i = e[i].nxt)
            if (dis[v = e[i].v] > dis[u] + e[i].c && e[i].w) {
                dis[v] = dis[u] + e[i].c, flow[v] = min(e[i].w, flow[u]), pre[v] = i;
                if (!vis[v])
                    vis[v] = 1, q.push(v);
            }
    }
    if (!flow[t])
        return 0;
    cost += flow[t] * dis[t];
    int u = t;
    while (u != s) {
        int id = pre[u];
        e[id].w -= flow[t], e[id ^ 1].w += flow[t];
        u = e[id ^ 1].v;
    }
    return 1;
}

int n, m;

signed main() {
    cin.tie(0)->sync_with_stdio(0), cin.tie(0);
    cin >> n >> m, t = n * 2 + 10;
    F(i, 1, n) {
        int a;
        cin >> a;
        init(i + n, i, INF, 0);
        init(i, i + n, INF, a);
        init(s, i, 1, 0), init(i + n, t, 1, 0);
    }
    F(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        init(u, v + n, INF, w);
    }
    while (spfa())
        ;
    cout << cost;
    return 0;
}
