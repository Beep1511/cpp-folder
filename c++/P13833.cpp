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
typedef pair<int, int> pii;
const int N = 17010, mod = 998244353;
int n, mx, l[N], c[N], f[N], g[N];
signed main(){
    read(n);
    for (int i = 1; i <= n; i ++ ){
        read(l[i]);
        mx = max(mx, l[i]);
    }
    for (int i = 0; i <= mx; i ++ )
        for (int j = 1; j <= n; j ++ )
            c[i] += (l[j] >= i);
    int up = mx * 2 / (n - 1), ans = 0;
    for (int k = 0; k < up; k ++ ){
        for (int i = 0; i <= mx; i ++ ) f[i] = c[i];
        for (int i = 2; i <= n; i ++ ){
            for (int j = mx; j >= 0; j -- )
                f[j] = (f[j] + f[j + 1]) % mod;
            for (int h = __lg(mx); h >= 0; h -- )
                if(!(k >> h & 1)){
                    int t = k >> h | 1;
                    for (int j = 0; j <= (mx >> h); j ++ ){
                        int l = j << h, r = (t ^ j) << h;
                        if(l <= r){
                            int val = (f[r] - f[r + (1 << h)] + mod) % mod;
                            g[l] = (g[l] + val) % mod;
                            g[l + (1 << h)] = (g[l + (1 << h)] - val + mod) % mod;
                        }
                    }
                }
            for (int j = 1; j <= mx; j ++ ) g[j] = (g[j] + g[j - 1]) % mod;
            for (int j = 0; j <= mx; j ++ ) f[j] = (ll)g[j] * (c[j] - i + 1) % mod, g[j] = 0;
        }
        for (int i = 0; i <= mx; i ++ ) ans = (ans + f[i]) % mod;
    }
    cout << ans << '\n';
    return 0;
}

