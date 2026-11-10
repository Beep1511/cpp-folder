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

typedef unsigned ui;
typedef unsigned long long ull;
const int N = 200010;
int n;
ull a[N], f[N];
ull gcd(const ull &a, const ull &b) {
    return b ? gcd(b, a % b) : a;
}
ull absl(ull a, ull b){
    if(a > b) return a - b;
    return b - a;
}
void solve(){
    cin >> n;
    int l = 1, mid = 1, r;
    int ans = 0;
    for (int i = 1; i <= n; i ++ ){
        cin >> a[i];
        a[i - 1] = absl(a[i - 1], a[i]);
    }
    for (int i = 1; i < n; i ++ ){
        f[i] = i == 1 || i - 1 == mid ? a[i] : gcd(f[i - 1], a[i]);
        while (l <= mid && gcd(f[l], f[i]) == 1) l ++ ;
        if (l > mid) {
            f[i] = a[mid = i];
            int j;
            for (j = i - 1; j >= l; j -- )
                f[j] = gcd(a[j], f[j + 1]);
            while (l <= i && f[l] == 1) l ++ ;
        }
        if (i - l + 1 > ans) ans = i - l + 1;
    }
    cout << ++ ans << '\n';
}
signed main(){
    int t;
    cin >> t;
    while (t -- ) solve();
    return 0;
}

