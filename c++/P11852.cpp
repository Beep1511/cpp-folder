#include <algorithm>
#include <iostream>
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
const int N = 2, M = 3;
#else
const int N = 1010, M = 500010;
#endif

int n, m, q;
struct edge{
    int u, v, w;
    int mark;
}e[M];
bool cmp(edge x, edge y){
    return x.w < y.w;
}
vector<int> dots[N];
vector<pair<int, int>> qu[N];
int bel[N], root[N], ans[M + 5];
struct dsu{
    int fa[N];
    void init(){
        for (int i = 1; i <= n; i ++ ) fa[i] = i;
    }
    int find(int x){
        if(fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }
} D1, D2;
vector<int> T[N];
int fa[N], dep[N];
void dfs(int u) {
    dep[u] = dep[fa[u]] + 1;
    for (int v : T[u]) {
        if (v == fa[u]) continue;
        fa[v] = u;
        dfs(v);
    }
}
int merge(int v, int u, int w) {
    if (dots[u].size() < dots[v].size()) swap(u, v);
    for (auto it : qu[v]) {
        if (bel[it.first] == u) ans[it.second] = w;
        else qu[u].push_back(it);
    }
    D2.fa[v] = u;
    root[u] = (dep[root[v]] < dep[root[u]] ? root[v] : root[u]);
    for (int it : dots[v])
        bel[it] = u, dots[u].push_back(it); 
    dots[v].clear(), qu[v].clear();
    return u;
}

signed main(){
    cin >> n >> m;
    for (int i = 1; i <= m; i ++ ) cin >> e[i].u >> e[i].v >> e[i].w;
    sort(e + 1, e + m + 1, cmp);
    cin >> q;
    for (int i = 1, u, v; i <= q; i ++ ){
        cin >> u >> v;
        qu[u].push_back({v, i});
        qu[v].push_back({u, i});
        ans[i] = -1;
    }
    D1.init(), D2.init();
    for (int i = 1, ru, rv; i <= m; i ++ ) {
        ru = D1.find(e[i].u), rv = D1.find(e[i].v);
        if(ru == rv) continue;
        D1.fa[ru] = rv;
        T[e[i].u].push_back(e[i].v);
        T[e[i].v].push_back(e[i].u);
        e[i].mark = 1;
    }
    dfs(1);
    for (int i = 1; i <= n; i ++ )
        bel[i] = root[i] = i, dots[i].push_back(i);
    for (int i = 1, u, v; i <= m; i ++ ) {
        if (e[i].mark) continue;
        u = D2.find(e[i].u);
        v = D2.find(e[i].v);
        if(u == v) continue;
        while (u != v) {
            if (dep[root[u]] < dep[root[v]]) swap(u, v);
            u = merge(u, D2.find(fa[root[u]]), e[i].w); 
            v = D2.find(v);
        }
    }
    for (int i = 1; i <= q; i ++ ) cout << ans[i] << '\n';
    return 0;
}

