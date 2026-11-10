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

#define int long long
const int inf = 1e11;
const int N = 200010;
int S0, S1;
int a[N], b[N], c[N], d[N];
int n, k, x, y;
int vor[(1 << 16) + 5], vand[(1 << 16) + 5];
int dp[(1 << 16) + 5];
void solve(){
    read(n, k, x, y);
    for (int i = 1; i <= n; i ++ ) read(a[i]);
    for (int i = 1; i <= n; i ++ ) read(b[i]);
    for (int i = 1; i <= n; i ++ ) read(c[i]);
    for (int i = 1; i <= n; i ++ ) read(d[i]);
    for (int i = 0; i < 1 << k; i ++ ) dp[i] = vor[i] = vand[i] = inf;
    for (int i = 1; i <= n; i ++ ){
        vand[a[i]] = min(vand[a[i]], c[i]);
        vor[b[i]] = min(vor[b[i]], d[i]);
    }
    S1 = y, S0 = (1 << k) - 1 - y;
    for (int i = 0; i < k; i ++ ){
        for (int j = 0; j < 1 << k; j ++ ){
            if(y >> i & 1){
                if(j >> i & 1){
                    vor[j ^ (1 << i)] = min(vor[j ^ (1 << i)], vor[j]);
                    vand[j ^ (1 << i)] = min(vand[j ^ (1 << i)], vand[j]);
                }
            }else{
                if(j >> i & 1){
                    vor[j] = min(vor[j ^ (1 << i)], vor[j]);
                    vand[j] = min(vand[j ^ (1 << i)], vand[j]);
                }
            }
        }
    }
    int S = (1 << k) - 1 - (x ^ y);
    dp[S] = 0;
    for (int i = 0; i < 1 << k; i ++ )
        if((i & S) == i) dp[i] = 0;
    for (int i = 0; i < 1 << k; i ++ ){
        if(dp[i] == inf) continue;
        int s0 = S0 & i, s1 = S1 & i;
        int T1 = S1 - s1, T0 = S0 - s0;
        for (int j = T1; j; j = (j - 1) & T1){
            dp[i | j] = min(dp[i | j], dp[i] + vor[j | (S0 - s0)]);
        }
        for (int j = T0; j; j = (j - 1) & T0){
            dp[i | j] = min(dp[i | j], dp[i] + vand[(S0 - j) | s1]);
        }
    }
    int res;
    if(dp[(1 << k) - 1] == inf) res = -1;
    else res = dp[(1 << k) - 1];
    cout << res << '\n';
}
signed main(){
    int T;
    read(T);
    while (T -- ) solve();
    return 0;
}

