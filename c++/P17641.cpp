#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
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
        static char stk[1 << 8], *tp;
        tp = stk;
        do
            *tp++ = (x % 10) ^ 48;
        while (x /= 10);
        while (tp != stk)
            pc(*--tp);
    }


    inline void write(const char &c) { pc(c); }
    inline void write(const std::string &s) {
        for (auto i : s)
            pc(i);
    }
    inline void write(const char *u) {
        for (; *u; ++ u)
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
const int N = 500010;
#endif

#define int long long
int n, m, dis[N];
bool vis[N], cir[N];
int st[N], dep[N], cnt[N], p[N];
array<int, 3> edg[N];
vector<array<int, 3>> g[N], gg[N];
vector<int> ggg[N];
void dfs(int f, int u){
    dep[u] = dep[f] + 1;
    vis[u] = 1;
    for (auto [v, w, id] : g[u]){
        if(v != f){
            if(vis[v]){
                if(dep[v] < dep[u]){
                    cnt[u] ++ , cnt[v] -- ;
                    cir[id] = 1;
                }
            }else{
                st[v] = id;
                dfs(u, v);
            }
        }
    }
}
void calc(int f, int u){
    for (auto [v, w, id] : g[u]){
        if(v != f && st[v] == id){
            calc(u, v);
            cnt[u] += cnt[v];
        }
    }
    if (cnt[u]){
        cir[st[u]] = 1;
    }
}
int find(int x){
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}
void merge(int x, int y){
    int px = find(x), py = find(y);
    if(px != py) p[px] = py;
}
vector<int> nod[N];
typedef pair<int, int> pii;
void dijkstra(int bel){
    priority_queue<pii, vector<pii>, greater<pii>> q;
    for (auto i : nod[bel])
        if(dis[i] < 1e18) q.push({dis[i], i});
    while (q.size()){
        auto [d, u] = q.top();
        q.pop();
        for (auto [v, w, id] : g[u]){
            if (find(v) == bel && dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
}
bool visd[N];
void dfs2(int f, int u){
    dijkstra(u);
    for (auto v : ggg[u])
        if(v != f) visd[v] = 1;
    for (auto [uu, v, w] : gg[u]){
        if (visd[find(v)])
            dis[v] = min(dis[v], dis[uu] + w);
    }
    for (auto v : ggg[u]){
        if (v != f)
            visd[v] = 0;
    }
    for (auto v : ggg[u]){
        if (v != f)
            dfs2(u, v);
    }
}
signed main(){
    cin >> n >> m;
    for (int i = 1; i <= m; i ++ ){
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w, i});
        g[v].push_back({u, w, i});
        edg[i] = {u, v, w};
    }
    dfs(0, 1);
    calc(0, 1);
    int res = 0;
    for (int i = 1; i <= n; i ++ ){
        p[i] = i;
    }
    for (int i = 1; i <= m; i ++ ){
        if (cir[i]){
            res += edg[i][2];
            merge(edg[i][0], edg[i][1]);
        }
        else{
            res += edg[i][2] * 2;
        }
    }
    for (int i = 1; i <= n; i ++ ) nod[find(i)].push_back(i);
    for (int i = 1; i <= n; i ++ ){
        for (auto &[v, w, id] : g[i]){
            if (!cir[id]){
                w = -w;
            }
            
            gg[find(i)].push_back({i, v, w});
            if (find(i) != find(v)){
                ggg[find(i)].push_back(find(v));
            }
        }
    }
    
    for (int i = 1; i <= n; i ++ ) dis[i] = 1e18;
    dis[1] = 0;
    dfs2(0, find(1));
    res += min(0ll, *min_element(dis + 1, dis + n + 1));
    cout << res << '\n';
    return 0;
}

