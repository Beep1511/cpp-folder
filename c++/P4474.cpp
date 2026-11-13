#include <cstring>
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

const int N = 100010, M = 2000010, inf = 1e8;
int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
void add(int a, int b, int c){
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++ ;
}
int q[N], d[N], cur[N];
int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0};
int id(int i, int j){
    return (i - 1) * m + j;
}
bool bfs(){
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt){
        int x = q[hh ++ ];
        for (int i = h[x]; ~i; i = ne[i]){
            int y = e[i];
            if(d[y] == -1 && f[i]){
                d[y] = d[x] + 1;
                cur[y] = h[y];
                if(y == T) return 1;
                q[ ++ tt] = y;
            }
        }
    }
    return 0;
}
int find(int u, int lim){
    if(u == T) return lim;
    int flow = 0;
    for (int i = cur[u]; ~i && flow < lim; i = ne[i]){
        int y = e[i];
        cur[u] = i;
        if(d[y] == d[u] + 1 && f[i]){
            int tmp = find(y, min(lim - flow, f[i]));
            if(!tmp) d[y] = -1;
            f[i] -= tmp;
            f[i ^ 1] += tmp;
            flow += tmp;
        }
    }
    return flow;
}
int dinic(){
    int res = 0, flow;
    while (bfs()) while ((flow = find(S, inf))) res += flow;
    return res;
}

signed main(){
    cin >> n >> m;
    S = 0, T = N - 10;
    memset(h, -1, sizeof h);
    int sum = 0;
    for (int i = 1; i <= n; i ++ ){
        for (int j = 1; j <= m; j ++ ){
            int x;
            cin >> x;
            sum += x;
            if ((i + j) & 1) {
                add(S, id(i, j), x);
                for (int k = 0; k < 4; k ++ ) {
                    int xx = i + dx[k], yy = j + dy[k];
                    if (xx >= 1 && xx <= n && yy >= 1 && yy <= m)
                        add(id(i, j), id(xx, yy), inf);
                }
            } else {
                add(id(i, j), T, x);
            }
        }
    }
    cout << sum - dinic();
    return 0;
}


