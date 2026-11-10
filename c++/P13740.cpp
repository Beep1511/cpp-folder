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
#else
#endif
const int N = 300010;
int n, m, a[N], d[N << 1], dis[N << 1], dans[4];
bool alls = 1, vis[N << 1];
vector<int> g[N << 1];
queue<int> q;
bool topo(){
    for (int i = 1; i <= (n << 1); i ++ ) !d[i] && (q.push(i), vis[i] = true);
    while (q.size()){
        int u = q.front();
        q.pop();
        for (int v : g[u])
            if(vis[v]) return false;
            else if(!( -- d[v])){
                q.push(v);
                dis[v] = max(dis[v], dis[u] + 1);
                vis[v] = true;
            }
    }
    for (int i = 1; i <= (n << 1); i ++ )
        if(!vis[i]) return false;
    return true;
}
signed main(){
    read(n, m);
    for (int i = 1; i <= n; i ++ ) read(a[i]), alls &= (a[i] == a[1]);
    if(alls) return putchar('1'), 0;
    for (int i = 1, u, v; i <= m; i ++ ){
        read(u, v);
        g[v + a[u] * n].push_back(u + (a[v] ^ 1) * n);
        g[u + a[v] * n].push_back(v + (a[u] ^ 1) * n);
        d[u + (a[v] ^ 1) * n] ++ ;
        d[v + (a[u] ^ 1) * n] ++ ;
    }
    if(topo()){
        for (int i = 1; i <= n; i ++ ){
            dans[a[i] << 1] = max(dans[a[i] << 1], dis[i]);
            dans[(a[i] << 1) | 1] = max(dans[(a[i] << 1) | 1], dis[i + n]);
        }
        cout << min(min(dans[0], dans[1]), min(dans[2], dans[3])) + 2 << '\n';
    }else puts("infinity");
    return 0;
}

