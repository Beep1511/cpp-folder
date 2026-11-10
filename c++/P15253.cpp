#include <bitset>
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
const int N = 2;
#else
const int N = 2000010;
#endif

#define int long long
int n, m;
int val[N];
int stk[N], top, timestamp;
int dfn[N], low[N], dcccnt, col[N];
bitset<N> instk;
vector<pair<int, int>> e[N];
vector<int> g[N];
vector<int> a[N];
struct node {
    int ls, rs;
    int val;
    #define ls(u) (t[u].ls)
    #define rs(u) (t[u].rs)
    #define val(u) (t[u].val)
} t[N << 5];
int idx;
inline void modify(int &u, int from, int l, int r, int x) {
    u = ++ idx, t[u] = t[from];
    val(u) += x;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        modify(ls(u), ls(from), l, mid, x);
    else
        modify(rs(u), rs(from), mid + 1, r, x);
    return;
}
inline int query(int u, int p, int l, int r) {
    if (!u)
        return 0;
    if (r <= p)
        return val(u);
    int mid = (l + r) >> 1;
    if (p > mid)
        return val(ls(u)) + query(rs(u), p, mid + 1, r);
    else
        return query(ls(u), p, l, mid);
}

inline void tarjan(int u, int from) {
    stk[ ++ top] = u, instk[u] = 1;
    dfn[u] = low[u] = ++ timestamp;
    for (auto [v, idx] : e[u]) {
        if ((from ^ 1) == idx)
            continue;
        if (!dfn[v]) {
            tarjan(v, idx);
            low[u] = min(low[u], low[v]);
        } else
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] != low[u])
        return;
    int v;
    dcccnt ++ ;
    do {
        v = stk[top -- ];
        instk[v] = 0;
        col[v] = dcccnt;
    } while (u != v);
    return;
}
int fa[N], dep[N], root[N], siz[N], son[N], rt[N];
inline void dfs(int u, int fth) {
    fa[u] = fth, dep[u] = dep[fth] + 1, siz[u] = 1;
    rt[u] = rt[fth];
    for (auto x : a[u])
        modify(rt[u], rt[u], 1, 1e6, x);
    for (auto v : g[u]) {
        if (v == fth)
            continue;
        dfs(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
    return;
}
inline void df5(int u, int top) {
    root[u] = top;
    if (!son[u])
        return;
    df5(son[u], top);
    for (auto v : g[u]) {
        if (v == fa[u] or v == son[u])
            continue;
        df5(v, v);
    }
    return;
}
inline int getlca(int u, int v) {
    while (root[u] != root[v]) {
        if (dep[root[u]] < dep[root[v]])
            swap(u, v);
        u = fa[root[u]];
    }
    return (dep[u] < dep[v] ? u : v);
}
signed main() {
    int sid;
    read(n, m, sid);
    for (int i = 1; i <= n; i ++ ) read(val[i]);
    for (int i = 1; i <= m; i ++ ) {
        int u, v;
        read(u, v);
        e[u].emplace_back(v, i << 1), e[v].emplace_back(u, i << 1 | 1);
    }
    tarjan(1, 2000000);
    for (int i = 1; i <= n; i ++ ) a[col[i]].emplace_back(val[i]);
    for (int u = 1; u <= n; u ++ )
        for (auto [v, idx] : e[u]) {
            if (col[u] == col[v])
                continue;
            g[col[u]].emplace_back(col[v]);
        }
    dfs(col[1], 0), df5(col[1], col[1]);
    int q;
    read(q);
    while (q -- ) {
        int x, y;
        read(x, y);
        x = col[x], y = col[y];
        int LCA = getlca(x, y);
        int fat = fa[LCA];
        int i = 0, j = 0;
        while (i != (j = query(rt[x], i + 1, 1, 1e6) + query(rt[y], i + 1, 1, 1e6) - query(rt[LCA], i + 1, 1, 1e6) - query(rt[fat], i + 1, 1, 1e6)))
            i = j;
        cout << i + 1 << '\n';
    }
    return 0;
}







