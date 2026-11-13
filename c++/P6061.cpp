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
const int E = 2;
#else
const int E = 5000000;
#endif

#define int long long
const int inf = 1e18, N = 600;
struct edge{
    int v, w, c, nxt;
}e[E];
int h[N << 1], pre[N << 1], cur[N << 1], dis[N << 1], flow[N << 1], cost, cnt = 1, s, t;

signed main(){
    return 0;
}



#define int long long

using namespace std;

const int E = 5e6, INF = 1e18, N = 600;

struct edge {
    int v, w, c, nxt;
} e[E];

int h[N << 1], pre[N << 1], cur[N << 1], dis[N << 1], flow[N << 1], cost, cnt = 1, s, t;
bool vis[N << 1];

void init(int u, int v, int w, int c) {
    e[++cnt] = {v, w, c, h[u]}, h[u] = cnt;
    e[++cnt] = {u, 0, -c, h[v]}, h[v] = cnt;
}

bool spfa() {
    memset(dis, 0x3f, sizeof dis), memset(flow, 0, sizeof flow), memcpy(cur, h, sizeof h);
    queue<int> q;
    q.push(s), flow[s] = INF, dis[s] = 0;
    while (!q.empty()) {
        int u = q.front(), v;
        q.pop(), vis[u] = 0;
        for (int i = h[u]; i; i = e[i].nxt)
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
