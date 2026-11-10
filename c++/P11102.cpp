#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

namespace IO {
    static const int BUFF = 1 << 20;
    static char buf[BUFF], *u = buf;
    inline char gc() {
        static char buf[BUFF], *p1 = buf, *p2 = buf;
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUFF, stdin), p1 == p2) ? -1 : *p1++;
    }
    inline void pc(char c) {
        *u++ = c;
        if (u - buf == BUFF)
            fwrite(buf, 1, BUFF, stdout), u = buf;
    }
    inline void flush() {
        fwrite(buf, 1, u - buf, stdout);
        u = buf;
    }
    template <typename T> inline void read(T &x) {
        x = 0;
        char c = gc();
        T f = 1;
        for (; !isdigit(c); c = gc())
            if (c == '-')
                f = -1;
        for (; isdigit(c); c = gc())
            x = (x << 3) + (x << 1) + (c ^ 48);
        x *= f;
    }
    inline void read(char &c, bool graph = 1) {
        c = gc();
        if (graph)
            while (!isgraph(c))
                c = gc();
    }
    inline void read(char *u) {
        char c = gc();
        for (; !isgraph(c); c = gc())
            ;
        for (; isgraph(c); c = gc())
            *u++ = c;
        *u = '\0';
    }
    inline void read(std::string &s) {
        s.clear();
        char c = gc();
        for (; !isgraph(c); c = gc())
            ;
        for (; isgraph(c); c = gc())
            s += c;
    }
    template <typename T, typename... Args> void read(T &x, Args &...args) {
        read(x);
        read(args...);
    }
    template <typename T> inline void write(const T &y) {
        T x = y;
        if (x < 0) {
            pc('-');
            x = -x;
        }
        static char stk[1 << 8], *top;
        top = stk;
        do
            *top++ = (x % 10) ^ 48;
        while (x /= 10);
        while (top != stk)
            pc(*--top);
    }


    inline void write(const char &c) { pc(c); }
    inline void write(const std::string &s) {
        for (auto i : s)
            pc(i);
    }
    inline void write(const char *u) {
        for (; *u; ++u)
            pc(*u);
    }
    inline void write(char *u) { write(static_cast<const char *>(u)); }
    template <typename T, typename... Args> void write(const T &x, const Args &...args) {
        write(x);
        write(args...);
    }
    struct __Flusher {
        ~__Flusher() { flush(); }
    } __flusher;
}; // namespace IO
// namespace IO
using IO::read;
using IO::write;
using IO::flush;

#ifdef __clang__
const int N = 2;
#else
const int N = 5e5 + 10;
#endif

int n, m, ptot;
vector<int> g[N];
vector<int> dcc[N];
int tot;
bool cut[N];
int dfn[N], stk[N], top, low[N], timestamp, dep[N], bel[N];
void tarjan(int u, int f) {
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u;
    dep[u] = dep[f] + 1;
    if (u == 1 && g[u].size() == 0) {
        cut[u] = true;
        dcc[ ++ tot].push_back(u);
    }
    int c = 0;
    for (int v : g[u]) if (v != f) {
        if (!dfn[v]) {
            tarjan(v, u); low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {		
                tot ++ ;
                c ++ ;
                if (c > 1 || u != 1) cut[u] = true;
                while (stk[top] != v) bel[stk[top]] = tot, dcc[tot].push_back(stk[top -- ]);
                dcc[tot].push_back(stk[top -- ]); bel[v] = tot;
                dcc[tot].push_back(u);
            }
        }else low[u] = min(low[u], dfn[v]);
    }
    return ;
}
vector<int> vec[N * 3];
unordered_map<long long, int> idx;
#define id(x, y) (1ll * x * 0x325609 + y)
int dist[N * 3]; bool vis[N * 3];
void bfs() {
    for (int i = 1; i <= ptot; i ++ ) dist[i] = 1e9, vis[i] = false;
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    vis[1] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : vec[u]) if (!vis[v])
            dist[v] = dist[u] + 1, vis[v] = 1, q.push(v);
    } return ;
}
void solve(){
    cin >> n >> m; 
    ptot = n;
    idx.clear();
    for (int i = 1, u, v; i <= m; i ++ ) {
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    tarjan(1, 0); 
    for (int i = 1; i <= n; i ++ )
        if (!cut[i]) {
            idx[id(i, bel[i])] = ++ ptot;
            for (int v : g[i]) vec[v].push_back(ptot), vec[ptot].push_back(v);
        }
    for (int i = 1; i <= n; i ++ ) if (cut[i]) {
        for (int v : g[i]) {
            int t = 0;
            if (dep[v] > dep[i]) {
                if (idx.find(id(i, bel[v])) == idx.end()) t = idx[id(i, bel[v])] = ++ ptot;
                else t = idx[id(i, bel[v])];
            } else {
                if (idx.find(id(i, bel[i])) == idx.end()) t = idx[id(i, bel[i])] = ++ ptot;
                else t = idx[id(i, bel[i])];
            }
            vec[t].push_back(v), vec[v].push_back(t);
        }
    }
    bfs();
    for (int i = 2; i <= n; i ++ )
        cout << (vis[i] ? dist[i] : -1) << " \n"[i == n];
    for (int i = 1; i <= n; i ++ ) g[i].clear(), dfn[i] = low[i] = 0, cut[i] = false;
    for (int i = 1; i <= tot; i ++ ) dcc[i].clear();
    for (int i = 1; i <= ptot; i ++ ) vec[i].clear(), vis[i] = false;
    top = timestamp = tot = 0;
}
int main() {
    int t;
    cin >> t;
    while (t -- ) solve();
    return 0;
}

