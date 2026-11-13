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

const int N = 510, M = N * N;
int n, m, w[N], d[N][N];
int link[N];
bool vis[N];
int h[N], e[M], ne[M], idx;
void add(int a, int b){
    e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}
void floyd(){
    for (int k = 1; k <= n; k ++ )
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= n; j ++ )
                d[i][j] |= d[i][k] & d[k][j];
}
bool dfs(int x, int s){
    for (int i = h[x]; i; i = ne[i])
        if(d[x][e[i]] && !vis[e[i]] && w[e[i]] <= s){
            int j = e[i];
            vis[j] = 1;
            if(!link[j] || dfs(link[j], s)){
                link[j] = x;
                return 1;
            }
        }
    return 0;
}
bool check(int x){
    int ans = 0, sum = 0;
    memset(link, 0, sizeof link);
    for (int i = 1; i <= n; i ++ )
        if(w[i] <= x){
            sum ++ ;
            memset(vis, 0, sizeof vis);
            ans += dfs(i, x);
        }
    return sum - ans <= m;
}
signed main(){
    cin >> m >> n;
    m ++ ;
    for (int i = 1; i <= n; i ++ ) d[i][i] = 1;
    for (int i = 1, m, x; i <= n; i ++ ){
        cin >> w[i] >> m;
        while (m -- ) cin >> x, d[i][x] = 1;
    }
    floyd();
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= n; j ++ )
            if(i != j && d[i][j]) add(i, j);
    if(check(1e9)){
        puts("AK");
        return 0;
    }
    int l = 0, r = 1e9;
	while (l < r){
		int mid = (l + r) >> 1;
		if(check(mid)) l = mid + 1;
		else r = mid;
	}
	cout << l << '\n';
    return 0;
}

