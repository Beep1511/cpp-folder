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
        T fact = 1;
        for (; !isdigit(c); c = gc())
            if (c == '-')
                fact = -1;
        for (; isdigit(c); c = gc())
            x = (x << 3) + (x << 1) + (c ^ 48);
        x *= fact;
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
const int mod = 1e9 + 7;
const int N = 4000010;
int n, x;
int fact[N], infact[N], a[N], ans[N], b[N];
int qmi(int a, int b){
    int res = 1;
    while (b){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int C(int n, int m){
    if(n < m) return 0;
    return fact[n] * infact[m] % mod * infact[n - m] % mod;
}
signed main(){
    int t;
    cin >> n >> t;
    fact[0] = 1;
    infact[0] = 1;
    for (int i = 1; i <= 3 * n + 5; i ++ ) fact[i] = fact[i - 1] * i % mod;
    infact[3 * n + 5] = qmi(fact[3 * n + 5], mod - 2);
    for (int i = 3 * n + 4; i >= 1; i -- ) infact[i] = infact[i + 1] * (i + 1) % mod;
    a[0] = -1, a[1] = -3, a[2] = -3, a[3] = -1;
    for (int i = 0; i <= 3 * n + 3; i ++ ) a[i] += C(3 * n + 3, i);
    for (int i = 3 * n + 3; i >= 3; i -- ){
        ans[i - 3] = a[i];
        a[i - 1] = ((a[i - 1] - 3 * a[i] + mod) % mod + mod) % mod;
        a[i - 2] = ((a[i - 2] - 3 * a[i] + mod) % mod + mod) % mod;
    }
    while (t -- ){
        cin >> x;
        cout << ans[x] << '\n';
    }
    return 0;
}
