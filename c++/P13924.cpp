#include <algorithm>
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

const int N = 100010;
struct Node{
    int h, l;
}b[N][11];
int n, k, pos[N], s[N], sc[N][2];
long long g[N][2], f[N][2], cnt[N];
bool cmp(Node x, Node y){
    return x.h < y.h;
}
int solve(long long num){
    memset(f, 0xcf, sizeof f);
    memset(sc, 0x3f, sizeof sc);
    f[0][0] = sc[0][0] = 0;
    for (int i = 1; i <= n; i ++ ){
        f[i][0] = max(f[i - 1][1] + g[i - 1][1], f[i - 1][0]);
        if (f[i][0] == f[i - 1][1] + g[i - 1][1])
            sc[i][0] = min(sc[i][0], sc[i - 1][1]);
        if (f[i][0] == f[i - 1][0])
            sc[i][0] = min(sc[i][0], sc[i - 1][0]);
        f[i][1] = max(f[i - 1][1], f[i - 1][0] + g[i][0]) + cnt[i] - num;
        if(f[i][1] == f[i - 1][1] + cnt[i] - num) sc[i][1] = min(sc[i][1], sc[i - 1][1] + 1);
        if(f[i][1] == f[i - 1][0] + g[i][0] + cnt[i] - num)
            sc[i][1] = min(sc[i][1], sc[i - 1][0] + 1);
    }
    if(f[n][0] > f[n][1]) return sc[n][0];
    if(f[n][0] < f[n][1]) return sc[n][1];
    return min(sc[n][0], sc[n][1]);
}
signed main(){
    read(n, k);
    for (int i = 1; i <= n; i ++ ) read(pos[i]);
    for (int i = 1; i <= n; i ++ ) read(s[i]);
    for (int i = 1; i <= n; i ++ ){
        for (int j = 1; j <= s[i]; j ++ ) read(b[i][j].h);
        for (int j = 1; j <= s[i]; j ++ ){
            read(b[i][j].l);
            cnt[i] += abs(b[i][j].l);
        }
        sort(b[i] + 1, b[i] + s[i] + 1, cmp);
    }
    for (int i = 1; i < n; i ++ ){
        int mx = 0;
        for (int j = 1, k = 1; j <= s[i]; j ++ ){
            while (k <= s[i + 1] && b[i + 1][k].h < b[i][j].h){
                mx = max(mx, -b[i + 1][k].l);
                k ++ ;
            }
            if(b[i][j].l > 0)
                g[i + 1][0] += max(0, mx + b[i][j].l - (pos[i + 1] - pos[i] - 1));
        }
        mx = 0;
        for (int j = 1, k = 1; j <= s[i + 1]; j ++ ){
            while (k <= s[i] && b[i][k].h < b[i + 1][j].h){
                mx = max(mx, b[i][k].l);
                k ++ ;
            }
            if (b[i + 1][j].l < 0)
                g[i][1] += max(0, mx - b[i + 1][j].l - (pos[i + 1] - pos[i] - 1));
        }
    }
    long long l = 0, r = 1e10;
    while (l < r){
        int mid = (l + r) >> 1;
        if(solve(mid) <= k) r = mid;
        else l = mid + 1;
    }
    solve(l);
    cout << max(f[n][0], f[n][1]) + k * l << '\n';
    return 0;
}

