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

const int N = 200010;
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    if(s[0] != '1' || s[n - 1] != '1'){
        puts("NO");
        return ;
    }
    int cnt = 0;
    for (int i = 0; i < n; i ++ )
        if(s[i] == '1') cnt ++ ;
    if(cnt & 1){
        puts("NO");
        return ;
    }
    puts("YES");
    char a[N], b[N];
    cnt >>= 1;
    for (int i = 0; i < n; i ++ ) {
        if (s[i] == '1') {
            if(cnt) {
                a[i] = b[i] = '(';
                cnt -- ;
            } else{
                a[i] = b[i] = ')';
            }
        }
    }
    
    char now = '(';
    for (int i = 0; i < n; i ++ ) {
        if (s[i] == '0') {
            a[i] = now;
            now ^= '(' ^ ')';
            b[i] = now;
        }
    }
    
    for (int i = 0; i < n; i ++ ) {
        putchar(a[i]);
    }
    puts("");
    for (int i = 0; i < n; i ++ ) {
        putchar(b[i]);
    }
    puts("");
}
signed main(){
    int t;
    cin >> t;
    while (t -- ) solve();
    return 0;
}
