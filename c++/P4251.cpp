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

typedef long long ll;
ll n, m, k;
ll mapp[310][310], maxn = -1, h[310], last[90010], to[90010];
ll tot = 1, l, r;
ll ans;
int match[310], vis[310];
void init(){
    memset(last, 0, sizeof last);
    memset(h, 0, sizeof h);
    memset(to, 0, sizeof to);
}
void add(ll x, ll y){
    to[ ++ tot] = y, last[tot] = h[x], h[x] = tot;
}
bool path(ll u){
    for (int i = h[u]; i; i = last[i]){
        ll v = to[i];
        if (vis[v] == 1)
            continue;
        vis[v] = 1;
        if (match[v] == -1 || path(match[v]) == true) {
            match[v] = u;
            return true;
        }
    }
    return false;
}
void solve(){
    ans = 0;
    memset(match, -1, sizeof match);
    for (int i = 1; i <= n; i ++ ){
        memset(vis, 0, sizeof vis);
        if(path(i)) ans ++ ;
    }
}
signed main(){
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ ){
            cin >> mapp[i][j];
            maxn = max(maxn, mapp[i][j]);
        }
    l = 0, r = maxn;
    while (l <= r){
        init();
        ll mid = (l + r) >> 1;
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= m; j ++ )
                if(mapp[i][j] < mid) add(i, j);
        solve();
        if(ans > n - k) r = mid - 1;
        else l = mid + 1;
    }
    cout << r;
    return 0;
}

