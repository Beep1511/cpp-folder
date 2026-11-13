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

int n;
const int N = 200010;
int val[N], flip[N], mx[N];
int ans;
int solve(int l, int r){
    int l1 = 0, l2 = 0, b1 = n + 1, b2 = n + 1, c1 = 0, c2 = 0;
    for (int i = l; i <= r; i ++ )
        if(b1 > val[i]) b1 = val[i], l1 ++ , c1 += flip[i];
        else if(b2 > val[i]) b2 = val[i], l2 ++ , c2 += flip[i];
        else printf("-1\n"), exit(0);
    return min(l1 - c1 + c2, l2 - c2 + c1);
}

signed main(){
    cin >> n;
    for (int i = 1, f = 0, a, b; i <= n; i ++ , f = 0){
        cin >> a >> b;
        if(a > b) swap(a, b), f = 1;
        if(a > n || b <= 1){
            cout << "-1";
            return 0;
        }
        val[a] = b - n, flip[a] = f;
    }
    for (int i = n; i; i -- ) mx[i] = max(mx[i + 1], val[i]);
    for (int i = 2, lst = 1, mn = val[1]; i <= n + 1; i ++ )
        if((mn = min(mn, val[i - 1])) > mx[i])
            ans += solve(lst, i - 1), lst = i;
    cout << ans << '\n';
    return 0;
}

