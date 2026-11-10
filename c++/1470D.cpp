#include <iostream>
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
int n, m;
int h[N << 1];
int cnt, vis[N], fa[N], d[N], v[N], f[N];
int root(int x){
    return x == fa[x] ? x : fa[x] = root(fa[x]);
}
struct edge{
    int to, ne;
}e[N << 1];
void add(int x, int y){
    e[ ++ cnt] = {y, h[x]};
    h[x] = cnt, d[x] ++ ;
}
void dfs(int x, int y){
    f[x] = y;
    for (int i = h[x]; i; i = e[i].ne)
        if(!f[e[i].to]) dfs(e[i].to, x);
}
void dfs1(int x, int y){
    bool ia = 1;
    for (int i = h[x]; i; i = e[i].ne)
        if(vis[e[i].to]) ia = 0;
    if(ia) vis[x] = 1;
    for (int i = h[x]; i; i = e[i].ne)
        if(f[e[i].to] == x) dfs1(e[i].to, x);
}
void solve(){
    cin >> n >> m;
    cnt = 0;
for (int i = 1; i <= n; i ++ )
        fa[i] = i, h[i] = vis[i] = d[i] = v[i] = f[i] = 0;
    for (int i = 1, x, y; i <= m; i ++ ){
        cin >> x >> y;
        add(x, y), add(y, x), fa[root(x)] = root(y);
    }
    bool ia = 1;
    for (int i = 1; i <= n; i ++ )
        if (root(i) ^ root(1))
            ia = 0;
    if (!ia) {
        puts("NO");
        return ;
    }
    f[1] = 1, dfs(1, 1), dfs1(1, 1);
    puts("YES");
    int s = 0;
    for (int i = 1; i <= n; i ++ )
        s += vis[i];
    printf("%d\n", s);
    for (int i = 1; i <= n; i ++ )
        if (vis[i])
            printf("%d ", i);
    puts("");
}
signed main(){
    int t;
    cin >> t;
    while (t -- ) solve();
    return 0;
}
